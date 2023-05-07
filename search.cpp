#include <iostream>
#include <cmath>
#include <algorithm>
// #include "tqdm.hpp"
#include "engine.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "engine_constants.hpp"
using namespace std;

double Engine::move_value(const Move &move, bool allow_pv_scoring, const Move &best_move){
    // PieceType move_piece_type = board->piece_type_at(move._from_square);
    if (move == best_move){
        return 60000;
    }
    if (allow_pv_scoring && _score_pv){
        if (_pv_table[0][_ply] == move){
            _score_pv = false;
            return 55000;
        }
    }
    if (move._promotion){
        return 150000;
    }
    push(move);
    bool gives_check = board->is_check();
    if (gives_check){
        if (board->generate_legal_moves().empty()){
            pop();
            return 100000;
        }
        pop();
        return 45000;
    }
    Bitboard piece_attack_mask = board->attacks_mask(move._to_square) & ~board->_kings;
    Bitboard attack_threats = piece_attack_mask & board->occupied_co(board->_turn);
    Bitboard defend_pieces = piece_attack_mask & board->occupied_co(!(board->_turn));
    Bitboard opponent_attackers_mask = board->attackers_mask(board->_turn, move._to_square);
    pop();
    if (board->is_capture(move)){
        if (board->is_passed_pawn(board->get_capture_piece_square(move), !(board->_turn))){
            return 40000;
        }
        return 35000 + 100 * see_capture(move._to_square) + evaluator.evaluate_capture(move);
    }
    for (unsigned char i = 0; i < NUM_KILLER_MOVES; i++){
        if (_killer_moves[i][_ply] == move){
            return 30000 - i;
        }
    }
    unsigned char num_pawn_attacks = popcount(opponent_attackers_mask & board->_pawns);
    if (num_pawn_attacks){
        return -(10000 + num_pawn_attacks);
    }
    if (defend_pieces){
        return 20000 + popcount(defend_pieces);
    }
    if (attack_threats){
        return 25000 + popcount(attack_threats);
    }
    // if (board->is_castling(move)){
    //     return 15000;
    // }
    double history_moves_score = _history_moves[board->piece_type_at(move._from_square)][board->color_at(move._from_square)][move._to_square] / 5;
    double passed_pawn_point = double(board->is_passed_pawn(move._from_square, board->_turn));
    return 100 * history_moves_score + 35 * passed_pawn_point;
}

// Score Engine::alpha_beta(unsigned char depth, Score alpha, Score beta, bool apply_null_move){
//     _num_nodes_searched++;
//     _pv_length[_ply] = _ply;
//     if (_ply){
//         unsigned char outcome = board->outcome();
//         if (outcome){
//             return get_game_over_score(outcome, evaluate_board());
//         }
//     }
//     if (depth > MAX_DEPTH - 1){
//         depth = 0;
//     }
//     if (!(depth) || _ply > MAX_DEPTH - 1){
//         Score evaluation = quiescence(alpha, beta);
//         return evaluation;
//     }
//     vector<Move> moves = get_ordered_moves();
//     for (unsigned short int move_index = 0; move_index < moves.size(); move_index++){
//         const Move &move = moves[move_index];
//         bool not_capture_move = !(board->is_capture(move));
//         push(move);
//         Score score = -alpha_beta(depth - 1, -beta, -alpha);
//         pop();
//         if (score >= beta){
//             if (not_capture_move){
//                 update_killer_moves(move);
//             }
//             return beta;
//         }
//         if (score > alpha){
//             if (not_capture_move){
//                 _history_moves[board->piece_type_at(move._from_square)][board->color_at(move._from_square)][move._to_square] += depth;
//             }
//             alpha = score;
//             update_pv_table(move);
//         }
//     }
//     return alpha;
// }

Score Engine::alpha_beta(unsigned char depth, Score alpha, Score beta, bool apply_null_move){
    _num_nodes_searched++;
    _pv_length[_ply] = _ply;
    if (_ply){
        unsigned char outcome = board->outcome();
        if (outcome){
            return get_game_over_score(outcome, evaluate_board() / 100);
        }
    }
    bool not_in_check = !(board->is_check());
    if (ENABLE_CHECK_EXTENSION && _ply && !(not_in_check) && (popcount(board->_checkers) > 1 || see_capture(msb(board->_checkers)) < 0)){
        depth++;
    }
    if (depth > MAX_DEPTH - 1){
        depth = 0;
    }
    Move best_move;
    unsigned long long key = board->_transposition_key;
    bool is_pvs_node = (beta - alpha) > PVS_CUTOFF;
    Score t_score = read_transposition_table(alpha, beta, key, best_move, depth);
    // bool transposition_allowed = bool(_ply) && !(board->is_repetition(2) || board->_is_halfmoves(98)) && !(is_pvs_node);
    bool transposition_allowed = bool(_ply) && !(board->is_repetition(2) || board->_is_halfmoves(98));
    if (transposition_allowed && t_score != INVALID_SCORE){
        return t_score;
    }
    if (!(depth) || _ply > MAX_DEPTH - 1){
        const Score &evaluation = quiescence(alpha, beta);
        if (!(T_TABLE_MIN_DEPTH)){
            write_transposition_table(HASH_EXACT, evaluation, key);
        }
        return evaluation;
    }
    // mate distance pruning
    Score mate_score = Score(1, 2) - _ply;
    if (mate_score < beta){
        beta = mate_score;
        if (alpha >= mate_score){
            return mate_score;
        }
    }

    // const unsigned char null_move_reduction_limit = 1 + sqrt(double(depth - 1));
    const unsigned char null_move_reduction_limit = 2;

    // if (apply_null_move){
    //     bool can_apply_null_move = depth > null_move_reduction_limit && not_in_check;
    //     if (_ply && can_apply_null_move){
    //         push(Move::null());
    //         Score score = -alpha_beta(depth - 1 - null_move_reduction_limit, -beta, -beta + PVS_CUTOFF, false);
    //         pop();
    //         if (score >= beta){
    //             return beta;
    //         }
    //     }
    // }

    bool futility_pruning = false;
    if (not_in_check && _game_phase < ENDGAME_PERCENTAGE){
        // static evaluation pruning
        Score static_evaluation = evaluate_board();
        const double pawn_evaluation = 100 * evaluator.evaluate_piece(1);
        if (depth < 3 && abs(beta - 1) > -mate_score + 100){
            double evaluation_margin = pawn_evaluation * depth;
            if (static_evaluation - evaluation_margin >= beta){
                return static_evaluation - evaluation_margin;
            }
        }
        // null move reduction
        if (apply_null_move){
            if (_ply && depth > null_move_reduction_limit){
                push(Move::null());
                Score score = -alpha_beta(depth - 1 - null_move_reduction_limit, -beta, -beta + PVS_CUTOFF, false);
                pop();
                if (score >= beta){
                    return beta;
                }
            }
            // razoring
            if (!(is_pvs_node)){
                Score evaluation = static_evaluation + pawn_evaluation;
                if (evaluation < beta && depth == 1){
                    Score new_evaluation = quiescence(alpha, beta);
                    return max(new_evaluation, evaluation);
                }
                evaluation += pawn_evaluation;
                if (evaluation < beta && depth < 4){
                    Score new_evaluation = quiescence(alpha, beta);
                    if (new_evaluation < beta){
                        return max(new_evaluation, evaluation);
                    }
                }
            }
        }
        // futility pruning condition
        const double knight_evaluation = 100 * evaluator.evaluate_piece(2);
        const double rook_evaluation = 100 * evaluator.evaluate_piece(4);
        const double futility_margin[4] = {0, pawn_evaluation, knight_evaluation, rook_evaluation};
        if (depth < 4 && alpha < mate_score && static_evaluation + futility_margin[depth] <= alpha){
            futility_pruning = true;
        }
    }

    unsigned char hash_flag = HASH_ALPHA;
    const vector<Move> moves = get_ordered_moves(BB_ALL, BB_ALL, best_move);
    // auto iter = _ply ? tq::range(moves.size()) : tq::trange(moves.size())
    // auto iter = tq::range(moves.size());
    // for (auto move_index : iter){
    for (unsigned int move_index = 0; move_index < moves.size(); move_index++){
        const Move &move = moves[move_index];
        // if (_ply == 1){
        //     const Move &prev_move = board->pop();
        //     string prev_move_san = board->san(prev_move);
        //     board->push(prev_move);
        //     cout << prev_move_san << " " << board->san(move) << " -> " << int(depth) << " " << alpha << " " << beta << " " << apply_null_move << endl;
        // }
        bool not_capture_move = !(board->is_capture(move));
        if (move_index && futility_pruning && not_capture_move && !(move._promotion) && not_in_check){
            continue;
        }
        bool safe_to_apply_lmr = can_apply_lmr(move) && !(is_pvs_node) && not_capture_move && not_in_check;
        push(move);
        safe_to_apply_lmr = safe_to_apply_lmr && !(board->is_check());
        Score score;
        if (!(move_index)){
            score = -alpha_beta(depth - 1, -beta, -alpha);
        } else{
            if (move_index >= FULL_DEPTH_SEARCH_LMR && depth >= REDUCTION_LIMIT_LMR && safe_to_apply_lmr){
                // const unsigned char lmr_reduction = depth / 3;
                // const unsigned char lmr_reduction = sqrt(double(depth - 1)) + sqrt(double(move_index - 1));
                const unsigned char lmr_reduction = 1 + sqrt(double(move_index - 1));
                score = -alpha_beta(depth - 1 - lmr_reduction, -alpha - PVS_CUTOFF, -alpha);
            } else{
                score = alpha + 1;
            }
            if (score > alpha){
                score = -alpha_beta(depth - 1, -alpha - PVS_CUTOFF, -alpha);
                if (score > alpha && score < beta){
                    score = -alpha_beta(depth - 1, -beta, -alpha);
                }
            }
        }
        pop();
        if (score > alpha){
            hash_flag = HASH_EXACT;
            if (not_capture_move){
                _history_moves[board->piece_type_at(move._from_square)][board->color_at(move._from_square)][move._to_square] += depth;
            }
            alpha = score;
            best_move = move;
            update_pv_table(move);
            if (score >= beta){
                if (depth >= T_TABLE_MIN_DEPTH){
                    write_transposition_table(HASH_BETA, beta, key, best_move, depth);
                }
                if (not_capture_move){
                    update_killer_moves(move);
                }
                return beta;
            }
        }
    }
    if (depth >= T_TABLE_MIN_DEPTH){
        write_transposition_table(hash_flag, alpha, key, best_move, depth);
    }
    return alpha;
}

double Engine::see(Square square, Bitboard self_attackers, Bitboard opponent_attackers){
    Bitboard least_attackers_mask = board->get_least_attackers_mask(square);
    if (!(least_attackers_mask)){
        return 0;
    }
    const Move move(msb(least_attackers_mask), square);
    PieceType captured_piece_type = board->get_capture_piece_type(move);
    double score = evaluator.evaluate_piece(captured_piece_type);
    push(move);
    score -= see(square);
    pop();
    return max(0.0, score);
}

double Engine::see_capture(Square square){
    Bitboard least_attackers_mask = board->get_least_attackers_mask(square);
    if (!(least_attackers_mask)){
        return 0;
    }
    const Move move(msb(least_attackers_mask), square);
    PieceType captured_piece_type = board->get_capture_piece_type(move);
    double score = evaluator.evaluate_piece(captured_piece_type);
    push(move);
    score -= see(square);
    pop();
    return score;
}

Score Engine::quiescence(Score alpha, Score beta){
    _num_nodes_searched++;
    // if (board->is_checkmate()){
    //     return Score(-_ply, 2);
    // }
    _pv_length[_ply] = _ply;
    if (_ply > MAX_DEPTH - 1){
        return evaluate_board();
    }
    const Score &evaluation = evaluate_board();
    if (evaluation >= beta){
        return beta;
    }
    if (evaluation > alpha){
        alpha = evaluation;
    }
    for (Move move : get_ordered_captures(BB_ALL, BB_ALL & ~board->_kings)){
        push(move);
        const Score &score = -quiescence(-beta, -alpha);
        pop();
        if (score > alpha){
            alpha = score;
            update_pv_table(move);
            if (score >= beta){
                return beta;
            }
        }
    }
    return alpha;
}