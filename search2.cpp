#include <iostream>
#include <cmath>
#include <algorithm>
#include "engine.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "engine_constants.hpp"
using namespace std;

double Engine::move_value(Move move, bool allow_pv_scoring){
    if (allow_pv_scoring && _score_pv){
        if (_pv_table[0][_ply] == move){
            _score_pv = false;
            return 50000;
        }
    }
    if (move._promotion){
        return 45000 + move._promotion;
    }
    board.push(move);
    if (board.is_check()){
        board.pop();
        return 40000;
    }
    unsigned long long piece_attack_mask = board.attacks_mask(move._to_square);
    board.pop();
    if (board.is_capture(move)){
        return 35000 + evaluate_capture(move);
    }
    for (unsigned int i = 0; i < NUM_KILLER_MOVES; i++){
        if (_killer_moves[i][_ply] == move){
            return 30000 - i;
        }
    }
    unsigned int num_attack_threats = popcount(piece_attack_mask & board.occupied_co(!(board._turn)));
    if (num_attack_threats){
        return 20000 + num_attack_threats;
    }
    unsigned int num_defend_pieces = popcount(piece_attack_mask & board.occupied_co(board._turn));
    if (num_defend_pieces){
        return 25000 + num_defend_pieces;
    }
    if (board.is_castling(move)){
        return 15000;
    }
    double history_moves_score = _history_moves[board.piece_type_at(move._from_square)][int(board.color_at(move._from_square))][move._to_square] / 5;
    double passed_pawn_point = double(board.is_passed_pawn(move._from_square, board._turn));
    return 100 * history_moves_score + 35 * passed_pawn_point;
}

Score Engine::alpha_beta(unsigned int depth, Score alpha, Score beta){
    _num_nodes_searched++;
    _pv_length[_ply] = _ply;
    if (_ply){
        bool is_game_over = board.is_game_over();
        if (is_game_over){
            Score evaluation = evaluate_board();
            if (board.is_checkmate()){
                return Score(-_ply, 2) + evaluation;
            }
            return DRAW_POINT + evaluation / 100;
        }
    }
    vector<unsigned long long> key = board.transposition_key_vector();
    bool is_pvs_search = (beta - alpha) > PVS_CUTOFF;
    bool transposition_allowed = bool(_ply) && !(board.is_repetition(2) || board._is_halfmoves(98)) && !(is_pvs_search);
    if (transposition_allowed){
        Score score = read_transposition_table(alpha, beta, key, depth);
        if (score != INVALID_SCORE){
            return score;
        }
    }
    bool not_in_check = !(board.is_check());
    // if (_ply){
    //     if (!(not_in_check)){
    //         depth++;
    //     }
    // }
    if (!(depth) || _ply > MAX_DEPTH - 1 || depth > MAX_DEPTH - 1){
        Score evaluation = quiescence(alpha, beta);
        if (!(T_TABLE_MIN_DEPTH)){
            write_transposition_table(HASH_EXACT, evaluation, key, 0);
        }
        return evaluation;
    }

    // bool apply_null_move = depth >= 1 + NULL_MOVE_REDUCTION_LIMIT && not_in_check && !(board._pawns & board._white_occupied & BB_RANK_7) && !(board._pawns & board._black_occupied & BB_RANK_1);
    // if (_ply && apply_null_move){
    //     board.push(Move::null());
    //     Score score = alpha_beta(depth - 1 - NULL_MOVE_REDUCTION_LIMIT, -beta, -beta + PVS_CUTOFF);
    //     board.pop();
    //     if (score >= beta){
    //         return beta;
    //         // depth -= 1;
    //     }
    // }
    vector<Move> moves = get_ordered_moves();
    unsigned int hash_flag = HASH_ALPHA;
    // bool null_move_applied;
    // if (_ply & 1){
    //     null_move_applied = _self_color == board._turn;
    // } else{
    //     null_move_applied = _self_color != board._turn;
    // }
    bool oppoent_has_important_capture_moves = false;
    // SquareSet important_pieces_squareset((board._queens | board._rooks) & board.occupied_co(board._turn));
    SquareSet important_pieces_squareset(board.occupied_co(board._turn) & ~board._pawns);
    // SquareSet important_pieces_squareset(board.occupied_co(board._turn));
    board.push(Move::null());
    for (Square square = important_pieces_squareset.start(); important_pieces_squareset.squares_left(); important_pieces_squareset.next(square)){
        if (board.attackers_mask(board._turn, square)){
            oppoent_has_important_capture_moves = true;
            break;
        }
    }
    board.pop();
    for (unsigned int move_index = 0; move_index < moves.size(); move_index++){
        const Move &move = moves[move_index];
        bool not_capture_move = !(board.is_capture(move));

        bool safe_to_apply_lmr = can_apply_lmr(move) && !(is_pvs_search) && not_capture_move && not_in_check && !(oppoent_has_important_capture_moves);
        push(move);
        safe_to_apply_lmr = safe_to_apply_lmr && !(board.is_check());
        Score score;
        if (!(move_index)){
            score = -alpha_beta(depth - 1, -beta, -alpha);
        } else{
            if (move_index >= FULL_DEPTH_SEARCH_LMR && depth >= REDUCTION_LIMIT_LMR && safe_to_apply_lmr){
                score = -alpha_beta(depth - 2, -alpha - PVS_CUTOFF, -alpha);
            } else{
                score = alpha + 1;
            }
            if (score > alpha){
                score = -alpha_beta(depth - 1, -alpha - PVS_CUTOFF, -alpha);
                if (score > alpha && score< beta){
                    score = -alpha_beta(depth - 1, -beta, -alpha);
                }
            }
        }
        pop();

        if (score >= beta){
            if (depth > T_TABLE_MIN_DEPTH - 1){
                write_transposition_table(HASH_BETA, beta, key, depth);
            }
            if (not_capture_move){
                update_killer_moves(move);
            }
            return beta;
        }
        if (score > alpha){
            hash_flag = HASH_EXACT;
            if (not_capture_move){
                _history_moves[board.piece_type_at(move._from_square)][int(board.color_at(move._from_square))][move._to_square] += depth;
            }
            alpha = score;
            update_pv_table(move);
        }
    }
    if (depth > T_TABLE_MIN_DEPTH - 1){
        write_transposition_table(hash_flag, alpha, key, depth);
    }
    return alpha;
}

Score Engine::quiescence(Score alpha, Score beta){
    _num_nodes_searched++;
    Score evaluation = evaluate_board();
    if (evaluation >= beta){
        return beta;
    }
    if (evaluation > alpha){
        alpha = evaluation;
    }
    if (board.is_check()){
        return alpha;
    }
    for (Move move : get_ordered_captures()){
        push(move);
        Score score = -quiescence(-beta, -alpha);
        pop();
        if (score >= beta){
            return beta;
        }
        if (score > alpha){
            alpha = score;
        }
    }
    return alpha;
}