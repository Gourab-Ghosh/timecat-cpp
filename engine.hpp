#ifndef _ENGINE_H
#define _ENGINE_H

#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_map>
#include <list>
#include <chrono>
#include "constants.hpp"
#include "utils.hpp"
#include "board.hpp"
#include "engine_constants.hpp"
#include "evaluate_board.hpp"
using namespace std;
using namespace std::chrono;

class Engine{
    // unordered_map<unsigned long long, TranspositionData> _transposition_table;
    unordered_map<unsigned long long, TranspositionData> _transposition_table;
    list<unsigned long long> _transposition_table_keys;
    unsigned long long max_keys_in_t_table = 100000;
    unordered_map<unsigned int, double> _random_move_values;
    time_point<system_clock> _clock_start;
    stack<double> _game_phase_stack;

public:
    // constants
    unsigned long long _num_nodes_searched;
    unsigned short int _ply;
    unsigned char _pv_length[MAX_DEPTH];
    Move _pv_table[MAX_DEPTH][MAX_DEPTH];
    bool _follow_pv;
    bool _score_pv;
    Score _last_predicted_score;
    Move _killer_moves[NUM_KILLER_MOVES][MAX_DEPTH];
    double _history_moves[7][2][64];
    unsigned char _last_depth_searched;
    bool _self_color;
    double _game_phase;
    Board *board;
    BoardEvaluator evaluator;
    // engine functions
    Engine(Board &board = RANDOM_BOARD);
    void set_fen(const string &fen);
    void reset_variables();
    void update_killer_moves(Move killer_move);
    Score evaluate_board(bool reverse_score = true, bool print_scores_seperately = false);
    Score read_transposition_table(const Score &alpha, const Score &beta, const unsigned long long &key, Move &best_move, unsigned char depth = 0);
    void write_transposition_table(unsigned char flag, Score score, const unsigned long long &key, const Move &best_move = Move::null(), unsigned char depth = 0);
    vector<Move> get_ordered_moves(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL, const Move &best_move = Move::null());
    vector<Move> get_ordered_captures(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    void enable_pv_scoring(const vector<Move> &moves);
    Score get_game_over_score(unsigned char outcome, const Score &current_evaluation) const;
    bool can_apply_lmr(const Move &move) const;
    void update_pv_table(const Move &move);
    void update_game_phase();
    void push(Move move);
    Move pop();
    double calculate_time_passed() const;
    void reset_clock();
    bool is_time_out(double time_left) const;
    Move get_best_move(unsigned char depth, bool print = true);
    string get_pv_line(bool san = true);
    // search functions
    double move_value(const Move &move, bool allow_pv_scoring = true, const Move &best_move = Move::null());
    Score alpha_beta(unsigned char depth, Score alpha = -inf, Score beta = inf, bool apply_null_move = true);
    double see(Square square, Bitboard self_attackers = BB_ALL, Bitboard opponent_attackers = BB_ALL);
    double see_capture(Square square);
    Score quiescence(Score alpha, Score beta);
};

#endif