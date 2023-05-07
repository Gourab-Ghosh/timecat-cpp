#ifndef _EVALUATE_BOARD_H
#define _EVALUATE_BOARD_H

#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_map>
#include <chrono>
#include "constants.hpp"
#include "utils.hpp"
#include "board.hpp"
#include "engine_constants.hpp"
#include "nnue/nnue_wrapper.hpp"
using namespace std;
using namespace std::chrono;

class BoardEvaluator{
public:
    double _game_phase;
    unsigned long long _num_times_board_evaluated;
    Board *board;
    BoardEvaluator(Board &board = RANDOM_BOARD);
    void reset_variables();
    double get_game_phase();
    double evaluate_mvv_lva(const Move &move);
    double evaluate_quick_see(Square square);
    double evaluate_capture(const Move &move);
    double evaluate_piece(PieceType piece_type) const;
    double evaluate_piece_position(PieceType piece_type, bool color, Square square);
    double evaluate_piece_at(PieceType piece_type, bool color, Square square, Bitboard mobility_mask = BB_ALL);
    static Bitboard get_king_side_board_mask(Ray king_file);
    bool is_uncovered_king(bool color, Square square);
    double evaluate_king_safety(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file, double material_score);
    static double evaluate_king_endgame_forcing_checkmate(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file, double material_score);
    double evaluate_rook_position(Square white_king_square, Square black_king_square, Ray white_king_rank, Ray black_king_rank, Ray white_king_file, Ray black_king_file);
    double evaluate_pawn_structures();
    double evaluate_opening_board(bool print_scores_seperately = false);
    double evaluate_midgame_board(bool print_scores_seperately = false);
    double evaluate_endgame_board(bool print_scores_seperately = false);
    double evaluate_board(bool reverse_score = false, bool print_scores_seperately = false);
};

#endif