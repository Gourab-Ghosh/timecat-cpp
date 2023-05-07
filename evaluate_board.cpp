#include <iostream>
#include <cmath>
#include <algorithm>
#include "board.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "evaluate_board.hpp"
#include "engine_constants.hpp"
using namespace std;

BoardEvaluator::BoardEvaluator(Board &board){
    this->board = &board;
    reset_variables();
}

void BoardEvaluator::reset_variables(){
    _game_phase = get_game_phase();
    _num_times_board_evaluated = 0;
}

double BoardEvaluator::get_game_phase(){
    const double weights[2] = {5, 2};
    Bitboard masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    const unsigned char initial_num_pieces_of_piece_type[7] = {0, 16, 4, 4, 4, 2, 2};
    double initial_material_sum = 0;
    double current_material_sum = 0;
    for (PieceType piece_type = 1; piece_type < 6; piece_type++){
        double material_weight = material_weights[piece_type];
        initial_material_sum += initial_num_pieces_of_piece_type[piece_type] * material_weight;
        current_material_sum += double(popcount(masks_array[piece_type])) * material_weight;
    }
    double backrank_occupied;
    double divide_factor;
    if (current_material_sum / initial_material_sum > OPENING_PERCENTAGE){
        backrank_occupied = 16 - double(popcount(board->_occupied & (BB_RANK_1 | BB_RANK_8)));
        divide_factor = initial_material_sum * weights[0] + 16 * weights[1];
    } else{
        backrank_occupied = 0;
        divide_factor = initial_material_sum * weights[0];
    }
    double position = (initial_material_sum - current_material_sum) * weights[0] + backrank_occupied * weights[1];
    return position / divide_factor;
}

double BoardEvaluator::evaluate_mvv_lva(const Move &move){
    if (board->is_en_passant(move)){
        return mvv_lva[1][1];
    }
    return mvv_lva[board->piece_type_at(move._from_square)][board->piece_type_at(move._to_square)];
}

double BoardEvaluator::evaluate_quick_see(Square square){
    Bitboard self_attackers_mask = board->attackers_mask(board->_turn, square);
    Bitboard opponent_attackers_mask = board->attackers_mask(!(board->_turn), square);
    // bool min_side_attackers = 0;
    PieceType opponent_last_attacker_piece_type = 0;
    double quick_see_score = 0;
    for (PieceType piece_type = 1; piece_type < 7; piece_type++){
        quick_see_score += double(popcount(self_attackers_mask & board->pieces_mask(piece_type, board->_turn))) * material_weights[piece_type];
        quick_see_score -= double(popcount(opponent_attackers_mask & board->pieces_mask(piece_type, !(board->_turn)))) * material_weights[piece_type];
        if (opponent_attackers_mask & board->pieces_mask(piece_type, !(board->_turn))){
            opponent_last_attacker_piece_type = piece_type;
        }
    }
    quick_see_score += material_weights[opponent_last_attacker_piece_type];
    return quick_see_score;
}

double BoardEvaluator::evaluate_capture(const Move &move){
    if (DEBUG){
        if (!(board->is_capture(move))){
            cout << "evaluate_capture works for capturemoves only!" << endl;
            raise_error();
        }
    }
    // double quick_see_score = max(0.0, evaluate_quick_see(move._to_square));
    // return 100 * quick_see_score + evaluate_mvv_lva(move);
    return evaluate_mvv_lva(move);
}

double BoardEvaluator::evaluate_piece(PieceType piece_type) const{
    return (1 - _game_phase) * opening_material_weights[piece_type] + _game_phase * endgame_material_weights[piece_type];
}

double BoardEvaluator::evaluate_piece_position(PieceType piece_type, bool color, Square square){
    if (color){
        square = square_mirror(square);
    }
    double opening_score = opening_pieces_unordered_mapping_weights[piece_type] * pieces_unordered_mapping[0][piece_type][square];
    double endgame_score = endgame_pieces_unordered_mapping_weights[piece_type] * pieces_unordered_mapping[1][piece_type][square];
    double score = 0;
    if (_game_phase < ENDGAME_PERCENTAGE - TRANSITION_PHASE_PERCENT / 2){
        score = opening_score;
    } else if (_game_phase > ENDGAME_PERCENTAGE + TRANSITION_PHASE_PERCENT / 2){
        score = endgame_score;
    } else{
        score = (1 - _game_phase) * opening_score + _game_phase * endgame_score;
    }
    return score;
}

double BoardEvaluator::evaluate_piece_at(PieceType piece_type, bool color, Square square, Bitboard mobility_mask){
    if (mobility_mask == BB_ALL){
        mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
    }
    if (DEBUG){
        if (!(piece_type)){
            cout << "Got unexpected piece type!" << endl;
            raise_error();
        }
    }
    double material_score = evaluate_piece(piece_type);
    // return material_score;
    if (piece_type != 1 && piece_type != 6){
        if (!(board->is_pinned(color, square) && board->generate_legal_moves(BB_SQUARES[square], BB_ALL).empty())){
            switch (piece_type){
                case 2:
                    material_score *= (1 + MOBILITY_ADVANTAGE_PERCENTAGE * double(popcount(mobility_mask)) / 9);
                    break;
                case 3:
                    material_score *= (1 + MOBILITY_ADVANTAGE_PERCENTAGE * double(popcount(mobility_mask)) / 15);
                    break;
                case 4:
                    material_score *= (1 + MOBILITY_ADVANTAGE_PERCENTAGE * double(popcount(mobility_mask)) / 15);
                    break;
                case 5:
                    material_score *= (1 + MOBILITY_ADVANTAGE_PERCENTAGE * double(popcount(mobility_mask)) / 29);
                    break;
            }
        } else{
            material_score *= (1 - PINNED_PENALTY_PERCENTAGE);
        }
    } else if (piece_type == 1){
        if (board->is_passed_pawn(square, color)){
            double pawn_promotion_distance = color ? 7 - square_file(square) : square_file(square);
            material_score *= (1 + PASSED_PAWN_ADVANTAGE_PERCENTAGE * match_interpolate(0.5, 1, 1, 6, 7 - pawn_promotion_distance));
        }
    }
    return material_score;
}

Bitboard BoardEvaluator::get_king_side_board_mask(Ray king_file){
    if (king_file > 4){
        return BB_FILE_F | BB_FILE_G | BB_FILE_H;
    }
    if (king_file < 3){
        return BB_FILE_A | BB_FILE_B | BB_FILE_C;
    }
    return BB_FILE_D | BB_FILE_E;
    // return BB_FILE_C | BB_FILE_D | BB_FILE_E | BB_FILE_F;
}

bool BoardEvaluator::is_uncovered_king(bool color, Square square){
    // Ray king_rank = square_rank(square);
    Ray king_file = square_file(square);
    if (color){
        if (king_file > 1){
            return true;
        }
    } else{
        if (king_file < 6){
            return true;
        }
    }
    if (popcount(get_king_side_board_mask(square) & board->_pawns & board->occupied_co(color)) < 2){
        return true;
    }
    return false;
}

double BoardEvaluator::evaluate_king_safety(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file, double material_score){
    Bitboard white_king_side_board_mask = BB_KING_ATTACKS[white_king_file];
    Bitboard black_king_side_board_mask = BB_KING_ATTACKS[black_king_file];
    double castling_point = 0;
    double rank_position_point = 0;
    double file_position_point = 0;
    double pawn_protection_point = 0;
    double attackers_point = 0;
    // castling
    if (board->has_castling_rights(true)){
        castling_point += 1;
    } else if (board->_white_castling_status == 1){
        castling_point += 3;
    } else if (board->_white_castling_status == 2){
        castling_point += 2;
    }
    if (board->has_castling_rights(false)){
        castling_point -= 1;
    } else if (board->_black_castling_status == 1){
        castling_point -= 3;
    } else if (board->_black_castling_status == 2){
        castling_point -= 2;
    }
    castling_point /= 3;
    // rank position
    switch (white_king_rank){
        case 0:
            rank_position_point += 2;
            break;
        case 1:
            rank_position_point += 1;
            break;
        default:
            rank_position_point -= 3;
            break;
    }
    switch (black_king_rank){
        case 7:
            rank_position_point -= 2;
            break;
        case 6:
            rank_position_point -= 1;
            break;
        default:
            rank_position_point += 3;
            break;
    }
    rank_position_point /= 3;
    // file position
    switch (white_king_file){
        case 0:
            file_position_point += 2;
            break;
        case 1:
            file_position_point += 3;
            break;
        case 2:
            file_position_point += 1;
            break;
        case 5:
            file_position_point += 2;
            break;
        case 6:
            file_position_point += 4;
            break;
        case 7:
            file_position_point += 3;
            break;
        default:
            file_position_point -= 1;
            break;
    }
    switch (black_king_file){
        case 0:
            file_position_point -= 2;
            break;
        case 1:
            file_position_point -= 3;
            break;
        case 2:
            file_position_point -= 1;
            break;
        case 5:
            file_position_point -= 2;
            break;
        case 6:
            file_position_point -= 4;
            break;
        case 7:
            file_position_point -= 3;
            break;
        default:
            file_position_point += 1;
            break;
    }
    file_position_point /= 3;
    // pawn protection
    if (white_king_file < 3 || white_king_file > 4){
        Bitboard protecting_pawns_mask = white_king_side_board_mask & (BB_RANK_2 | BB_RANK_3) & board->_pawns & board->_white_occupied;
        SquareSet protecting_pawns_squareset(protecting_pawns_mask);
        Bitboard king_side_board_mask = 0;
        for (Square square = protecting_pawns_squareset.start(); protecting_pawns_squareset.squares_left(); protecting_pawns_squareset.next(square)){
            pawn_protection_point += 2.0 / square_distance(white_king_square, square);
            king_side_board_mask |= BB_FILES[square_file(square)];
        }
        if (popcount(protecting_pawns_mask) > 2 && king_side_board_mask == white_king_side_board_mask){
            pawn_protection_point += 5;
        }
    } else{
        pawn_protection_point -= 2;
    }
    if (black_king_file < 3 || black_king_file > 4){
        Bitboard protecting_pawns_mask = black_king_side_board_mask & (BB_RANK_6 | BB_RANK_7) & board->_pawns & board->_black_occupied;
        SquareSet protecting_pawns_squareset(protecting_pawns_mask);
        Bitboard king_side_board_mask = 0;
        for (Square square = protecting_pawns_squareset.start(); protecting_pawns_squareset.squares_left(); protecting_pawns_squareset.next(square)){
            pawn_protection_point -= 2.0 / square_distance(black_king_square, square);
            king_side_board_mask |= BB_FILES[square_file(square)];
        }
        if (popcount(protecting_pawns_mask) > 2 && king_side_board_mask == black_king_side_board_mask){
            pawn_protection_point -= 5;
        }
    } else{
        pawn_protection_point += 2;
    }
    pawn_protection_point /= 8;
    // arrackers
    Bitboard white_king_surrounding_mask = get_surrounding_mask(white_king_square);
    Bitboard black_king_surrounding_mask = get_surrounding_mask(black_king_square);
    SquareSet white_king_surrounding_mask_squareset(white_king_surrounding_mask | BB_SQUARES[white_king_square]);
    for (Square square = white_king_surrounding_mask_squareset.start(); white_king_surrounding_mask_squareset.squares_left(); white_king_surrounding_mask_squareset.next(square)){
        attackers_point -= popcount(board->_attackers_mask(false, square, board->_pawns));
    }
    SquareSet black_king_surrounding_mask_squareset(black_king_surrounding_mask | BB_SQUARES[black_king_square]);
    for (Square square = black_king_surrounding_mask_squareset.start(); black_king_surrounding_mask_squareset.squares_left(); black_king_surrounding_mask_squareset.next(square)){
        attackers_point += popcount(board->_attackers_mask(true, square, board->_pawns));
    }
    attackers_point /= 8;
    // return (1000 * castling_point + 100 * rank_position_point + 300 * file_position_point + 2000 * pawn_protection_point + 50 * attackers_point) / 3000;
    return (5 * castling_point + 7 * rank_position_point + 4 * file_position_point + 20 * pawn_protection_point + 6 * attackers_point) / 40;
}

double BoardEvaluator::evaluate_king_endgame_forcing_checkmate(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file, double material_score){
    // forcing king to corner
    unsigned char min_white_king_corner_distance = 16;
    unsigned char min_black_king_corner_distance = 16;
    unsigned char min_white_king_center_distance = 16;
    unsigned char min_black_king_center_distance = 16;
    for (Square corner_square : {A1, H1, A8, H8}){
        unsigned char black_king_corner_distance = rank_file_distance_sum(corner_square, black_king_square);
        unsigned char white_king_corner_distance = rank_file_distance_sum(corner_square, white_king_square);
        if (min_black_king_corner_distance > black_king_corner_distance){
            min_black_king_corner_distance = black_king_corner_distance;
        }
        if (min_white_king_corner_distance > white_king_corner_distance){
            min_white_king_corner_distance = white_king_corner_distance;
        }
    }
    for (Square center_square : {D1, E1, D2, E2}){
        unsigned char black_king_center_distance = rank_file_distance_sum(center_square, black_king_square);
        unsigned char white_king_center_distance = rank_file_distance_sum(center_square, white_king_square);
        if (min_black_king_center_distance > black_king_center_distance){
            min_black_king_center_distance = black_king_center_distance;
        }
        if (min_white_king_center_distance > white_king_center_distance){
            min_white_king_center_distance = white_king_center_distance;
        }
    }
    unsigned char distance_between_kings = rank_file_distance_sum(white_king_square, black_king_square);
    double forcing_towards_corner_score = 0;
    // moving the king having advantage towards the other king for checkmate
    if (material_score > 2){
        forcing_towards_corner_score += 3 * (16 - distance_between_kings) + (16 - min_black_king_corner_distance);
    } else if (material_score < 2){
        forcing_towards_corner_score -= 3 * (16 - distance_between_kings) + (16 - min_white_king_corner_distance);
    }
    forcing_towards_corner_score /= 5;
    return forcing_towards_corner_score;
}

double BoardEvaluator::evaluate_rook_position(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file){
    double open_file_point = 0;
    double double_rook_point = 0;
    double connected_rook_point = 0;
    vector<Square> white_rook_squares = SquareSet(board->_rooks & board->_white_occupied).get_vector();
    for (Square square : white_rook_squares){
        open_file_point -= popcount(board->_pawns & BB_FILES[square_file(square)] & board->_white_occupied);
    }
    vector<Square> black_rook_squares = SquareSet(board->_rooks & board->_black_occupied).get_vector();
    for (Square square : black_rook_squares){
        open_file_point += popcount(board->_pawns & BB_FILES[square_file(square)] & board->_black_occupied);
    }
    if (white_rook_squares.size() == 2){
        if (!(square_rank(white_rook_squares[0])) && !(square_rank(white_rook_squares[1]))){
            if (!(between(white_rook_squares[0], white_rook_squares[1]) & board->_kings)){
                connected_rook_point += 1;
            }
        } else{
            double_rook_point += char(square_file(white_rook_squares[0]) == square_file(white_rook_squares[1]));
        }
    }
    if (black_rook_squares.size() == 2){
        if (square_rank(black_rook_squares[0]) == 7 && square_rank(black_rook_squares[1]) == 7){
            if (!(between(black_rook_squares[0], black_rook_squares[1]) & board->_kings)){
                connected_rook_point -= 1;
            }
        } else{
            double_rook_point -= char(square_file(black_rook_squares[0]) == square_file(black_rook_squares[1]));
        }
    }
    return (2 * open_file_point + 10 * double_rook_point + 5 * connected_rook_point) / 10;
}

double BoardEvaluator::evaluate_pawn_structures(){
    double double_pawns_point = 0;
    double isolated_pawns_point = 0;
    double passed_pawn_point = 0;
    Bitboard white_occupied = board->_white_occupied;
    Bitboard black_occupied = board->_black_occupied;
    Bitboard all_pawns = board->_pawns;
    Bitboard white_pawns = all_pawns & white_occupied;
    Bitboard black_pawns = all_pawns & black_occupied;
    // double pawn
    for (Ray file = 0; file < 8; file++){
        Bitboard file_mask = BB_FILES[file];
        Bitboard white_pawns_in_current_file = white_pawns & file_mask;
        Bitboard black_pawns_in_current_file = black_pawns & file_mask;
        if (white_pawns_in_current_file){
            double_pawns_point -= double(popcount(white_pawns_in_current_file)) - 1;
        }
        if (black_pawns_in_current_file){
            double_pawns_point += double(popcount(black_pawns_in_current_file)) - 1;
        }
    }
    SquareSet white_pawns_squareset(white_pawns);
    for (Square square = white_pawns_squareset.start(); white_pawns_squareset.squares_left(); white_pawns_squareset.next(square)){ // WHITE
        // isolated pawn
        if (!(ADJACENT_FILE_MASKS[square] & white_pawns)){
            isolated_pawns_point -= 1;
        }
        // passed pawn
        if (board->is_passed_pawn(square, true)){
            passed_pawn_point += 1;
        }
    }
    SquareSet black_pawns_squareset(black_pawns);
    for (Square square = black_pawns_squareset.start(); black_pawns_squareset.squares_left(); black_pawns_squareset.next(square)){ // BLACK
        // isolated pawn
        if (!(ADJACENT_FILE_MASKS[square] & black_pawns)){
            isolated_pawns_point += 1;
        }
        // passed pawn
        if (board->is_passed_pawn(square, false)){
            passed_pawn_point -= 1;
        }
    }
    return (3 * double_pawns_point + 2 * isolated_pawns_point + 10 * passed_pawn_point) / 10;
}

double BoardEvaluator::evaluate_opening_board(bool print_scores_seperately){
    // material advantage and piece position and development and center control and threat and mobility
    Square white_king_square = board->find_king_square(true);
    Square black_king_square = board->find_king_square(false);
    Bitboard white_occupied_mask = board->_white_occupied;
    Bitboard black_occupied_mask = board->_black_occupied;
    Ray white_king_rank = square_rank(white_king_square);
    Ray black_king_rank = square_rank(black_king_square);
    Ray white_king_file = square_file(white_king_square);
    Ray black_king_file = square_file(black_king_square);
    const Bitboard masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    Bitboard develop_pieces_mask = board->_bishops | board->_knights;
    Bitboard rook_development_file = BB_FILE_C | BB_FILE_D | BB_FILE_E | BB_FILE_F;

    double material_score = 0;
    double center_control_point = 0;
    double positional_point = 0;
    // double piece_developmnt = 0;
    double piece_developmnt = 3 * (double(popcount(develop_pieces_mask & black_occupied_mask & BB_RANK_8)) - double(popcount(develop_pieces_mask & white_occupied_mask & BB_RANK_1)));
    piece_developmnt += double(popcount(board->_rooks & white_occupied_mask & rook_development_file)) - double(popcount(board->_rooks & black_occupied_mask & rook_development_file));
    piece_developmnt /= 8;

    for (PieceType piece_type = 1; piece_type < 7; piece_type++){
        SquareSet white_pieces_squareset(masks_array[piece_type] & white_occupied_mask);
        for (Square square = white_pieces_squareset.start(); white_pieces_squareset.squares_left(); white_pieces_squareset.next(square)){
            Bitboard mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score += evaluate_piece_at(piece_type, true, square, mobility_mask);
            if (piece_type != 6){
                center_control_point += (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
            }
            positional_point += evaluate_piece_position(piece_type, true, square);
        }
        SquareSet black_pieces_squareset(masks_array[piece_type] & black_occupied_mask);
        for (Square square = black_pieces_squareset.start(); black_pieces_squareset.squares_left(); black_pieces_squareset.next(square)){
            Bitboard mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score -= evaluate_piece_at(piece_type, false, square, mobility_mask);
            if (piece_type != 6){
                center_control_point -= (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
            }
            positional_point -= evaluate_piece_position(piece_type, false, square);
        }
    }
    center_control_point /= 50;
    positional_point /= 100;

    // bishop pair advantage
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }

    // king safety
    double king_safety_score = evaluate_king_safety(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double pawn_structure_point = evaluate_pawn_structures();

    // If king is not safe, try to exchange queens
    double queen_trading_points = 0;
    if (is_uncovered_king(true, white_king_square) & !(board->_queens & black_occupied_mask)){
        queen_trading_points += 1;
    }
    if (is_uncovered_king(false, black_king_square) & !(board->_queens & white_occupied_mask)){
        queen_trading_points -= 1;
    }
    king_safety_score += queen_trading_points;

    double material_score_weight = 1000000;
    double score = material_score_weight * (material_score + king_safety_score / 2 + bishop_pair_advantage_point / 5) + 2000 * piece_developmnt + 500 * center_control_point + 500 * positional_point + 1000 * pawn_structure_point;

    if (DEBUG){
        if (print_scores_seperately){
            cout << "material_score: " << material_score << endl;
            cout << "king_safety_score: " << king_safety_score << endl;
            cout << "center_control_point: " << center_control_point << endl;
            cout << "piece_developmnt: " << center_control_point << endl;
            cout << "positional_point: " << positional_point << endl;
            cout << "pawn_structure_point: " << pawn_structure_point << endl;
        }
    }

    material_score_weight /= 100;
    score /= material_score_weight;
    return score;
}

double BoardEvaluator::evaluate_midgame_board(bool print_scores_seperately){
    // material advantage and piece position and development and center control and mobility
    Square white_king_square = board->find_king_square(true);
    Square black_king_square = board->find_king_square(false);
    Bitboard white_occupied_mask = board->_white_occupied;
    Bitboard black_occupied_mask = board->_black_occupied;
    Ray white_king_rank = square_rank(white_king_square);
    Ray black_king_rank = square_rank(black_king_square);
    Ray white_king_file = square_file(white_king_square);
    Ray black_king_file = square_file(black_king_square);
    const Bitboard masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};

    double material_score = 0;
    double center_control_point = 0;
    double positional_point = 0;
    double attack_threat = 0;

    for (PieceType piece_type = 1; piece_type < 7; piece_type++){
        SquareSet white_pieces_squareset(masks_array[piece_type] & white_occupied_mask);
        for (Square square = white_pieces_squareset.start(); white_pieces_squareset.squares_left(); white_pieces_squareset.next(square)){
            Bitboard mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score += evaluate_piece_at(piece_type, true, square, mobility_mask);
            if (piece_type != 6){
                center_control_point += (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
                attack_threat += popcount(mobility_mask & board->_black_occupied & ~board->_pawns);
            }
            positional_point += evaluate_piece_position(piece_type, true, square);
        }
        SquareSet black_pieces_squareset(masks_array[piece_type] & black_occupied_mask);
        for (Square square = black_pieces_squareset.start(); black_pieces_squareset.squares_left(); black_pieces_squareset.next(square)){
            Bitboard mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score -= evaluate_piece_at(piece_type, false, square, mobility_mask);
            if (piece_type != 6){
                center_control_point -= (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
                attack_threat -= popcount(mobility_mask & board->_white_occupied & ~board->_pawns);
            }
            positional_point -= evaluate_piece_position(piece_type, false, square);
        }
    }
    center_control_point = pow(1 - _game_phase, 2) * center_control_point / 50;
    positional_point /= 100;

    // knight outpost
    double knight_outpost_point = 0;
    SquareSet white_knignts_squareset(board->_knights & board->_white_occupied);
    for (Square square = white_knignts_squareset.start(); white_knignts_squareset.squares_left(); white_knignts_squareset.next(square)){
        if (!(PASSED_PAWN_MASKS[1][square] & ADJACENT_FILE_MASKS[square] & board->_pawns & board->_black_occupied)){
            knight_outpost_point += 1;
        }
    }
    SquareSet black_knignts_squareset(board->_knights & board->_black_occupied);
    for (Square square = black_knignts_squareset.start(); black_knignts_squareset.squares_left(); black_knignts_squareset.next(square)){
        if (!(PASSED_PAWN_MASKS[0][square] & ADJACENT_FILE_MASKS[square] & board->_pawns & board->_white_occupied)){
            knight_outpost_point -= 1;
        }
    }

    // bishop pair advantage
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }

    // king safety
    double king_safety_score = evaluate_king_safety(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double rooks_evaluation_point = evaluate_rook_position(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file);
    double pawn_structure_point = evaluate_pawn_structures();

    // If king is not safe, try to exchange queens
    double queen_trading_points = 0;
    if (is_uncovered_king(true, white_king_square) & !(board->_queens & black_occupied_mask)){
        queen_trading_points += 1;
    }
    if (is_uncovered_king(false, black_king_square) & !(board->_queens & white_occupied_mask)){
        queen_trading_points -= 1;
    }
    king_safety_score += queen_trading_points;

    double material_score_weight = 1000000;
    double score = material_score_weight * (material_score + king_safety_score / 2 + (2 * bishop_pair_advantage_point + knight_outpost_point) / 10) + 1000 * center_control_point + 500 * positional_point + 1000 * pawn_structure_point + 500 * rooks_evaluation_point + 400 * attack_threat;

    if (DEBUG){
        if (print_scores_seperately){
            cout << "material_score: " << material_score << endl;
            cout << "king_safety_score: " << king_safety_score << endl;
            cout << "center_control_point: " << center_control_point << endl;
            cout << "positional_point: " << positional_point << endl;
            cout << "pawn_structure_point: " << pawn_structure_point << endl;
            cout << "rooks_evaluation_point: " << rooks_evaluation_point << endl;
            cout << "knight_outpost_point: " << knight_outpost_point << endl;
            cout << "bishop_pair_advantage_point: " << bishop_pair_advantage_point << endl;
        }
    }

    material_score_weight /= 100;
    score /= material_score_weight;
    return score;
}

double BoardEvaluator::evaluate_endgame_board(bool print_scores_seperately){
    // material advantage and piece position and development and center control and mobility
    Square white_king_square = board->find_king_square(true);
    Square black_king_square = board->find_king_square(false);
    Bitboard white_occupied_mask = board->_white_occupied;
    Bitboard black_occupied_mask = board->_black_occupied;
    Ray white_king_rank = square_rank(white_king_square);
    Ray black_king_rank = square_rank(black_king_square);
    Ray white_king_file = square_file(white_king_square);
    Ray black_king_file = square_file(black_king_square);
    const Bitboard masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};

    double material_score = 0;
    double positional_point = 0;

    for (PieceType piece_type = 1; piece_type < 7; piece_type++){
        SquareSet white_pieces_squareset(masks_array[piece_type] & white_occupied_mask);
        for (Square square = white_pieces_squareset.start(); white_pieces_squareset.squares_left(); white_pieces_squareset.next(square)){
            material_score += evaluate_piece_at(piece_type, true, square, 0);
            positional_point += evaluate_piece_position(piece_type, true, square);
        }
        SquareSet black_pieces_squareset(masks_array[piece_type] & black_occupied_mask);
        for (Square square = black_pieces_squareset.start(); black_pieces_squareset.squares_left(); black_pieces_squareset.next(square)){
            material_score -= evaluate_piece_at(piece_type, false, square, 0);
            positional_point -= evaluate_piece_position(piece_type, false, square);
        }
    }
    positional_point /= 100;

    // insufficient material
    double insufficient_material_score = 0;
    if (_game_phase > ENDGAME_PERCENTAGE){
        if (board->has_insufficient_material(true)){
            insufficient_material_score -= 1;
        }
        if (board->has_insufficient_material(false)){
            insufficient_material_score += 1;
        }
    }

    // bishop pair advantage
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }

    // king checkmate
    double king_checkmate_score = evaluate_king_endgame_forcing_checkmate(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double rooks_evaluation_point = evaluate_rook_position(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file);
    double pawn_structure_point = evaluate_pawn_structures();

    // make king participate into the game
    // double king_center_square_distance_point = double(min(square_distance(white_king_square, E4), square_distance(white_king_square, D5))) - double(min(square_distance(black_king_square, E4), square_distance(black_king_square, D5)));
    double king_participation_point = evaluate_piece_position(6, true, white_king_square) - evaluate_piece_position(6, false, black_king_square);

    // endgame pawn push
    double pawn_push_point = 0;
    SquareSet white_pawns_squareset(board->_pawns & white_occupied_mask);
    for (Square square = white_pawns_squareset.start(); white_pawns_squareset.squares_left(); white_pawns_squareset.next(square)){
        unsigned char pawn_promotion_distance = 7 - square_rank(square);
        if (board->is_passed_pawn(square, true)){
            pawn_push_point += pow(10 - pawn_promotion_distance, 2);
        } else{
            pawn_push_point += pow(10 - pawn_promotion_distance, 1.5);
        }
    }
    SquareSet black_pawns_squareset(board->_pawns & black_occupied_mask);
    for (Square square = black_pawns_squareset.start(); black_pawns_squareset.squares_left(); black_pawns_squareset.next(square)){
        unsigned char pawn_promotion_distance = 7 - square_rank(square);
        if (board->is_passed_pawn(square, false)){
            pawn_push_point -= pow(10 - pawn_promotion_distance, 2);
        } else{
            pawn_push_point -= pow(10 - pawn_promotion_distance, 1.5);
        }
    }
    pawn_push_point /= 640;

    double material_score_weight = 1000000;
    double score = material_score_weight * (material_score + 3 * insufficient_material_score + bishop_pair_advantage_point / 5 + (pawn_structure_point + pawn_push_point) / 5) + 500 * positional_point + 2000 * king_checkmate_score + 1000 * king_participation_point + 500 * rooks_evaluation_point;

    if (DEBUG){
        if (print_scores_seperately){
            cout << "material_score: " << material_score << endl;
            cout << "positional_point: " << positional_point << endl;
            cout << "insufficient_material_score: " << insufficient_material_score << endl;
            cout << "pawn_structure_point: " << pawn_structure_point << endl;
            cout << "rooks_evaluation_point: " << rooks_evaluation_point << endl;
            cout << "bishop_pair_advantage_point: " << bishop_pair_advantage_point << endl;
            cout << "pawn_push_point: " << pawn_push_point << endl;
        }
    }

    material_score_weight /= 100;
    score /= material_score_weight;
    return score;
}

double BoardEvaluator::evaluate_board(bool reverse_score, bool print_scores_seperately){
    if (DEBUG){
        if (popcount(board->_kings) < 2){
            cout << "King capture not possible" << endl;
            raise_error();
        }
    }
    _num_times_board_evaluated++;
    double score;
    if (false){
        if (_game_phase < OPENING_PERCENTAGE){
            score = evaluate_opening_board(print_scores_seperately);
        } else if (_game_phase > ENDGAME_PERCENTAGE){
            score = evaluate_endgame_board(print_scores_seperately);
        } else{
            score = evaluate_midgame_board(print_scores_seperately);
        }
    } else{
        score = board->_turn ? eval_position_nnue(board) : -eval_position_nnue(board);
        // if (_game_phase > ENDGAME_PERCENTAGE){
        //     Square white_king_square = board->find_king_square(true);
        //     Square black_king_square = board->find_king_square(false);
        //     Ray white_king_rank = square_rank(white_king_square);
        //     Ray black_king_rank = square_rank(black_king_square);
        //     Ray white_king_file = square_file(white_king_square);
        //     Ray black_king_file = square_file(black_king_square);
        //     score += evaluate_king_endgame_forcing_checkmate(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, score);

        //     if (board->has_insufficient_material(true)){
        //         score -= 5;
        //     }
        //     if (board->has_insufficient_material(false)){
        //         score += 5;
        //     }

        //     score += evaluate_pawn_structures();
        // }
    }
    score *= double(100 - board->_halfmove_clock) / 100;
    if (reverse_score && !(board->_turn)){
        score = -score;
    }
    return score;
}