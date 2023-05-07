#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>
#include <chrono>
#include "engine.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "engine_constants.hpp"
#include "evaluate_board.cpp"
#include "search.cpp"
// #include "search2.cpp"
using namespace std;
using namespace std::chrono;

Engine::Engine(Board &board) : evaluator(BoardEvaluator(board)){
    this->board = &board;
    reset_variables();
}

void Engine::set_fen(const string &fen){
    board->set_fen(fen);
    reset_variables();
}

void Engine::reset_variables(){
    _num_nodes_searched = 0;
    _ply = 0;
    for (unsigned char i = 0; i < MAX_DEPTH; i++){
        _pv_length[i] = 0;
        for (unsigned char j = 0; j < MAX_DEPTH; j++){
            _pv_table[i][j] = Move::null();
        }
    }
    _follow_pv = false;
    _score_pv = false;
    for (unsigned char i = 0; i < NUM_KILLER_MOVES; i++){
        for (unsigned char j = 0; j < MAX_DEPTH; j++){
            _killer_moves[i][j] = Move::null();
        }
    }
    for (PieceType i = 0; i < 7; i++){
        for (bool j : {true, false}){
            for (Square k = 0; k < 64; k++){
                _history_moves[i][j][k] = 0;
            }
        }
    }
    _last_predicted_score = INVALID_SCORE;
    _last_depth_searched = 0;
    _self_color = board->_turn;
    reset_clock();
    update_game_phase();
    evaluator.reset_variables();
}

void Engine::update_killer_moves(Move killer_move){
    for (unsigned char i = NUM_KILLER_MOVES - 1; i > 0; i--){
        _killer_moves[i][_ply] = _killer_moves[i-1][_ply];
    }
    _killer_moves[0][_ply] = killer_move;
}

Score Engine::evaluate_board(bool reverse_score, bool print_scores_seperately){
    return Score(evaluator.evaluate_board(reverse_score, print_scores_seperately));
}

Score Engine::read_transposition_table(const Score &alpha, const Score &beta, const unsigned long long &key, Move &best_move, unsigned char depth){
    if (_transposition_table.find(key) != _transposition_table.end()){
        const TranspositionData &transposition_data = _transposition_table[key];
        best_move = transposition_data._best_move;
        if (DISABLE_T_TABLE){
            return INVALID_SCORE;
        }
        if (transposition_data._depth >= depth){
            switch (transposition_data._flag){
                case HASH_EXACT:
                    return transposition_data._score;
                case HASH_ALPHA:
                    if (transposition_data._score <= alpha){
                        return transposition_data._score;
                    }
                    break;
                case HASH_BETA:
                    if (transposition_data._score >= beta){
                        return transposition_data._score;
                    }
                    break;
            }
        }
    }
    return INVALID_SCORE;
}

void Engine::write_transposition_table(unsigned char flag, Score score, const unsigned long long &key, const Move &best_move, unsigned char depth){
    bool not_to_save_score = DISABLE_T_TABLE || score._checkmate || abs(score) < 0.05;
    // if (_transposition_table.find(key) == _transposition_table.end()){
    //     _transposition_table[key] = TranspositionData();
    //     // _transposition_table_keys.push_back(key);
    //     // if (_transposition_table_keys.size() > max_keys_in_t_table){
    //     //     _transposition_table.erase(_transposition_table_keys.front());
    //     //     _transposition_table_keys.pop_front();
    //     // }
    // } else if (_transposition_table[key]._depth > depth){
    //     // return;
    // }
    _transposition_table.try_emplace(key, TranspositionData());
    if (not_to_save_score){
        _transposition_table[key]._best_move = best_move;
        return;
    }
    update_transposition_data(_transposition_table[key], depth, flag, score, best_move);
}

vector<Move> Engine::get_ordered_moves(Bitboard from_mask, Bitboard to_mask, const Move &best_move){
    vector<Move> possible_moves = board->generate_legal_moves(from_mask, to_mask);
    if (_follow_pv){
        enable_pv_scoring(possible_moves);
    }
    for (Move move : possible_moves){
        _random_move_values[move.get_hash()] = move_value(move, true, best_move) + double(move._promotion) / 100;
    }
    sort(possible_moves.begin(), possible_moves.end(), [this] (const Move &move1, const Move &move2){return _random_move_values[move1.get_hash()] > _random_move_values[move2.get_hash()];});
    _random_move_values.clear();
    return possible_moves;
}

vector<Move> Engine::get_ordered_captures(Bitboard from_mask, Bitboard to_mask){
    vector<Move> capture_moves = board->generate_legal_captures(from_mask, to_mask);
    for (Move move : capture_moves){
        double score = 100 * see_capture(move._to_square) + evaluator.evaluate_capture(move) + double(move._promotion) / 100;
        _random_move_values[move.get_hash()] = score;
    }
    sort(capture_moves.begin(), capture_moves.end(), [this] (const Move &move1, const Move &move2){return _random_move_values[move1.get_hash()] > _random_move_values[move2.get_hash()];});
    _random_move_values.clear();
    return capture_moves;
}

void Engine::enable_pv_scoring(const vector<Move> &moves){
    _follow_pv = false;
    const Move &pv_move = _pv_table[0][_ply];
    if (any_of(moves.begin(), moves.end(), [pv_move] (const Move &m){return m == pv_move;})){
        _score_pv = true;
        _follow_pv = true;
    }
}

Score Engine::get_game_over_score(unsigned char outcome, const Score &current_evaluation) const{
    if (outcome == 1){
        return Score(-_ply, 2) + current_evaluation;
    }
    Score draw_point = current_evaluation / 100;
    if (_game_phase < ENDGAME_PERCENTAGE){
        draw_point = DRAW_POINT;
    }
    return draw_point;
}

bool Engine::can_apply_lmr(const Move &move) const{
    // return false;
    if (move._promotion){
        return false;
    }
    for (unsigned char i = 0; i < NUM_KILLER_MOVES; i++){
        if (_killer_moves[i][_ply] == move){
            return false;
        }
    }
    return true;
}

void Engine::update_pv_table(const Move &move){
    _pv_table[_ply][_ply] = move;
    for (unsigned char next_ply = _ply + 1; next_ply < _pv_length[_ply + 1]; next_ply++){
        _pv_table[_ply][next_ply] = _pv_table[_ply + 1][next_ply];
    }
    _pv_length[_ply] = _pv_length[_ply + 1];
}

void Engine::update_game_phase(){
    _game_phase = evaluator.get_game_phase();
    evaluator._game_phase = _game_phase;
}

void Engine::push(Move move){
    board->push(move);
    _ply++;
    _game_phase_stack.push(_game_phase);
    update_game_phase();
}

Move Engine::pop(){
    _game_phase = _game_phase_stack.top();
    evaluator._game_phase = _game_phase;
    _game_phase_stack.pop();
    _ply--;
    return board->pop();
}

string Engine::get_pv_line(bool san){
    string pv_line = "";
    unsigned char num_push = 0;
    for (unsigned char i = 0; i < _pv_length[0]; i++){
        Move move = _pv_table[0][i];
        if (san){
            pv_line += board->san(move);
            board->push(move);
            num_push++;
        } else{
            pv_line += move.uci();
        }
        pv_line += " ";
    }
    while (num_push){
        board->pop();
        num_push--;
    }
    if (pv_line.empty()){
        pv_line += "-";
    }
    return pv_line;
}

double Engine::calculate_time_passed() const{
    duration<double> elapsed_seconds = system_clock::now() - _clock_start;
    return elapsed_seconds.count();
}

void Engine::reset_clock(){
    _clock_start = system_clock::now();
}

bool Engine::is_time_out(double time_left) const{
    return calculate_time_passed() > time_left;
}

Move Engine::get_best_move(unsigned char depth, bool print){
    reset_variables();
    _transposition_table.clear();
    Score score;
    unsigned char current_depth = 1;
    Score alpha = -inf;
    Score beta = inf;
    double time_passed = 0;
    do {
        _follow_pv = true;
        score = alpha_beta(current_depth, alpha, beta);
        if (score <= alpha || score >= beta){
            alpha = -inf;
            beta = inf;
            continue;
        }
        alpha = score - ASPIRATION_WINDOW_CUTOFF;
        beta = score + ASPIRATION_WINDOW_CUTOFF;
        if (!(board->_turn)){
            score = -score;
        }
        time_passed = calculate_time_passed();
        if (print){
            cout << "info depth " << int(current_depth) << " score " << score << " nodes " << _num_nodes_searched << " nps " << _num_nodes_searched / time_passed << " time " << time_passed << " pv " << get_pv_line() << endl;
        }
        current_depth++;
        if (score._checkmate){
            break;
        }
    // } while (current_depth < depth + 1);
    } while (current_depth < depth + 1 || (_game_phase > ENDGAME_PERCENTAGE && time_passed < 1));
    current_depth--;
    _last_predicted_score = score;
    _last_depth_searched = current_depth;
    return _pv_table[0][0];
}