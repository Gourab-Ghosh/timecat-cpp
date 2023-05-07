#ifndef _BOARD_H
#define _BOARD_H

#include <string>
#include <stack>
#include <vector>
#include <map>
#include "constants.hpp"
#include "utils.hpp"
using namespace std;

class _BoardState;

class Board{
    unordered_map<Bitboard, unsigned short int> _repetition_map;
public:
    Bitboard _pawns;
    Bitboard _knights;
    Bitboard _bishops;
    Bitboard _rooks;
    Bitboard _queens;
    Bitboard _kings;
    Bitboard _occupied;
    Bitboard _black_occupied;
    Bitboard _white_occupied;
    Bitboard _promoted;
    bool _turn;
    Bitboard _castling_rights;
    Square _ep_square;
    unsigned short int _fullmove_number;
    unsigned short int _halfmove_clock;
    unsigned char _white_castling_status; // 1 if kingside else 2
    unsigned char _black_castling_status; // 1 if kingside else 2
    unsigned long long _transposition_key;
    Bitboard _checkers;
    bool _chess960;
    stack<Move> _move_stack;
    stack<_BoardState> _stack;
    Board(const string &fen = "", bool chess960 = false);
    unsigned long long generate_transposition_key();
    void set_fen(string fen);
    static bool is_variant_end(); // empty function
    static bool is_variant_win(); // empty function
    static bool is_variant_loss(); // empty function
    static bool is_variant_draw(); // empty function
    Bitboard occupied_co(bool color) const;
    void _clear_board();
    PieceType _remove_piece_at(Square square);
    void _set_piece_at(Square square, PieceType piece_type, bool color, bool promoted = false);
    void set_turn(bool turn);
    void swap_turn();
    string board_fen(bool promoted = false) const;
    void _set_board_fen(string fen);
    void _set_castling_fen(string castling_fen);
    void clear_stack();
    void reset_board();
    string get_checkers_squares();
    string string_representation(bool color = true, Bitboard hilight_bb = 0, bool use_unicode = false, bool invert_color = INVERT_UNICODE_COLOR) const;
    string string_unicode_representation(bool color = true, Bitboard hilight_bb = 0, bool invert_color = INVERT_UNICODE_COLOR) const;
    void print_board(bool color = true, bool use_unicode = false);
    void print_unicode_board(bool color = true);
    bool is_check();
    Bitboard _attackers_mask(bool color, Square square, Bitboard occupied) const;
    Bitboard attackers_mask(bool color, Square square);
    Bitboard get_least_attackers_mask(Square square);
    bool _attacked_for_king(Bitboard path, Bitboard occupied);
    Bitboard clean_castling_rights();
    Move _from_chess960(bool chess960, Square from_square, Square to_square, PieceType promotion = 0, PieceType drop = 0) const;
    Move _to_chess960(const Move &move) const;
    vector<Move> generate_castling_moves(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    Bitboard _attacks_mask(Square square, Bitboard occupied) const;
    Bitboard attacks_mask(Square square);
    vector<Move> generate_pseudo_legal_ep(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    vector<Move> generate_pseudo_legal_moves(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    vector<Move> generate_legal_checks(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    string castling_xfen();
    string get_fen(bool promoted = false);
    PieceType piece_type_at(Square square) const;
    bool color_at(Square square) const;
    Piece piece_at(Square square) const;
    Square find_king_square(bool color) const;
    Bitboard _slider_blockers(Square king);
    vector<Move> _generate_evasions(Square king, Bitboard checkers, Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    bool is_castling(const Move &move);
    bool is_kingside_castling(const Move &move);
    bool is_queenside_castling(const Move &move);
    bool is_attacked_by(bool color, Square square);
    bool is_en_passant(const Move &move) const;
    bool _ep_skewered(Square king, Square capturer);
    Bitboard pin_mask(bool color, Square square) const;
    bool is_pinned(bool color, Square square) const;
    bool _is_safe(Square king, Bitboard blockers, const Move &move);
    vector<Move> generate_legal_moves(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    _BoardState _board_state();
    bool is_zeroing(const Move &move);
    void increase_repetition_map(unsigned short int increment = 1);
    void decrease_repetition_map(unsigned short int decrement = 1);
    unsigned short int get_repetition_count();
    void update_checkers();
    static void _push_capture(const Move &move, Square capture_square, PieceType piece_type, bool was_promoted); // empty function
    void push(Move move);
    Move pop();
    bool is_capture(const Move &move);
    Square get_capture_piece_square(const Move &move);
    PieceType get_capture_piece_type(const Move &move);
    vector<Move> generate_pseudo_legal_captures(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    bool has_castling_rights(bool color);
    bool is_into_check(const Move &move);
    vector<Move> generate_legal_ep(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    vector<Move> generate_legal_captures(Bitboard from_mask = BB_ALL, Bitboard to_mask = BB_ALL);
    bool _is_halfmoves(unsigned short int n);
    bool is_seventyfive_moves();
    bool _reduces_castling_rights(const Move &move);
    bool has_legal_en_passant();
    bool is_irreversible(const Move &move);
    bool is_repetition(unsigned short int count = 3);
    bool is_threefold_repetition();
    bool is_fivefold_repetition();
    bool is_fifty_moves();
    bool can_claim_fifty_moves();
    bool can_claim_threefold_repetition();
    unsigned char outcome(bool claim_draw = false); // not implemented completely
    bool is_game_over(bool claim_draw = false);
    bool has_insufficient_material(bool color) const;
    bool is_insufficient_material() const;
    bool is_checkmate();
    Bitboard pieces_mask(PieceType piece_type) const;
    Bitboard pieces_mask(PieceType piece_type, bool color) const;
    bool is_passed_pawn(Square square, bool color) const;
    string _algebraic_without_suffix(const Move &move, bool _long = false);
    string _algebraic_and_push(const Move &move, bool _long = false);
    string _algebraic(const Move &move, bool _long = false);
    string san(const Move &move);
    string san_and_push(const Move &move);
    Board copy_board(bool copy_stack = true) const;
    bool is_pseudo_legal(const Move &move);
    bool is_legal(const Move &move);
    string variation_san(vector<Move> variation) const;
    string game_pgn() const;
    Move parse_san(const string &san_string);
    Move push_san(const string &san_string);
    string uci(const Move &move) const;
    Move parse_uci(const string &uci);
    Move push_uci(const string &uci);
};

Board RANDOM_BOARD;

class _BoardState{
public:
    Bitboard _pawns;
    Bitboard _knights;
    Bitboard _bishops;
    Bitboard _rooks;
    Bitboard _queens;
    Bitboard _kings;
    Bitboard _occupied_w;
    Bitboard _occupied_b;
    Bitboard _occupied;
    Bitboard _promoted;
    bool _turn;
    Bitboard _castling_rights;
    Square _ep_square;
    unsigned short int _fullmove_number;
    unsigned short int _halfmove_clock;
    unsigned char _white_castling_status;
    unsigned char _black_castling_status;
    unsigned long long _transposition_key;
    Bitboard _checkers;
    _BoardState(const Board &board = RANDOM_BOARD);
    PieceType piece_type_at(Square square) const;
    void restore(Board &board) const;
};

class Perft{
    // struct VectorHasher{
    //     size_t operator()(const vector<Bitboard> &V) const{
    //         Bitboard x;
    //         Bitboard hash = V.size();
    //         for (auto i = V.begin(); i != V.end(); i++){
    //             x = *i;
    //             x = ((x >> 16) ^ x) * 0x45d9f3b;
    //             x = ((x >> 16) ^ x) * 0x45d9f3b;
    //             x = (x >> 16) ^ x;
    //             hash ^= x + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    //         }
    //         return hash;
    //     }
    // };
    // unordered_map<vector<Bitboard>, Bitboard, VectorHasher> _dict;

public:
    Board *_board_pointer;
    map<Bitboard, Bitboard> _dict;
    bool _enable_transposition_table;
    Perft(Board &board = RANDOM_BOARD, bool enable_transposition_table = true);
    unsigned long long perft(unsigned short int depth, bool print = true);
    unsigned long long nps(unsigned short int depth, bool print = false); // nodes per second
};

#endif