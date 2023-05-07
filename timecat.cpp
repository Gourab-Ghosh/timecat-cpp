#include <numeric>
#include <chrono>
#include <random>
#include <cmath>
#include <sstream>
#include <cctype>
#include <string>
#include <map>
#include <stdio.h>
#include <unordered_map>
#include <list>
#include <stack>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
using namespace std::chrono;
#define Square unsigned int
const bool DEBUG = true;
string COLOR_RESET = "\033[0m";
string COLOR_BLACK = "\033[30m";      /* Black */
string COLOR_RED = "\033[31m";      /* Red */
string COLOR_GREEN = "\033[32m";      /* Green */
string COLOR_YELLOW = "\033[33m";      /* Yellow */
string COLOR_BLUE = "\033[34m";      /* Blue */
string COLOR_MAGENTA = "\033[35m";      /* Magenta */
string COLOR_CYAN = "\033[36m";      /* Cyan */
string COLOR_WHITE = "\033[37m";      /* White */
string COLOR_BOLDBLACK = "\033[1m\033[30m";      /* Bold Black */
string COLOR_BOLDRED = "\033[1m\033[31m";      /* Bold Red */
string COLOR_BOLDGREEN = "\033[1m\033[32m";      /* Bold Green */
string COLOR_BOLDYELLOW = "\033[1m\033[33m";      /* Bold Yellow */
string COLOR_BOLDBLUE = "\033[1m\033[34m";      /* Bold Blue */
string COLOR_BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
string COLOR_BOLDCYAN = "\033[1m\033[36m";      /* Bold Cyan */
string COLOR_BOLDWHITE = "\033[1m\033[37m";      /* Bold White */
string NO_COLOR = "";
const string STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
unsigned long long BB_SQUARES[64];
unsigned long long BB_RANKS[8];
unsigned long long BB_FILES[8];
unsigned long long BB_EMPTY = 0;
unsigned long long BB_ALL = 0xffffffffffffffff;
unsigned long long BB_LIGHT_SQUARES = 0x55aa55aa55aa55aa;
unsigned long long BB_DARK_SQUARES = 0xaa55aa55aa55aa55;
unsigned long long BB_CORNERS;
unsigned long long BB_CENTER;
unsigned long long BB_BACKRANKS;
unsigned long long BB_BLACK_SQUARES = 0xaa55aa55aa55aa55;
unsigned long long BB_WHITE_SQUARES = 0x55aa55aa55aa55aa;
unsigned long long BB_UPPER_HALF_BOARD = 0xffffffff00000000;
unsigned long long BB_LOWER_HALF_BOARD = 0x00000000ffffffff;
unsigned long long BB_LEFT_HALF_BOARD = 0xf0f0f0f0f0f0f0f0;
unsigned long long BB_RIGHT_HALF_BOARD = 0x0f0f0f0f0f0f0f0f;
unsigned int A1;
unsigned int B1;
unsigned int C1;
unsigned int D1;
unsigned int E1;
unsigned int F1;
unsigned int G1;
unsigned int H1;
unsigned int A2;
unsigned int B2;
unsigned int C2;
unsigned int D2;
unsigned int E2;
unsigned int F2;
unsigned int G2;
unsigned int H2;
unsigned int A3;
unsigned int B3;
unsigned int C3;
unsigned int D3;
unsigned int E3;
unsigned int F3;
unsigned int G3;
unsigned int H3;
unsigned int A4;
unsigned int B4;
unsigned int C4;
unsigned int D4;
unsigned int E4;
unsigned int F4;
unsigned int G4;
unsigned int H4;
unsigned int A5;
unsigned int B5;
unsigned int C5;
unsigned int D5;
unsigned int E5;
unsigned int F5;
unsigned int G5;
unsigned int H5;
unsigned int A6;
unsigned int B6;
unsigned int C6;
unsigned int D6;
unsigned int E6;
unsigned int F6;
unsigned int G6;
unsigned int H6;
unsigned int A7;
unsigned int B7;
unsigned int C7;
unsigned int D7;
unsigned int E7;
unsigned int F7;
unsigned int G7;
unsigned int H7;
unsigned int A8;
unsigned int B8;
unsigned int C8;
unsigned int D8;
unsigned int E8;
unsigned int F8;
unsigned int G8;
unsigned int H8;
unsigned long long BB_A1;
unsigned long long BB_B1;
unsigned long long BB_C1;
unsigned long long BB_D1;
unsigned long long BB_E1;
unsigned long long BB_F1;
unsigned long long BB_G1;
unsigned long long BB_H1;
unsigned long long BB_A2;
unsigned long long BB_B2;
unsigned long long BB_C2;
unsigned long long BB_D2;
unsigned long long BB_E2;
unsigned long long BB_F2;
unsigned long long BB_G2;
unsigned long long BB_H2;
unsigned long long BB_A3;
unsigned long long BB_B3;
unsigned long long BB_C3;
unsigned long long BB_D3;
unsigned long long BB_E3;
unsigned long long BB_F3;
unsigned long long BB_G3;
unsigned long long BB_H3;
unsigned long long BB_A4;
unsigned long long BB_B4;
unsigned long long BB_C4;
unsigned long long BB_D4;
unsigned long long BB_E4;
unsigned long long BB_F4;
unsigned long long BB_G4;
unsigned long long BB_H4;
unsigned long long BB_A5;
unsigned long long BB_B5;
unsigned long long BB_C5;
unsigned long long BB_D5;
unsigned long long BB_E5;
unsigned long long BB_F5;
unsigned long long BB_G5;
unsigned long long BB_H5;
unsigned long long BB_A6;
unsigned long long BB_B6;
unsigned long long BB_C6;
unsigned long long BB_D6;
unsigned long long BB_E6;
unsigned long long BB_F6;
unsigned long long BB_G6;
unsigned long long BB_H6;
unsigned long long BB_A7;
unsigned long long BB_B7;
unsigned long long BB_C7;
unsigned long long BB_D7;
unsigned long long BB_E7;
unsigned long long BB_F7;
unsigned long long BB_G7;
unsigned long long BB_H7;
unsigned long long BB_A8;
unsigned long long BB_B8;
unsigned long long BB_C8;
unsigned long long BB_D8;
unsigned long long BB_E8;
unsigned long long BB_F8;
unsigned long long BB_G8;
unsigned long long BB_H8;
unsigned long long BB_FILE_A;
unsigned long long BB_FILE_B;
unsigned long long BB_FILE_C;
unsigned long long BB_FILE_D;
unsigned long long BB_FILE_E;
unsigned long long BB_FILE_F;
unsigned long long BB_FILE_G;
unsigned long long BB_FILE_H;
unsigned long long BB_RANK_1;
unsigned long long BB_RANK_2;
unsigned long long BB_RANK_3;
unsigned long long BB_RANK_4;
unsigned long long BB_RANK_5;
unsigned long long BB_RANK_6;
unsigned long long BB_RANK_7;
unsigned long long BB_RANK_8;
char PIECE_SYMBOLS[7];
map<char, string> UNICODE_PIECE_SYMBOLS;
bool INVERT_UNICODE_COLOR = true;
unsigned long long BB_KNIGHT_ATTACKS[64];
unsigned long long BB_KING_ATTACKS[64];
unsigned long long BB_PAWN_ATTACKS[2][64];
unsigned long long BB_DIAG_MASKS[64];
unsigned long long BB_FILE_MASKS[64];
unsigned long long BB_RANK_MASKS[64];
map<unsigned long long, unsigned long long> BB_DIAG_ATTACKS[64];
map<unsigned long long, unsigned long long> BB_FILE_ATTACKS[64];
map<unsigned long long, unsigned long long> BB_RANK_ATTACKS[64];
unsigned long long BB_RAYS[64][64];
string FILE_NAMES[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
string RANK_NAMES[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
string SQUARE_NAMES[64];
unsigned int SQUARES_180[64];
unsigned long long CENTER_SQUARES_BB = 0x0000001818000000;
unsigned long long PSEUDO_CENTER_SQUARES_BB = 0X00003C24243C0000;
unsigned long long ADJACENT_FILE_MASKS[64];
unsigned long long PASSED_PAWN_MASKS[2][64];
map<unsigned long long, unsigned int> OLD_MSB_MAP;
unsigned int NUM_TO_BITS[65536];
const Square NO_SQUARE = 0xff;
unsigned long long ZOBRIST_PIECE_KEY[2][7][64];
unsigned long long ZOBRIST_ENPASSANT_KEY[NO_SQUARE + 1];
unsigned long long ZOBRIST_CASTLING_KEY[64];
unsigned long long ZOBRIST_TURN_KEY;
template <typename T> string to_str(const T& t){ 
    ostringstream os;
    os<<t;
    return os.str();
}
void raise_error();
string hexadeimal(unsigned long long key);
double interpolate(double start, double end, double alpha);
double inverse_interpolate(double start, double end, double value);
double match_interpolate(double new_start, double new_end, double old_start, double old_end, double old_value);
unsigned long long rand_64();
Square square_file(Square square);
Square square_rank(Square square);
Square square_distance(unsigned int a, unsigned int b);
unsigned int rank_file_distance_sum(unsigned int a, unsigned int b);
unsigned long long sliding_attacks(Square square, unsigned long long occupied, int deltas[], unsigned int size);
unsigned long long step_attacks(Square square, int deltas[], unsigned int size);
unsigned long long ray(unsigned int a, unsigned int b);
unsigned long long get_surrounding_mask(Square square);
unsigned long long flip_vertical(unsigned long long bb);
unsigned long long flip_horizontal(unsigned long long bb);
unsigned int popcount(unsigned long long bb);
unsigned int lsb(unsigned long long bb);
unsigned int msb(unsigned long long bb);
unsigned long long between(unsigned int a, unsigned int b);
Square square_mirror(Square square);
void handle_fen_exceptions(const string &board_part, const string &turn_part, const string &castling_part, const string &ep_part, const string &halfmove_part, const string &fullmove_part, const string &remaining_part);
unsigned long long adjacet_file_mask(Square square);
unsigned long long passed_mask(bool color, Square square);
int index(string *arr_pointer, const string &elem, unsigned int size);
int index(char *arr_pointer, const char &elem, unsigned int size);
int index(int *arr_pointer, const int &elem, unsigned int size);
string color_output(string s, const string &color = NO_COLOR);
string color_output(char c, const string &color = NO_COLOR);
class Move{
public:
    unsigned char _from_square;
    unsigned char _to_square;
    unsigned char _promotion;
    unsigned char _drop;
    Move(unsigned int from = 0, unsigned int to = 0, unsigned int promotion = 0, unsigned int drop = 0);
    static Move from_uci(string uci);
    string uci() const;
    bool is_valid() const;
    static Move null();
    static Move from_hash(unsigned int hash);
    unsigned int get_hash() const;
    bool operator == (Move move) const;
    bool operator != (Move move) const;
};
ostream& operator << (ostream &os, Move move);
class Piece{
public:
    unsigned int _type;
    bool _color;
    Piece(unsigned int type, bool color);
    char symbol() const;
    string unicode_symbol(bool invert_color = INVERT_UNICODE_COLOR) const;
    static Piece from_symbol(char s);
};
class SquareSet{
    unsigned long long _bb;
    unsigned long long _bb_temp;
public:
    SquareSet(unsigned long long bb = 0);
    unsigned int start();
    void next(unsigned int &i);
    bool squares_left() const;
    void setbb(unsigned long long bb);
    void reset();
    vector<unsigned int> get_vector();
    string visualize();
};
class TranspositionKeyCounter{
    unordered_map<unsigned long long, unsigned int> _counter_table;
public:
    int _start;
    TranspositionKeyCounter(int start = 0);
    void update(unsigned long long key);
    int get_count(unsigned long long key);
};
class Score{
public:
    bool _is_invalid;
    double _normal;
    char _checkmate;
    char _infinity;
    Score(double score = 0, unsigned int type = 1);
    Score get_copy() const;
    unsigned int get_mate_in_score() const;
    bool operator == (const Score &score) const;
    bool operator != (const Score &score) const;
    bool operator > (const Score &score) const;
    bool operator >= (const Score &score) const;
    bool operator < (const Score &score) const;
    bool operator <= (const Score &score) const;
    Score operator + (const Score &score) const;
    void operator += (Score score);
    Score operator - () const;
    Score operator - (const Score &score) const;
    void operator -= (Score score);
    bool operator == (double score) const;
    bool operator != (double score) const;
    bool operator > (double score) const;
    bool operator < (double score) const;
    bool operator >= (double score) const;
    bool operator <= (double score) const;
    Score operator + (double score) const;
    void operator += (double score);
    Score operator - (double score) const;
    void operator -= (double score);
    Score operator * (double d) const;
    void operator *= (double d);
    Score operator / (double d) const;
    void operator /= (double d);
    string str();
};
ostream& operator << (ostream &os, Score score);
Score abs(Score score);
struct TranspositionData{
    unsigned char _depth;
    unsigned char _flag;
    Score _score;
    Move _best_move;
};
void update_transposition_data(TranspositionData &transposition_data, unsigned int depth, unsigned int flag, const Score &score, const Move &best_move);
const double pieces_unordered_mapping[2][7][64] = {
    {
        {
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
        },
        { // pawn
             0,   0,   0,   0,   0,   0,   0,   0,
            -4,  68,  61,  47,  47,  49,  45,  -1,
             6,  16,  25,  33,  24,  24,  14,  -6,
             0,  -1,   9,  28,  20,   8,  -1,  11,
             6,   4,   6,  14,  14,  -5,   6,  -6,
            -1,  -8,  -4,   4,   2, -12,  -1,   5,
             5,  16,  16, -14, -14,  13,  15,   8,
             0,   0,   0,   0,   0,   0,   0,   0,
        },
        { // knight
            -55, -40, -30, -28, -26, -30, -40, -50,
            -37, -15,   0,  -6,   4,   3, -17, -40,
            -25,   5,  16,  12,  11,   6,   6, -29,
            -24,   5,  21,  14,  18,   9,  11, -26,
            -36,  -5,   9,  23,  24,  21,   2, -24,
            -32,  -1,   4,  19,  20,   4,  11, -25,
            -38, -22,   4,  -1,   8,  -5, -18, -34,
            -50, -46, -32, -24, -36, -25, -34, -50,
        },
        { // bishop
            -16, -15, -12,  -5, -10, -12, -10, -20,
            -13,   5,   6,   1,  -6,  -5,   3,  -6,
            -16,   6,  -1,  16,   7,  -1,  -6,  -5,
            -14,  -1,  11,  14,   4,  10,  11, -13,
             -4,   5,  12,  16,   4,   6,   2, -16,
            -15,   4,  14,   8,  16,   4,  16, -15,
             -5,   6,   6,   6,   3,   6,   9,  -7,
            -14,  -4, -15,  -4,  -9,  -4, -12, -14,
        },
        { // rook
              5,  -2,   6,   2,  -2,  -6,   4,  -2,
              8,  13,  11,  15,  11,  15,  16,   4,
             -6,   3,   3,   6,   1,  -2,   3,  -5,
            -10,   5,  -4,  -4,  -1,  -6,   3,  -2,
             -4,   3,   5,  -2,   4,   1,  -5,   1,
              0,   1,   1,  -3,   5,   6,   1,  -9,
            -10,  -1,  -4,   0,   5,  -6,  -6,  -9,
             -1,  -2,  -6,   9,   9,   5,   4,  -5,
        },
        { // queen
            -25,  -9, -11,  -3,  -7, -13, -10, -17,
             -4,  -6,   4,  -5,  -1,   6,   4,  -5,
             -8,  -5,   2,   0,   7,   6,  -4,  -5,
              0,  -4,   7,  -1,   7,  11,   0,   1,
             -6,   4,   7,   1,  -1,   2,  -6,  -2,
            -15,  11,  11,  11,   4,  11,   6, -15,
             -5,  -6,   1,  -6,   3,  -3,   3, -10,
            -15,  -4, -13,  -8,  -3, -16,  -8, -24,
        },
        { // king
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -37, -43, -49, -50, -39, -40, -30,
            -32, -41, -40, -46, -49, -40, -46, -30,
            -32, -38, -39, -52, -54, -39, -39, -30,
            -20, -33, -29, -42, -44, -29, -30, -19,
            -10, -18, -17, -20, -22, -21, -20, -13,
             14,  18,  -1,  -1,   4,  -1,  15,  14,
             21,  35,  11,   6,   1,  14,  32,  22,
        },
    },
    {
        {
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
              0,   0,   0,   0,   0,   0,   0,   0,
        },
        { // pawn
             0,   0,   0,   0,   0,   0,   0,   0,
            -4, 174, 120,  94,  85,  98,  68,   4,
             6,  48,  44,  45,  31,  38,  37,  -6,
            -6,  -4,  -1,  -6,   2,  -1,  -2,  -2,
             2,   2,   5,  -3,   0,  -5,   4,  -3,
            -2,   0,   1,   5,   0,  -1,   0,   1,
            -2,   5,   6,  -6,   0,   3,   4,  -4,
             0,   0,   0,   0,   0,   0,   0,   0,
        },
        { // knight
            -50, -40, -30, -24, -24, -35, -40, -50,
            -38, -17,   6,  -5,   5,  -4, -15, -40,
            -24,   3,  15,   9,  15,  10,  -6, -26,
            -29,   5,  21,  17,  18,   9,  10, -28,
            -36,  -5,  18,  16,  14,  20,   5, -26,
            -32,   7,   5,  20,  11,  15,   9, -27,
            -43, -20,   5,  -1,   5,   1, -22, -40,
            -50, -40, -32, -27, -30, -25, -35, -50,
        },
        { // bishop
            -14, -13,  -4,  -7, -14,  -9, -16, -20,
            -11,   6,   3,  -6,   4,  -3,   5,  -4,
            -11,  -3,   5,  15,   4,  -1,  -5, -10,
             -7,  -1,  11,  16,   5,  11,   7, -13,
             -4,   4,  10,  16,   6,  12,   4, -16,
             -4,   4,  11,  12,  10,   7,   7, -12,
            -11,   7,   6,   6,  -3,   2,   1,  -7,
            -15,  -4, -11,  -4, -10, -10,  -6, -17,
        },
        { // rook
              5,  -6,   1,  -4,  -4,  -6,   6,  -3,
             -6,   4,   2,   5,  -1,   3,   4, -15,
            -15,   3,   3,   0,  -1,  -6,   5,  -9,
            -16,   6,   0,  -6,  -3,  -3,  -4,  -4,
            -15,   6,   2,  -6,   6,   0,  -6, -10,
             -6,  -1,   3,  -2,   6,   5,   0, -15,
             -8,  -4,   1,  -4,   3,  -5,  -6,  -5,
              1,   0,  -2,   1,   1,   4,   2,   0,
        },
        { // queen
            -21,  -7,  -6,   1,  -8, -15, -10, -16,
             -4,  -5,   3,  -4,   2,   6,   3, -10,
            -13,  -2,   7,   2,   6,  10,  -4,  -6,
             -1,  -4,   3,   1,   8,   8,  -2,  -2,
              0,   6,   8,   1,  -1,   1,   0,  -3,
            -11,  10,   6,   3,   7,   9,   4, -10,
            -12,  -6,   5,   0,   0,  -5,   4, -10,
            -20,  -6,  -7,  -7,  -4, -12,  -9, -20,
        },
        { // king
            -50, -40, -30, -20, -20, -30, -40, -50,
            -30, -18, -15,   6,   3,  -6, -24, -30,
            -35, -16,  20,  32,  34,  14, -11, -30,
            -34,  -5,  24,  35,  34,  35, -16, -35,
            -36,  -7,  31,  34,  34,  34, -12, -31,
            -30,  -7,  14,  33,  36,  16, -13, -33,
            -36, -27,   5,   2,   5,  -1, -31, -33,
            -48, -26, -26, -26, -28, -25, -30, -51,
        },
    },
};
const unsigned int HASH_EXACT = 1;
const unsigned int HASH_ALPHA = 2;
const unsigned int HASH_BETA = 3;
double TRANSITION_PHASE_PERCENT = 0.1;
const double mvv_lva[7][7] = {
    {0.00,      0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
    {0.00,      1.05, 2.05, 3.05, 4.05, 5.05, 6.05},
    {0.00,      1.04, 2.04, 3.04, 4.04, 5.04, 6.04},
    {0.00,      1.03, 2.03, 3.03, 4.03, 5.03, 6.03},
    {0.00,      1.02, 2.02, 3.02, 4.02, 5.02, 6.02},
    {0.00,      1.01, 2.01, 3.01, 4.01, 5.01, 6.01},
    {0.00,      1.00, 2.00, 3.00, 4.00, 5.00, 6.00},
};
const double opening_pieces_unordered_mapping_weights[7] = {1, 1, 1, 1, 1, 1, 1};
const double endgame_pieces_unordered_mapping_weights[7] = {1, 1, 1, 1, 1, 1, 1};
const double material_weights[7] = {0, 1, 3, 3, 5, 9, 200};
const double opening_material_weights[7] = {0, 0.89, 3.08, 3.19, 4.88, 8.88, 200.01};
const double endgame_material_weights[7] = {0, 0.96, 3.19, 3.31, 4.97, 8.53, 199.98};
const int MAX_DEPTH = 64;
const Score inf = Score(1, 3);
const Score DRAW_POINT = Score(-50);
const Score INVALID_SCORE = Score(0, 0);
const double MOBILITY_ADVANTAGE_PERCENTAGE = 0.2;
const double PINNED_PENALTY_PERCENTAGE = 0.2;
const double BAD_BISHOP_PENALTY_PERCENTAGE = 0.4;
const double PASSED_PAWN_ADVANTAGE_PERCENTAGE = 1;
const double OPENING_PERCENTAGE = 0.2;
const double ENDGAME_PERCENTAGE = 0.6;
const int NUM_KILLER_MOVES = 5;
const int T_TABLE_MIN_DEPTH = 1;
const bool DISABLE_T_TABLE = false;
const bool ENABLE_CHECK_EXTENSION = true;
const Score PVS_CUTOFF = Score(1);
const Score ASPIRATION_WINDOW_CUTOFF = Score(50);
const unsigned int FULL_DEPTH_SEARCH_LMR = 5;
const unsigned int REDUCTION_LIMIT_LMR = 3;
const unsigned int NULL_MOVE_REDUCTION_LIMIT = 2;
class _BoardState;
class Board{
    unordered_map<unsigned long long, unsigned int> _repetition_map;
public:
    unsigned long long _pawns;
    unsigned long long _knights;
    unsigned long long _bishops;
    unsigned long long _rooks;
    unsigned long long _queens;
    unsigned long long _kings;
    unsigned long long _occupied;
    unsigned long long _black_occupied;
    unsigned long long _white_occupied;
    unsigned long long _promoted;
    bool _turn;
    unsigned long long _castling_rights;
    unsigned int _ep_square;
    unsigned int _fullmove_number;
    unsigned int _halfmove_clock;
    int _white_castling_status; // 1 if kingside else 2
    int _black_castling_status; // 1 if kingside else 2
    unsigned long long _transposition_key;
    unsigned long long _checkers;
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
    unsigned long long occupied_co(bool color) const;
    void _clear_board();
    int _remove_piece_at(Square square);
    void _set_piece_at(Square square, int piece_type, bool color, bool promoted = false);
    void set_turn(bool turn);
    void swap_turn();
    string board_fen(bool promoted = false) const;
    void _set_board_fen(string fen);
    void _set_castling_fen(string castling_fen);
    void clear_stack();
    void reset_board();
    string get_checkers_squares();
    string string_representation(bool color = true, unsigned long long hilight_bb = 0, bool use_unicode = false, bool invert_color = INVERT_UNICODE_COLOR) const;
    string string_unicode_representation(bool color = true, unsigned long long hilight_bb = 0, bool invert_color = INVERT_UNICODE_COLOR) const;
    void print_board(bool color = true, bool use_unicode = false);
    void print_unicode_board(bool color = true);
    bool is_check();
    unsigned long long attackers_mask(bool color, Square square);
    unsigned long long _attackers_mask(bool color, Square square, unsigned long long occupied) const;
    bool _attacked_for_king(unsigned long long path, unsigned long long occupied);
    unsigned long long clean_castling_rights();
    Move _from_chess960(bool chess960, unsigned int from_square, unsigned int to_square, unsigned int promotion = 0, unsigned int drop = 0) const;
    Move _to_chess960(const Move &move) const;
    vector<Move> generate_castling_moves(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    unsigned long long _attacks_mask(Square square, unsigned long long occupied) const;
    unsigned long long attacks_mask(Square square);
    vector<Move> generate_pseudo_legal_ep(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    vector<Move> generate_pseudo_legal_moves(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    vector<Move> generate_legal_checks(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    string castling_xfen();
    string get_fen(bool promoted = false);
    int piece_type_at(Square square) const;
    bool color_at(Square square) const;
    Piece piece_at(Square square) const;
    unsigned int find_king_square(bool color) const;
    unsigned long long _slider_blockers(int king);
    vector<Move> _generate_evasions(int king, unsigned long long checkers, unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    bool is_castling(const Move &move);
    bool is_kingside_castling(const Move &move);
    bool is_queenside_castling(const Move &move);
    bool is_attacked_by(bool color, Square square);
    bool is_en_passant(const Move &move) const;
    bool _ep_skewered(int king, int capturer);
    unsigned long long pin_mask(bool color, Square square) const;
    bool is_pinned(bool color, Square square) const;
    bool _is_safe(unsigned int king, unsigned long long blockers, const Move &move);
    vector<Move> generate_legal_moves(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    _BoardState _board_state();
    bool is_zeroing(const Move &move);
    void increase_repetition_map(unsigned int increment = 1);
    void decrease_repetition_map(unsigned int decrement = 1);
    unsigned int get_repetition_count();
    void update_checkers();
    static void _push_capture(const Move &move, int capture_square, int piece_type, bool was_promoted); // empty function
    void push(Move move);
    Move pop();
    bool is_capture(const Move &move);
    unsigned int get_capture_piece_square(const Move &move);
    unsigned int get_capture_piece_type(const Move &move);
    vector<Move> generate_pseudo_legal_captures(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    bool has_castling_rights(bool color);
    bool is_into_check(const Move &move);
    vector<Move> generate_legal_ep(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    vector<Move> generate_legal_captures(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    bool _is_halfmoves(unsigned int n);
    bool is_seventyfive_moves();
    bool _reduces_castling_rights(const Move &move);
    bool has_legal_en_passant();
    bool is_irreversible(const Move &move);
    bool is_repetition(unsigned int count = 3);
    bool is_threefold_repetition();
    bool is_fivefold_repetition();
    bool is_fifty_moves();
    bool can_claim_fifty_moves();
    bool can_claim_threefold_repetition();
    unsigned int outcome(bool claim_draw = false); // not implemented completely
    bool is_game_over(bool claim_draw = false);
    bool has_insufficient_material(bool color) const;
    bool is_insufficient_material() const;
    bool is_checkmate();
    unsigned long long pieces_mask(unsigned int piece_type, bool color) const;
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
    unsigned long long _pawns;
    unsigned long long _knights;
    unsigned long long _bishops;
    unsigned long long _rooks;
    unsigned long long _queens;
    unsigned long long _kings;
    unsigned long long _occupied_w;
    unsigned long long _occupied_b;
    unsigned long long _occupied;
    unsigned long long _promoted;
    bool _turn;
    unsigned long long _castling_rights;
    unsigned int _ep_square;
    unsigned int _fullmove_number;
    unsigned int _halfmove_clock;
    int _white_castling_status;
    int _black_castling_status;
    unsigned long long _transposition_key;
    unsigned long long _checkers;
    _BoardState(const Board &board = RANDOM_BOARD);
    int piece_type_at(Square square) const;
    void restore(Board &board) const;
};
class Perft{
public:
    Board *_board_pointer;
    map<unsigned long long, unsigned long long> _dict;
    bool _enable_transposition_table;
    Perft(Board &board = RANDOM_BOARD, bool enable_transposition_table = true);
    unsigned long long perft(int depth, bool print = true);
    unsigned long long nps(int depth, bool print = false); // nodes per second
};
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
    double evaluate_piece(unsigned int piece_type) const;
    double evaluate_piece_position(unsigned int piece_type, bool color, Square square);
    double evaluate_piece_at(int piece_type, bool color, Square square, unsigned long long mobility_mask = BB_ALL);
    static unsigned long long get_king_side_board_mask(unsigned int king_file);
    bool is_uncovered_king(bool color, Square square);
    double evaluate_king_safety(unsigned int white_king_square, unsigned int black_king_square, unsigned int white_king_rank, unsigned int black_king_rank, unsigned int white_king_file, unsigned int black_king_file, double material_score);
    static double evaluate_king_endgame_forcing_checkmate(unsigned int white_king_square, unsigned int black_king_square, unsigned int white_king_rank, unsigned int black_king_rank, unsigned int white_king_file, unsigned int black_king_file, double material_score);
    double evaluate_rook_position(int white_king_square, int black_king_square, int white_king_rank, int black_king_rank, int white_king_file, int black_king_file);
    double evaluate_pawn_structures();
    double evaluate_opening_board(bool print_scores_seperately = false);
    double evaluate_midgame_board(bool print_scores_seperately = false);
    double evaluate_endgame_board(bool print_scores_seperately = false);
    Score evaluate_board(bool reverse_score = false, bool print_scores_seperately = false);
};
class Engine{
    unordered_map<unsigned long long, TranspositionData> _transposition_table;
    list<unsigned long long> _transposition_table_keys;
    unsigned long long max_keys_in_t_table = 100000;
    unordered_map<unsigned int, double> _random_move_values;
    time_point<system_clock> _clock_start;
    stack<double> _game_phase_stack;
public:
    unsigned long long _num_nodes_searched;
    int _ply;
    unsigned int _pv_length[MAX_DEPTH];
    Move _pv_table[MAX_DEPTH][MAX_DEPTH];
    bool _follow_pv;
    bool _score_pv;
    Score _last_predicted_score;
    Move _killer_moves[NUM_KILLER_MOVES][MAX_DEPTH];
    double _history_moves[7][2][64];
    unsigned int _last_depth_searched;
    bool _self_color;
    double _game_phase;
    Board *board;
    BoardEvaluator evaluator;
    Engine(Board &board = RANDOM_BOARD);
    void set_fen(const string &fen);
    void reset_variables();
    void update_killer_moves(Move killer_move);
    Score evaluate_board(bool reverse_score = true, bool print_scores_seperately = false);
    Score read_transposition_table(const Score &alpha, const Score &beta, const unsigned long long &key, Move &best_move, unsigned int depth = 0);
    void write_transposition_table(unsigned int flag, const Score &score, const unsigned long long &key, const Move &best_move = Move::null(), unsigned int depth = 0);
    vector<Move> get_ordered_moves(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL, const Move &best_move = Move::null());
    vector<Move> get_ordered_captures(unsigned long long from_mask = BB_ALL, unsigned long long to_mask = BB_ALL);
    void enable_pv_scoring(const vector<Move> &moves);
    Score get_game_over_score(unsigned int outcome, const Score &current_evaluation) const;
    bool can_apply_lmr(const Move &move) const;
    void update_pv_table(const Move &move);
    void update_game_phase();
    void push(Move move);
    Move pop();
    double calculate_time_passed() const;
    void reset_clock();
    bool is_time_out(double time_left) const;
    Move get_best_move(unsigned int depth, bool print = true);
    string get_pv_line(bool san = true);
    double move_value(const Move &move, bool allow_pv_scoring = true, const Move &best_move = Move::null());
    Score alpha_beta(unsigned int depth, Score alpha = -inf, Score beta = inf, bool apply_null_move = true);
    double see(Square square);
    Score quiescence(Score alpha, Score beta);
};
void initialize_squares(){
    BB_SQUARES[0] = 1;
    for (unsigned int i = 1; i < 64; i++){
        BB_SQUARES[i] = 2*BB_SQUARES[i-1];
    }
}
void initialize_ranks(){
    BB_RANKS[0] = 0xff;
    for (unsigned int i = 1; i < 8; i++){
        BB_RANKS[i] = 256*BB_RANKS[i-1];
    }
}
void initialize_files(){
    for (unsigned int i = 0; i < 8; i++){
        BB_FILES[i] = 0x0101010101010101 << i;
    }
}
unsigned long long _edges(Square square){
    return (((BB_RANK_1 | BB_RANK_8) & ~BB_RANKS[square_rank(square)]) | ((BB_FILE_A | BB_FILE_H) & ~BB_FILES[square_file(square)]));
}
map<unsigned long long, unsigned long long>* _attack_table(int deltas[], int size){
    map<unsigned long long, unsigned long long>* attack_table = new map<unsigned long long, unsigned long long>[64];
    for (Square square = 0; square < 64; square++){
        map<unsigned long long, unsigned long long> attacks;
        unsigned long long mask = sliding_attacks(square, 0, deltas, size) & ~_edges(square);
        unsigned long long subset = 0;
        while (true){
            attacks[subset] = sliding_attacks(square, subset, deltas, size);
            subset = (subset - mask) & mask;
            if (!(subset)){
                break;
            }
        }
        attack_table[square] = attacks;
    }
    return attack_table;
}
int _old_popcount(unsigned long long bb){
    int c = 0;
    while (bb){
        bb &= (bb - 1);
        c++;
    }
    return c;
}
void assign_variable_values(){
    A1 = 0;
    B1 = 1;
    C1 = 2;
    D1 = 3;
    E1 = 4;
    F1 = 5;
    G1 = 6;
    H1 = 7;
    A2 = 8;
    B2 = 9;
    C2 = 10;
    D2 = 11;
    E2 = 12;
    F2 = 13;
    G2 = 14;
    H2 = 15;
    A3 = 16;
    B3 = 17;
    C3 = 18;
    D3 = 19;
    E3 = 20;
    F3 = 21;
    G3 = 22;
    H3 = 23;
    A4 = 24;
    B4 = 25;
    C4 = 26;
    D4 = 27;
    E4 = 28;
    F4 = 29;
    G4 = 30;
    H4 = 31;
    A5 = 32;
    B5 = 33;
    C5 = 34;
    D5 = 35;
    E5 = 36;
    F5 = 37;
    G5 = 38;
    H5 = 39;
    A6 = 40;
    B6 = 41;
    C6 = 42;
    D6 = 43;
    E6 = 44;
    F6 = 45;
    G6 = 46;
    H6 = 47;
    A7 = 48;
    B7 = 49;
    C7 = 50;
    D7 = 51;
    E7 = 52;
    F7 = 53;
    G7 = 54;
    H7 = 55;
    A8 = 56;
    B8 = 57;
    C8 = 58;
    D8 = 59;
    E8 = 60;
    F8 = 61;
    G8 = 62;
    H8 = 63;
    BB_A1 = BB_SQUARES[0];
    BB_B1 = BB_SQUARES[1];
    BB_C1 = BB_SQUARES[2];
    BB_D1 = BB_SQUARES[3];
    BB_E1 = BB_SQUARES[4];
    BB_F1 = BB_SQUARES[5];
    BB_G1 = BB_SQUARES[6];
    BB_H1 = BB_SQUARES[7];
    BB_A2 = BB_SQUARES[8];
    BB_B2 = BB_SQUARES[9];
    BB_C2 = BB_SQUARES[10];
    BB_D2 = BB_SQUARES[11];
    BB_E2 = BB_SQUARES[12];
    BB_F2 = BB_SQUARES[13];
    BB_G2 = BB_SQUARES[14];
    BB_H2 = BB_SQUARES[15];
    BB_A3 = BB_SQUARES[16];
    BB_B3 = BB_SQUARES[17];
    BB_C3 = BB_SQUARES[18];
    BB_D3 = BB_SQUARES[19];
    BB_E3 = BB_SQUARES[20];
    BB_F3 = BB_SQUARES[21];
    BB_G3 = BB_SQUARES[22];
    BB_H3 = BB_SQUARES[23];
    BB_A4 = BB_SQUARES[24];
    BB_B4 = BB_SQUARES[25];
    BB_C4 = BB_SQUARES[26];
    BB_D4 = BB_SQUARES[27];
    BB_E4 = BB_SQUARES[28];
    BB_F4 = BB_SQUARES[29];
    BB_G4 = BB_SQUARES[30];
    BB_H4 = BB_SQUARES[31];
    BB_A5 = BB_SQUARES[32];
    BB_B5 = BB_SQUARES[33];
    BB_C5 = BB_SQUARES[34];
    BB_D5 = BB_SQUARES[35];
    BB_E5 = BB_SQUARES[36];
    BB_F5 = BB_SQUARES[37];
    BB_G5 = BB_SQUARES[38];
    BB_H5 = BB_SQUARES[39];
    BB_A6 = BB_SQUARES[40];
    BB_B6 = BB_SQUARES[41];
    BB_C6 = BB_SQUARES[42];
    BB_D6 = BB_SQUARES[43];
    BB_E6 = BB_SQUARES[44];
    BB_F6 = BB_SQUARES[45];
    BB_G6 = BB_SQUARES[46];
    BB_H6 = BB_SQUARES[47];
    BB_A7 = BB_SQUARES[48];
    BB_B7 = BB_SQUARES[49];
    BB_C7 = BB_SQUARES[50];
    BB_D7 = BB_SQUARES[51];
    BB_E7 = BB_SQUARES[52];
    BB_F7 = BB_SQUARES[53];
    BB_G7 = BB_SQUARES[54];
    BB_H7 = BB_SQUARES[55];
    BB_A8 = BB_SQUARES[56];
    BB_B8 = BB_SQUARES[57];
    BB_C8 = BB_SQUARES[58];
    BB_D8 = BB_SQUARES[59];
    BB_E8 = BB_SQUARES[60];
    BB_F8 = BB_SQUARES[61];
    BB_G8 = BB_SQUARES[62];
    BB_H8 = BB_SQUARES[63];
    BB_FILE_A = BB_FILES[0];
    BB_FILE_B = BB_FILES[1];
    BB_FILE_C = BB_FILES[2];
    BB_FILE_D = BB_FILES[3];
    BB_FILE_E = BB_FILES[4];
    BB_FILE_F = BB_FILES[5];
    BB_FILE_G = BB_FILES[6];
    BB_FILE_H = BB_FILES[7];
    BB_RANK_1 = BB_RANKS[0];
    BB_RANK_2 = BB_RANKS[1];
    BB_RANK_3 = BB_RANKS[2];
    BB_RANK_4 = BB_RANKS[3];
    BB_RANK_5 = BB_RANKS[4];
    BB_RANK_6 = BB_RANKS[5];
    BB_RANK_7 = BB_RANKS[6];
    BB_RANK_8 = BB_RANKS[7];
    BB_CORNERS = BB_A1 | BB_H1 | BB_A8 | BB_H8;
    BB_CENTER = BB_D4 | BB_E4 | BB_D5 | BB_E5;
    BB_BACKRANKS = BB_RANK_1 | BB_RANK_8;
    PIECE_SYMBOLS[0] = ' ';
    PIECE_SYMBOLS[1] = 'p';
    PIECE_SYMBOLS[2] = 'n';
    PIECE_SYMBOLS[3] = 'b';
    PIECE_SYMBOLS[4] = 'r';
    PIECE_SYMBOLS[5] = 'q';
    PIECE_SYMBOLS[6] = 'k';
    UNICODE_PIECE_SYMBOLS[PIECE_SYMBOLS[0]] = " ";
    UNICODE_PIECE_SYMBOLS['R'] = "♖";
    UNICODE_PIECE_SYMBOLS['N'] = "♘";
    UNICODE_PIECE_SYMBOLS['B'] = "♗";
    UNICODE_PIECE_SYMBOLS['Q'] = "♕";
    UNICODE_PIECE_SYMBOLS['K'] = "♔";
    UNICODE_PIECE_SYMBOLS['P'] = "♙";
    UNICODE_PIECE_SYMBOLS['r'] = "♜";
    UNICODE_PIECE_SYMBOLS['n'] = "♞";
    UNICODE_PIECE_SYMBOLS['b'] = "♝";
    UNICODE_PIECE_SYMBOLS['q'] = "♛";
    UNICODE_PIECE_SYMBOLS['k'] = "♚";
    UNICODE_PIECE_SYMBOLS['p'] = "♟";
    int arbl1[8] = {17, 15, 10, 6, -17, -15, -10, -6};  // KNIGHT ATTACKS
    int arbl2[8] = {9, 8, 7, 1, -9, -8, -7, -1};  // KING ATTACKS
    int arbl3[2] = {-7, -9};  // PAWN ATTACKS
    int arbl4[2] = {7, 9};  // PAWN ATTACKS
    int arbl5[4] = {-9, -7, 7, 9};  // DIAG ATTACKS
    int arbl6[2] = {-8, 8};  // FILE ATTACKS
    int arbl7[2] = {-1, 1};  // RANK ATTACKS
    for (Square sq = 0; sq < 64; sq++){
        BB_KNIGHT_ATTACKS[sq] = step_attacks(sq, arbl1, 8);
        BB_KING_ATTACKS[sq] = step_attacks(sq, arbl2, 8);
        BB_PAWN_ATTACKS[0][sq] = step_attacks(sq, arbl3, 2);
        BB_PAWN_ATTACKS[1][sq] = step_attacks(sq, arbl4, 2);
    }
    map<unsigned long long, unsigned long long> * bb_diag_attacks = _attack_table(arbl5, 4);
    map<unsigned long long, unsigned long long> * bb_file_attacks = _attack_table(arbl6, 2);
    map<unsigned long long, unsigned long long> * bb_rank_attacks = _attack_table(arbl7, 2);
    for (Square square = 0; square < 64; square++){
        BB_DIAG_ATTACKS[square] = bb_diag_attacks[square];
        BB_FILE_ATTACKS[square] = bb_file_attacks[square];
        BB_RANK_ATTACKS[square] = bb_rank_attacks[square];
        BB_DIAG_MASKS[square] = BB_DIAG_ATTACKS[square][0] & ~_edges(square);
        BB_FILE_MASKS[square] = BB_FILE_ATTACKS[square][0] & ~_edges(square);
        BB_RANK_MASKS[square] = BB_RANK_ATTACKS[square][0] & ~_edges(square);
    }
    for (unsigned int a = 0; a < 64; a++){
        unsigned long long bb_a = BB_SQUARES[a];
        for (unsigned int b = 0; b < 64; b++){
            unsigned long long bb_b = BB_SQUARES[b];
            if (BB_DIAG_ATTACKS[a][0] & bb_b){
                BB_RAYS[a][b] = (BB_DIAG_ATTACKS[a][0] & BB_DIAG_ATTACKS[b][0]) | bb_a | bb_b;
            }else if (BB_RANK_ATTACKS[a][0] & bb_b){
                BB_RAYS[a][b] = BB_RANK_ATTACKS[a][0] | bb_a;
            }else if (BB_FILE_ATTACKS[a][0] & bb_b){
                BB_RAYS[a][b] = BB_FILE_ATTACKS[a][0] | bb_a;
            }else {
                BB_RAYS[a][b] = BB_EMPTY;
            }
        }
    }
    for (unsigned int rank = 0; rank < 8; rank++){
        for (unsigned int file = 0; file < 8; file++){
            SQUARE_NAMES[8*rank+file] = FILE_NAMES[file] + RANK_NAMES[rank];
        }
    }
    for (Square square = 0; square < 64; square++){
        SQUARES_180[square] = square_mirror(square);
        ADJACENT_FILE_MASKS[square] = adjacet_file_mask(square);
        PASSED_PAWN_MASKS[0][square] = passed_mask(false, square);
        PASSED_PAWN_MASKS[1][square] = passed_mask(true, square);
    }
    unsigned long long arb_var = 1;
    for (unsigned int i = 0; i < 64; i++){
        OLD_MSB_MAP[arb_var] = i;
        arb_var <<= 1;
    }
    for (unsigned long long i = 0; i < 65536; i++){
        NUM_TO_BITS[i] = _old_popcount(i);
    }
    for (Square square = 0; square < 64; square++){
        for (unsigned int color = 0; color < 2; color++){
            for (unsigned int piece_type = 0; piece_type < 7; piece_type++){
                ZOBRIST_PIECE_KEY[color][piece_type][square] = piece_type ? rand_64() : 0;
            }
        }
        ZOBRIST_CASTLING_KEY[square] = 0;
    }
    for (Square square = 0; square <= NO_SQUARE; square++){
        ZOBRIST_ENPASSANT_KEY[square] = (square < 64 || square == NO_SQUARE) ? rand_64() : 0;
    }
    for (unsigned int castling_square : {A1, H1, A8, H8}){
        ZOBRIST_CASTLING_KEY[castling_square] = rand_64();
    }
    ZOBRIST_TURN_KEY = rand_64();
}
void initialize_constants(){
    initialize_squares();
    initialize_ranks();
    initialize_files();
    assign_variable_values();
}
void raise_error(){
    throw 0;
}
string hexadeimal(unsigned long long key){
    ostringstream os;
    os << hex << key;
    string hex_str = os.str();
    transform(hex_str.begin(), hex_str.end(), hex_str.begin(), ::toupper);
    return hex_str;
}
double interpolate(double start, double end, double alpha){
    return (1 - alpha) * start + alpha * end;
}
double inverse_interpolate(double start, double end, double value){
    if (DEBUG){
        if (start == end){
            cout << "start and end value can not be ame in inverse_interpolate!" << endl;
            raise_error();
        }
    }
    return (value - start) / (end - start);
}
double match_interpolate(double new_start, double new_end, double old_start, double old_end, double old_value){
    return interpolate(new_start, new_end, inverse_interpolate(old_start, old_end, old_value));
}
unsigned long long rand_64(){
    return (unsigned long long)rand() << 32 | rand();
}
Square square_file(Square square){return square & 7;}
Square square_rank(Square square){return square >> 3;}
Square square_distance(unsigned int a, unsigned int b){
    unsigned int file_a = square_file(a);
    unsigned int file_b = square_file(b);
    unsigned int rank_a = square_rank(a);
    unsigned int rank_b = square_rank(b);
    unsigned int file_distance;
    if (file_a > file_b){
        file_distance = file_a - file_b;
    } else{
        file_distance = file_b - file_a;
    }
    unsigned int rank_distance;
    if (rank_a > rank_b){
        rank_distance = rank_a - rank_b;
    } else{
        rank_distance = rank_b - rank_a;
    }
    if (file_distance > rank_distance){
        return file_distance;
    }
    return rank_distance;
}
unsigned int rank_file_distance_sum(unsigned int a, unsigned int b){
    unsigned int file_a = square_file(a);
    unsigned int file_b = square_file(b);
    unsigned int rank_a = square_rank(a);
    unsigned int rank_b = square_rank(b);
    unsigned int file_distance;
    if (file_a > file_b){
        file_distance = file_a - file_b;
    } else{
        file_distance = file_b - file_a;
    }
    unsigned int rank_distance;
    if (rank_a > rank_b){
        rank_distance = rank_a - rank_b;
    } else{
        rank_distance = rank_b - rank_a;
    }
    return rank_distance + file_distance;
}
int index(string *arr_pointer, const string &elem, unsigned int size){
    const auto &arr = arr_pointer;
    for (unsigned int i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}
int index(char *arr_pointer, const char &elem, unsigned int size){
    const auto &arr = arr_pointer;
    for (unsigned int i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}
int index(int *arr_pointer, const int &elem, unsigned int size){
    const auto &arr = arr_pointer;
    for (unsigned int i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}
unsigned long long sliding_attacks(Square square, unsigned long long occupied, int deltas[], unsigned int size){
    unsigned long long attacks = BB_EMPTY;
    for (unsigned int i = 0; i < size; i++){
        int delta = deltas[i];
        Square sq = square;
        while (true){
            sq += delta;
            if (!(sq < 64) || square_distance(sq, sq - delta) > 2){
                break;
            }
            attacks |= BB_SQUARES[sq];
            if (occupied & BB_SQUARES[sq]){
                break;
            }
        }
    }
    return attacks;
}
unsigned long long step_attacks(Square square, int deltas[], unsigned int size){return sliding_attacks(square, BB_ALL, deltas, size);}
unsigned long long ray(unsigned int a, unsigned int b){return BB_RAYS[a][b];}
unsigned long long get_surrounding_mask(Square square){
    unsigned long long surrounding_mask = 0;
    for (int offset: {-9, -8, -7, -1, 0, 1, 7, 8, 9}){
        unsigned int offset_square = square + offset;
        if (offset_square < 64){
            surrounding_mask |= BB_SQUARES[offset_square];
        }
    }
    return surrounding_mask;
}
unsigned long long flip_vertical(unsigned long long bb){
    bb = ((bb >> 8) & 0x00ff00ff00ff00ff) | ((bb & 0x00ff00ff00ff00ff) << 8);
    bb = ((bb >> 16) & 0x0000ffff0000ffff) | ((bb & 0x0000ffff0000ffff) << 16);
    bb = (bb >> 32) | ((bb & 0x00000000ffffffff) << 32);
    return bb;
}
unsigned long long flip_horizontal(unsigned long long bb){
    bb = ((bb >> 1) & 0x5555555555555555) | ((bb & 0x5555555555555555) << 1);
    bb = ((bb >> 2) & 0x3333333333333333) | ((bb & 0x3333333333333333) << 2);
    bb = ((bb >> 4) & 0x0f0f0f0f0f0f0f0f) | ((bb & 0x0f0f0f0f0f0f0f0f) << 4);
    return bb;
}
unsigned int popcount(unsigned long long bb){
    if (bb){
        return NUM_TO_BITS[bb & 0xffff] + popcount(bb >> 16);
    }
    return NUM_TO_BITS[0];
}
unsigned int lsb(unsigned long long bb){
    return msb(bb & -bb);
}
unsigned int msb(unsigned long long bb){
    bb |= (bb >> 1);
    bb |= (bb >> 2);
    bb |= (bb >> 4);
    bb |= (bb >> 8);
    bb |= (bb >> 16);
    bb |= (bb >> 32);
    bb &= ~(bb >> 1);
    return OLD_MSB_MAP[bb];
}
unsigned long long between(unsigned int a, unsigned int b){
    unsigned long long bb = BB_RAYS[a][b] & ((BB_ALL << a) ^ (BB_ALL << b));
    return bb & (bb - 1);
}
Square square_mirror(Square square){
    return square ^ 0x38;
}
void handle_fen_exceptions(const string &board_part, const string &turn_part, const string &castling_part, const string &ep_part, const string &halfmove_part, const string &fullmove_part, const string &remaining_part){}
unsigned long long adjacet_file_mask(Square square){
    unsigned int file = square_file(square);
    if (!(file)){
        return BB_FILES[1];
    } else if (file == 7){
        return BB_FILES[6];
    }
    return BB_FILES[file - 1] | BB_FILES[file + 1];
}
unsigned long long passed_mask(bool color, Square square){
    unsigned int rank = square_rank(square);
    if (color){
        if (rank == 7){
            return 0;
        }
    } else{
        if (!(rank)){
            return 0;
        }
    }
    unsigned long long file_mask = adjacet_file_mask(square) | BB_FILES[square_file(square)];
    unsigned long long upper_rank_mask = 0;
    unsigned int iterator_start;
    unsigned int iterator_end;
    if (color){
        iterator_start = rank + 1;
        iterator_end = 8;
    } else{
        iterator_start = 0;
        iterator_end = rank;
    }
    for (unsigned int i = iterator_start; i < iterator_end; i++){
        upper_rank_mask |= BB_RANKS[i];
    }
    unsigned long long mask = file_mask & upper_rank_mask;
    return mask;
}
string color_output(string s, const string &color){
    if (color == NO_COLOR){
        return s;
    }
    return color + s + COLOR_RESET;
}
string color_output(char c, const string &color){
    if (color == NO_COLOR){
        return to_str(c);
    }
    return color + to_str(c) + COLOR_RESET;
}
Move::Move(unsigned int from, unsigned int to, unsigned int promotion, unsigned int drop){
    if (DEBUG){
        if (from > 63 || to > 63 || promotion > 6 || drop > 6){
            cout << "invalid arguments in Move initializer" << endl;
            cout << "_from_square = " << _from_square << endl;
            cout << "_to_square = " << _to_square << endl;
            cout << "_promotion = " << _promotion << endl;
            cout << "_drop = " << _drop << endl;
            raise_error();
        }
    }
    _from_square = from;
    _to_square = to;
    _promotion = promotion;
    _drop = drop;
}
Move Move::from_uci(string uci){
    if (uci == "0000"){
        return null();
    } else if (uci.size() == 4 && uci[1] == '@'){
        char promotion_char = tolower(uci[0]);
        int drop = index(PIECE_SYMBOLS, promotion_char, 7);
        Square square = index(SQUARE_NAMES, uci.substr(2), 64);
        return Move(square, square, 0, drop);
    } else if (uci.size() == 4 || uci.size() == 5){
        int from_square = index(SQUARE_NAMES, uci.substr(0, 2), 64);
        int to_square = index(SQUARE_NAMES, uci.substr(2, 2), 64);
        int promotion;
        if (uci.size() == 5){
            promotion = index(PIECE_SYMBOLS, uci[4], 7);
        } else{
            promotion = 0;
        }
        if (from_square == to_square){
            cout << "invalid uci (use 0000 for null moves): " << uci << endl;
            raise_error();
        }
        return Move(from_square, to_square, promotion, 0);
    }
    else{
        cout << "expected uci string to be of length 4 or 5: " << uci << endl;
        raise_error();
        return Move::null();
    }
}
string Move::uci() const{
    if (_drop){
        string s = "";
        s += toupper(PIECE_SYMBOLS[_drop]);
        s += "@";
        s += SQUARE_NAMES[_to_square];
        return s;
    } else  if (_promotion){
        return SQUARE_NAMES[_from_square] + SQUARE_NAMES[_to_square] + PIECE_SYMBOLS[_promotion];
    } else if (is_valid()){
        return SQUARE_NAMES[_from_square] + SQUARE_NAMES[_to_square];
    } else{
        return "0000";
    }
}
Move Move::null(){
    return Move(0, 0);
}
bool Move::is_valid() const{
    return _from_square | _to_square | _promotion | _drop;
}
Move Move::from_hash(unsigned int hash){
    Move move;
    move._drop = hash & 7;
    hash >>= 3;
    move._promotion = hash & 7;
    hash >>= 3;
    move._to_square = hash & 63;
    move._from_square = hash >> 6;
    return move;
}
unsigned int Move::get_hash() const{
    unsigned int hash = _from_square;
    hash <<= 6;
    hash |= _to_square;
    hash <<= 3;
    hash |= _promotion;
    hash <<= 3;
    hash |= _drop;
    return hash;
}
bool Move::operator == (Move move) const{
    if (_from_square == move._from_square){
        if (_to_square == move._to_square){
            if (_promotion == move._promotion){
                if (_drop == move._drop){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Move::operator != (Move move) const{
    if (_from_square != move._from_square){
        return true;
    }
    if (_to_square != move._to_square){
        return true;
    }
    if (_promotion != move._promotion){
        return true;
    }
    if (_drop != move._drop){
        return true;
    }
    return false;
}
ostream& operator << (ostream &os, Move move){
    os << "Move::from_uci(\"" << move.uci() << "\")";
    return os;
}
Piece::Piece(unsigned int type, bool color){
    _type = type;
    _color = color;
}
char Piece::symbol() const{
    char s = PIECE_SYMBOLS[_type];
    if (_color){
        s = toupper(s);
    } else{
        s = tolower(s);
    }
    return s;
}
string Piece::unicode_symbol(bool invert_color) const{
    char s = symbol();
    if (invert_color){
        if (isupper(s)){
            s = tolower(s);
        }else {
            s = toupper(s);
        }
    }
    return UNICODE_PIECE_SYMBOLS[s];
}
Piece Piece::from_symbol(char s){
    for (int type = 1; type < 7; type++){
        if (tolower(s) == PIECE_SYMBOLS[type]){
            return Piece(type, isupper(s));
        }
    }
    return Piece(0, true);
}
SquareSet::SquareSet(unsigned long long bb){
    _bb = bb;
    _bb_temp = bb;
}
unsigned int SquareSet::start(){
    int i = 0;
    while (!(_bb_temp & 1)&&_bb_temp){
        _bb_temp >>= 1;
        i++;
    };
    return i;
}
void SquareSet::next(unsigned int &i){
    do{
        _bb_temp >>= 1;
        i++;
    } while (!(_bb_temp & 1)&&_bb_temp);
}
bool SquareSet::squares_left() const{
    return _bb_temp;
}
void SquareSet::setbb(unsigned long long bb){
    _bb = bb;
    _bb_temp = bb;
}
void SquareSet::reset(){
    _bb_temp = _bb;
}
string SquareSet::visualize(){
    unsigned long long flipped = flip_horizontal(_bb);
    string s = "";
    for (Square square = 63; square < 64; square--){
        if (flipped & BB_SQUARES[square]){
            s += 'x';
        } else{
            s += '.';
        }
        if (square){
            if (!(square & 7)){
                s += "\n";
            }else {
                s += " ";
            }
        }
    }
    return s;
}
vector<unsigned int> SquareSet::get_vector(){
    vector<unsigned int> integers_vector;
    for (unsigned  int i = start(); squares_left(); next(i)){
        integers_vector.push_back(i);
    }
    return integers_vector;
}
TranspositionKeyCounter::TranspositionKeyCounter(int start){
    _start = start;
}
void TranspositionKeyCounter::update(unsigned long long key){
    if (_counter_table.find(key) != _counter_table.end()){
        _counter_table[key] = 1;
    } else{
        _counter_table[key] += 1;
    }
}
int TranspositionKeyCounter::get_count(unsigned long long key){
    return _counter_table[key];
}
Score::Score(double score, unsigned int type){
    if (type){
        _is_invalid = false;
        _normal = 0;
        _checkmate = 0;
        _infinity = 0;
        if (type == 1){
            _normal = score;
        } else if (type == 2){
            _checkmate = round(score);
        } else if (type == 3){
            _infinity = score;
        }
    } else{
        _is_invalid = true;
    }
}
Score Score::get_copy() const{
    Score n_score(0, 0);
    n_score._is_invalid = _is_invalid;
    n_score._normal = _normal;
    n_score._checkmate = _checkmate;
    n_score._infinity = _infinity;
    return n_score;
}
unsigned int Score::get_mate_in_score() const{
    if (DEBUG){
        if (_infinity){
            cout << "You can call Score::get_mate_in_score() only for chekmate scores!";
            raise_error();
        }
    }
    unsigned int mate_in = abs(_checkmate);
    if (mate_in & 1){
        return (mate_in + 1) / 2;
    }
    return mate_in / 2;
}
bool Score::operator == (const Score &score) const{
    if (_is_invalid || score._is_invalid){
        return _is_invalid == score._is_invalid;
    }
    return _normal == score._normal && _infinity == score._infinity && _checkmate == score._checkmate;
}
bool Score::operator != (const Score &score) const{
    return !(*this == score);
}
bool Score::operator > (const Score &score) const{
    if (DEBUG){
        if (_is_invalid || score._is_invalid){
            cout << "Operations >, >=, <, <= not defined for invalid scores" << endl;
            raise_error();
        }
    }
    if (_infinity != score._infinity){
        return _infinity > score._infinity;
    }
    if (_checkmate != score._checkmate){
        if ((_checkmate > 0 && score._checkmate > 0) || (_checkmate < 0 && score._checkmate < 0)){
            return _checkmate < score._checkmate;
        }
        return _checkmate > score._checkmate;
    }
    if (_normal != score._normal){
        return _normal > score._normal;
    }
    return false;
}
bool Score::operator >= (const Score &score) const{
    return *this == score || *this > score;
}
bool Score::operator < (const Score &score) const{
    return !(*this >= score);
}
bool Score::operator <= (const Score &score) const{
    return !(*this > score);
}
Score Score::operator + (const Score &score) const{
    Score n_score = get_copy();
    n_score += score;
    return n_score;
}
void Score::operator += (Score score){
    if (DEBUG){
        if (_is_invalid || score._is_invalid){
            cout << "Operations +, +=, -, -=, *, *=, /, /= not defined for invalid scores" << endl;
            raise_error();
        }
    }
    _normal += score._normal;
    _checkmate += score._checkmate;
    _infinity += score._infinity;
}
Score Score::operator - () const{
    if (DEBUG){
        if (_is_invalid){
            cout << "Negative of invalid score is not defined" << endl;
            raise_error();
        }
    }
    Score n_score(0, 0);
    n_score._is_invalid = _is_invalid;
    n_score._normal = -_normal;
    n_score._checkmate = -_checkmate;
    n_score._infinity = -_infinity;
    return n_score;
}
Score Score::operator - (const Score &score) const{
    Score n_score = get_copy();
    n_score -= score;
    return n_score;
}
void Score::operator -= (Score score){
    if (DEBUG){
        if (_is_invalid || score._is_invalid){
            cout << "Operations +, +=, -, -=, *, *=, /, /= not defined for invalid scores" << endl;
            raise_error();
        }
    }
    _normal -= score._normal;
    _checkmate -= score._checkmate;
    _infinity -= score._infinity;
}
bool Score::operator == (double score) const{
    return _normal == score && !(_infinity) && !(_checkmate);
}
bool Score::operator != (double score) const{
    return _normal != score || _infinity != 0 || _checkmate != 0;
}
bool Score::operator > (double score) const{
    if (_infinity || _checkmate){
        return _infinity > 0 || _checkmate > 0;
    }
    return _normal > score;
}
bool Score::operator < (double score) const{
    return !(*this >= score);
}
bool Score::operator >= (double score) const{
    return *this == score || *this > score;
}
bool Score::operator <= (double score) const{
    return !(*this > score);
}
Score Score::operator + (double score) const{
    Score n_score = get_copy();
    n_score += score;
    return n_score;
}
void Score::operator += (double score){
    if (DEBUG){
        if (_is_invalid){
            cout << "Operations +, +=, -, -=, *, *=, /, /= not defined for invalid scores" << endl;
            raise_error();
        }
    }
    _normal += score;
}
Score Score::operator - (double score) const{
    Score n_score = get_copy();
    n_score -= score;
    return n_score;
}
void Score::operator -= (double score){
    *this += -score;
}
Score Score::operator * (double d) const{
    Score n_score = get_copy();
    n_score *= d;
    return n_score;
}
void Score::operator *= (double d){
    if (DEBUG){
        if (_is_invalid){
            cout << "Operations +, +=, -, -=, *, *=, /, /= not defined for invalid scores" << endl;
            raise_error();
        }
        if (_checkmate){
            cout << "Operations *, *=, /, /= not defined for checkmate scores" << endl;
            raise_error();
        }
    }
    _normal *= d;
    _infinity *= d;
}
Score Score::operator / (double d) const{
    Score n_score = get_copy();
    n_score /= d;
    return n_score;
}
void Score::operator /= (double d){
    if (DEBUG){
        if (_is_invalid){
            cout << "Operations +, +=, -, -=, *, *=, /, /= not defined for invalid scores" << endl;
            raise_error();
        }
        if (_checkmate){
            cout << "Operations *, *=, /, /= not defined for checkmate scores" << endl;
            raise_error();
        }
    }
    _normal /= d;
    _infinity /= d;
}
string Score::str(){
    if (_is_invalid){
        return "INVALID SCORE";
    }
    if (_infinity){
        if (_infinity < 0){
            return "-INF";
        }
        return "INF";
    }
    if (_checkmate){
        if (_checkmate < 0){
            return "-M" + to_str(get_mate_in_score());
        }
        return "M" + to_str(get_mate_in_score());
    }
    return to_str(_normal / 100);
}
ostream& operator << (ostream &os, Score score){
    os << score.str();
    return os;
}
Score abs(Score score){
    if (score < 0){
        return -score;
    }
    return score;
}
void update_transposition_data(TranspositionData &transposition_data, unsigned int depth, unsigned int flag, const Score &score, const Move &best_move){
    transposition_data._depth = depth;
    transposition_data._flag = flag;
    transposition_data._score = score;
    transposition_data._best_move = best_move;
}
_BoardState::_BoardState(const Board &board){
    _pawns = board._pawns;
    _knights = board._knights;
    _bishops = board._bishops;
    _rooks = board._rooks;
    _queens = board._queens;
    _kings = board._kings;
    _occupied_w = board._white_occupied;
    _occupied_b = board._black_occupied;
    _occupied = board._occupied;
    _promoted = board._promoted;
    _turn = board._turn;
    _castling_rights = board._castling_rights;
    _ep_square = board._ep_square;
    _fullmove_number = board._fullmove_number;
    _halfmove_clock = board._halfmove_clock;
    _white_castling_status = board._white_castling_status;
    _black_castling_status = board._black_castling_status;
    _transposition_key = board._transposition_key;
    _checkers = board._checkers;
}
void _BoardState::restore(Board &board) const{
    board._pawns = _pawns;
    board._knights = _knights;
    board._bishops = _bishops;
    board._rooks = _rooks;
    board._queens = _queens;
    board._kings = _kings;
    board._white_occupied = _occupied_w;
    board._black_occupied = _occupied_b;
    board._occupied = _occupied;
    board._promoted = _promoted;
    board._turn = _turn;
    board._castling_rights = _castling_rights;
    board._ep_square = _ep_square;
    board._fullmove_number = _fullmove_number;
    board._halfmove_clock = _halfmove_clock;
    board._white_castling_status = _white_castling_status;
    board._black_castling_status = _black_castling_status;
    board._transposition_key = _transposition_key;
    board._checkers = _checkers;
}
int _BoardState::piece_type_at(Square square) const{
    unsigned long long bb = BB_SQUARES[square];
    if (bb & _pawns){
        return 1;
    } else if (bb & _knights){
        return 2;
    } else if (bb & _bishops){
        return 3;
    } else if (bb & _rooks){
        return 4;
    } else if (bb & _queens){
        return 5;
    } else if (bb & _kings){
        return 6;
    } else {
        return 0;
    }
}
bool Board::is_variant_end(){return false;}
bool Board::is_variant_win(){return false;}
bool Board::is_variant_loss(){return false;}
bool Board::is_variant_draw(){return false;}
unsigned long long Board::occupied_co(bool color) const{
    if (color){
        return _white_occupied;
    }
    return _black_occupied;
}
Board::Board(const string &fen, bool chess960){
    if (fen.empty()){
        reset_board();
    } else{
        set_fen(fen);
    }
    _chess960 = chess960;
}
unsigned long long Board::generate_transposition_key(){
    unsigned long long t_key = 0;
    for (unsigned int color = 0; color < 2; color++){
        for (unsigned int piece_type = 1; piece_type < 7; piece_type++){
            unsigned long long piece_mask = pieces_mask(piece_type, color);
            SquareSet pieces_squareset(piece_mask);
            for (Square square = pieces_squareset.start(); pieces_squareset.squares_left(); pieces_squareset.next(square)){
                t_key ^= ZOBRIST_PIECE_KEY[color][piece_type][square];
            }
        }
    }
    SquareSet castling_squareset(_castling_rights);
    for (Square square = castling_squareset.start(); castling_squareset.squares_left(); castling_squareset.next(square)){
        t_key ^= ZOBRIST_CASTLING_KEY[square];
    }
    t_key ^= ZOBRIST_ENPASSANT_KEY[_ep_square];
    if (_turn){
        t_key ^= ZOBRIST_TURN_KEY;
    }
    return t_key;
}
void Board::_clear_board(){
    _pawns = BB_EMPTY;
    _knights = BB_EMPTY;
    _bishops = BB_EMPTY;
    _rooks = BB_EMPTY;
    _queens = BB_EMPTY;
    _kings = BB_EMPTY;
    _promoted = BB_EMPTY;
    _white_occupied = BB_EMPTY;
    _black_occupied = BB_EMPTY;
    _occupied = BB_EMPTY;
    _transposition_key = 0;
    _checkers = 0;
    clear_stack();
}
int Board::_remove_piece_at(Square square){
    unsigned int piece_type = piece_type_at(square);
    unsigned long long mask = BB_SQUARES[square];
    switch (piece_type){
        case 1:
            _pawns ^= mask;
            break;
        case 2:
            _knights ^= mask;
            break;
        case 3:
            _bishops ^= mask;
            break;
        case 4:
            _rooks ^= mask;
            break;
        case 5:
            _queens ^= mask;
            break;
        case 6:
            _kings ^= mask;
            break;
        default:
            return 0;
    }
    _occupied ^= mask;
    _transposition_key ^= ZOBRIST_PIECE_KEY[int(color_at(square))][piece_type][square];
    _white_occupied &= ~mask;
    _black_occupied &= ~mask;
    _promoted &= ~mask;
    return piece_type;
}
void Board::_set_piece_at(Square square, int piece_type, bool color, bool promoted){
    _remove_piece_at(square);
    unsigned long long mask = BB_SQUARES[square];
    switch (piece_type){
        case 1:
            _pawns |= mask;
            break;
        case 2:
            _knights |= mask;
            break;
        case 3:
            _bishops |= mask;
            break;
        case 4:
            _rooks |= mask;
            break;
        case 5:
            _queens |= mask;
            break;
        case 6:
            _kings |= mask;
            break;
        default:
            return;
    }
    _occupied ^= mask;
    _transposition_key ^= ZOBRIST_PIECE_KEY[int(color)][piece_type][square];
    if (color){
        _white_occupied ^= mask;
    } else{
        _black_occupied ^= mask;
    }
    if (promoted){
        _promoted ^= mask;
    }
}
void Board::set_turn(bool turn){
    _turn = turn;
    _transposition_key = generate_transposition_key();
}
void Board::swap_turn(){
    _turn = !(_turn);
    _transposition_key ^= ZOBRIST_TURN_KEY;
}
string Board::board_fen(bool promoted) const{
    string builder = "";
    int empty = 0;
    for (unsigned int i = 0; i < 64; i++){
        Square square = SQUARES_180[i];
        Piece piece = piece_at(square);
        if (!(piece._type)){
            empty += 1;
        } else{
            if (empty){
                builder += to_str(empty);
                empty = 0;
            }
            builder += piece.symbol();
            if (promoted && BB_SQUARES[square] & _promoted){
                builder += "~";
            }
        }
        if ((BB_SQUARES[square] & BB_FILE_H)){
            if (empty){
                builder += to_str(empty);
                empty = 0;
            }
            if (square != H1){
                builder += "/";
            }
        }
    }
    return builder;
}
void Board::_set_board_fen(string fen){
    _clear_board();
    Square square_index = 0;
    string digits = "12345678";
    string pieces ="pnbrqkPNBRQK";
    for (unsigned int i = 0; i < fen.length(); i++){
        char c = fen[i];
        if (digits.find(c) != string::npos){
            square_index += (int(c) - '0');
        } else if (pieces.find(c) != string::npos){
            Piece piece = Piece::from_symbol(c);
            _set_piece_at(SQUARES_180[square_index], piece._type, piece._color);
            square_index++;
        } else if (c == '~'){
            _promoted |= BB_SQUARES[SQUARES_180[square_index - 1]];
        }
    }
}
void Board::_set_castling_fen(string castling_fen){
    _castling_rights = BB_EMPTY;
    if (castling_fen.empty() || (castling_fen == "-")){
        return;
    }
    for (unsigned  int i = 0; i < castling_fen.length(); i++){
        char flag = castling_fen[i];
        bool color = isupper(flag);
        flag = tolower(flag);
        unsigned long long backrank = color ? BB_RANK_1 : BB_RANK_8;
        unsigned long long rooks = occupied_co(color) & _rooks & backrank;
        unsigned int king = find_king_square(color);
        if (flag == 'q'){
            if (king != NO_SQUARE && lsb(rooks) < king){
                _castling_rights |= rooks & -rooks;
            } else{
                _castling_rights |= BB_FILE_A & backrank;
            }
        } else if (flag == 'k'){
            unsigned int rook = msb(rooks);
            if (king != NO_SQUARE && king < rook){
                _castling_rights |= BB_SQUARES[rook];
            } else{
                _castling_rights |= BB_FILE_H & backrank;
            }
        } else{
            for (unsigned int j = 0; j < 8; j++){
                if (FILE_NAMES[j][0] == flag){
                    _castling_rights |= BB_FILES[j] & backrank;
                    break;
                }
            }
        }
    }
}
void Board::clear_stack(){
    while (!(_move_stack.empty())){
        _move_stack.pop();
    }
    while (!(_stack.empty())){
        _stack.pop();
    }
    _repetition_map.clear();
    increase_repetition_map();
}
string Board::castling_xfen(){
    string builder = "";
    for (int i = 1; i > -1; i--){
        bool color = bool(i);
        unsigned int king = find_king_square(color);
        if (!(king)){
            continue;
        }
        unsigned int king_file = square_file(king);
        unsigned long long backrank = color ? BB_RANK_1 : BB_RANK_8;
        SquareSet castling_squares_squarset(clean_castling_rights() & backrank);
        for (unsigned int rook_square = castling_squares_squarset.start(); castling_squares_squarset.squares_left(); castling_squares_squarset.next(rook_square)){
            unsigned int rook_file = square_file(rook_square);
            bool a_side = rook_file < king_file;
            unsigned int other_rooks = occupied_co(color) & _rooks & backrank & ~BB_SQUARES[rook_square];
            SquareSet other_rooks_squareset(other_rooks);
            char ch;
            if (a_side){
                ch = 'q';
            } else{
                ch = 'k';
            }
            for (unsigned int other = other_rooks_squareset.start(); other_rooks_squareset.squares_left(); other_rooks_squareset.next(other)){
                if ((square_file(other) < rook_file) == a_side){
                    ch = FILE_NAMES[rook_file][0];
                    break;
                }
            }
            if (color){
                ch = toupper(ch);
            }
            builder += ch;
        }
    }
    if (builder.empty()){
        return "-";
    } else{
        string chars = "KQkq";
        string fen = "";
        for (unsigned int i = 0; i < 4; i++){
            char ch = chars[i];
            for (unsigned int j = 0; j < builder.length(); j++){
                if (ch == builder[j]){
                    fen += ch;
                    break;
                }
            }
        }
        return fen;
    }
}
string Board::get_fen(bool promoted){
    string fen = board_fen(promoted) + " ";
    if (_turn){
        fen += "w ";
    } else{
        fen += "b ";
    }
    fen += castling_xfen() + " ";
    if (_ep_square == NO_SQUARE){
        fen += "- ";
    } else{
        fen += SQUARE_NAMES[_ep_square] + " ";
    }
    fen += to_str(_halfmove_clock) + " ";
    fen += to_str(_fullmove_number);
    return fen;
}
void Board::set_fen(string fen){
    string board_part = "";
    string turn_part = "";
    string castling_part = "";
    string ep_part = "";
    string halfmove_part = "";
    string fullmove_part = "";
    string remaining_part = "";
    int n = 0;
    for (unsigned int i = 0; i < fen.length(); i++){
        char c = fen[i];
        if (c == ' '){
            n++;
        } else{
            switch(n){
                case 0:
                    board_part += c;
                    break;
                case 1:
                    turn_part += c;
                    break;
                case 2:
                    castling_part += c;
                    break;
                case 3:
                    ep_part += c;
                    break;
                case 4:
                    halfmove_part += c;
                    break;
                case 5:
                    fullmove_part += c;
                    break;
                default:
                    remaining_part += c;
            }
        }
    }
    handle_fen_exceptions(board_part, turn_part, castling_part, ep_part, halfmove_part, fullmove_part, remaining_part);
    if (turn_part.empty()){
        set_turn(true);
    } else{
        if (turn_part == "w"){
            set_turn(true);
        } else if (turn_part == "b"){
            set_turn(false);
        }
    }
    if (castling_part.empty()){
        castling_part = "-";
    }   
    _ep_square = NO_SQUARE;
    if (!(ep_part.empty() || ep_part == "-")){
        for (Square square = 0; square < 64; square++){
            if (SQUARE_NAMES[square] == ep_part){
                _ep_square = square;
                break;
            }
        }
    }
    if (halfmove_part.empty()){
        _halfmove_clock = 0;
    } else{
        _halfmove_clock = stoi(halfmove_part);
    }
    if (fullmove_part.empty()){
        _fullmove_number = 1;
    } else{
        _fullmove_number = stoi(fullmove_part);
        if (_fullmove_number < 1){
            _fullmove_number = 1;
        }
    }
    _set_board_fen(board_part);
    _set_castling_fen(castling_part);
    _white_castling_status = 0;
    _black_castling_status = 0;
    _transposition_key = generate_transposition_key();
    unsigned long long king_mask = _kings & occupied_co(_turn);
    if (king_mask){
        _checkers = attackers_mask(!(_turn), msb(king_mask));
    } else{
        _checkers = 0;
    }
    clear_stack();
}
void Board::reset_board(){
    _pawns = BB_RANK_2 | BB_RANK_7;
    _knights = BB_B1 | BB_G1 | BB_B8 | BB_G8;
    _bishops = BB_C1 | BB_F1 | BB_C8 | BB_F8;
    _rooks = BB_CORNERS;
    _queens = BB_D1 | BB_D8;
    _kings = BB_E1 | BB_E8;
    _promoted = BB_EMPTY;
    _white_occupied = BB_RANK_1 | BB_RANK_2;
    _black_occupied = BB_RANK_7 | BB_RANK_8;
    _occupied = BB_RANK_1 | BB_RANK_2 | BB_RANK_7 | BB_RANK_8;
    _castling_rights = BB_A1 | BB_H1 | BB_A8 | BB_H8;
    _turn = true;
    _ep_square = NO_SQUARE;
    _halfmove_clock = 0;
    _fullmove_number = 1;
    _white_castling_status = 0;
    _black_castling_status = 0;
    _transposition_key = generate_transposition_key();
    _checkers = 0;
    clear_stack();
}
int Board::piece_type_at(Square square) const{
    unsigned long long bb = BB_SQUARES[square];
    if (bb & _pawns){
        return 1;
    } else if (bb & _knights){
        return 2;
    } else if (bb & _bishops){
        return 3;
    } else if (bb & _rooks){
        return 4;
    } else if (bb & _queens){
        return 5;
    } else if (bb & _kings){
        return 6;
    }
    return 0;
}
bool Board::color_at(Square square) const{
    return BB_SQUARES[square] & _white_occupied;
}
Piece Board::piece_at(Square square) const{
    return Piece(piece_type_at(square), color_at(square));
}
unsigned int Board::find_king_square(bool color) const{
        
        unsigned long long king_mask = occupied_co(color) & _kings & ~_promoted;
        if (king_mask){
            return msb(king_mask);
        }
        return NO_SQUARE;
}
string Board::get_checkers_squares(){
    string checkers_squares = "";
    SquareSet checkers_squareset(_checkers);
    for (Square square = checkers_squareset.start(); checkers_squareset.squares_left(); checkers_squareset.next(square)){
        checkers_squares += SQUARE_NAMES[square] + " ";
    }
    return checkers_squares;
}
string Board::string_representation(bool color, unsigned long long hilight_bb, bool use_unicode, bool invert_color) const{
    string border_color = color ? COLOR_GREEN : NO_COLOR;
    string black_piece_color = color ? COLOR_BOLDMAGENTA : NO_COLOR;
    string white_piece_color = color ? COLOR_BOLDWHITE : NO_COLOR;
    string lebel_color = color ? COLOR_BOLDRED : NO_COLOR;
    string highlight_color = color ? COLOR_BOLDYELLOW : NO_COLOR;
    string line_sep = "+---+---+---+---+---+---+---+---+";
    string s = color_output(line_sep + "\n| ", border_color);
    for (Square square = 63; square < 64; square--){
        int mirror_square = square ^ 7;
        string c = "";
        Piece piece = piece_at(mirror_square);
        if (use_unicode){
            c += piece.unicode_symbol(invert_color);
        } else{
            if (hilight_bb & BB_SQUARES[mirror_square]){
                c += color_output(piece.symbol(), highlight_color);
            } else{
                if (piece._color){
                    c += color_output(piece.symbol(), white_piece_color);
                } else{
                    c += color_output(piece.symbol(), black_piece_color);
                }
            }
        }
        s += c + color_output(" | ", border_color);
        if (!(square & 7)){
            s += color_output(to_str(square_rank(square) + 1), lebel_color);
            if (square){
                s += color_output("\n" + line_sep + "\n| ", border_color);
            }
        }
    }
    s += color_output("\n" + line_sep + "\n  ", border_color) + color_output("a   b   c   d   e   f   g   h", lebel_color);
    return s;
}
string Board::string_unicode_representation(bool color, unsigned long long hilight_bb, bool invert_color) const{
    return string_representation(color, hilight_bb, true, invert_color);
}
void Board::print_board(bool color, bool use_unicode){
    cout << string_representation(color, 0, use_unicode) << endl;
    cout << endl << "FEN: " << get_fen() << endl;
    cout << "Transposition Key: " << hexadeimal(_transposition_key) << endl;
    cout << "Checker Squares: " << get_checkers_squares() << endl;
}
void Board::print_unicode_board(bool color){
    print_board(color, true);
}
bool Board::is_check(){
    return _checkers;
}
unsigned long long Board::_attackers_mask(bool color, Square square, unsigned long long occupied) const{
    unsigned long long rank_pieces = BB_RANK_MASKS[square] & occupied;
    unsigned long long file_pieces = BB_FILE_MASKS[square] & occupied;
    unsigned long long diag_pieces = BB_DIAG_MASKS[square] & occupied;
    unsigned long long queens_and_rooks = _queens | _rooks;
    unsigned long long queens_and_bishops = _queens | _bishops;
    unsigned long long attackers = (BB_KING_ATTACKS[square] & _kings) | (BB_KNIGHT_ATTACKS[square] & _knights) | (BB_RANK_ATTACKS[square][rank_pieces] & queens_and_rooks) | (BB_FILE_ATTACKS[square][file_pieces] & queens_and_rooks) | (BB_DIAG_ATTACKS[square][diag_pieces] & queens_and_bishops) | (BB_PAWN_ATTACKS[!(color)][square] & _pawns);
    return attackers & occupied_co(color);
}
unsigned long long Board::attackers_mask(bool color, Square square){
    return _attackers_mask(color, square, _occupied);
}
bool Board::_attacked_for_king(unsigned long long path, unsigned long long occupied){
    SquareSet squareset(path);
    for (Square sq = squareset.start(); squareset.squares_left(); squareset.next(sq)){
        if (_attackers_mask(!(_turn), sq, occupied)){
            return true;
        }
    }
    return false;
}
unsigned long long Board::clean_castling_rights(){
    if (!(_stack.empty())){
        return _castling_rights;
    }
    unsigned long long castling = _castling_rights & _rooks;
    unsigned long long white_castling = castling & BB_RANK_1 & _white_occupied;
    unsigned long long black_castling = castling & BB_RANK_8 & _black_occupied;
    if (!(_chess960)){
        white_castling &= (BB_A1 | BB_H1);
        black_castling &= (BB_A8 | BB_H8);
        if (!(bool(_white_occupied & _kings & ~_promoted & BB_E1))){
            white_castling = BB_EMPTY;
        }
        if (!(bool(_black_occupied & _kings & ~_promoted & BB_E8))){
            black_castling = BB_EMPTY;
        }
        return white_castling | black_castling;
    } else{
        unsigned long long white_king_mask = _white_occupied & _kings & BB_RANK_1 & ~_promoted;
        unsigned long long black_king_mask = _black_occupied & _kings & BB_RANK_8 & ~_promoted;
        if (!(white_king_mask)){
            white_castling = BB_EMPTY;
        }
        if (!(black_king_mask)){
            black_castling = BB_EMPTY;
        }
        unsigned long long white_a_side = white_castling & -white_castling;
        unsigned long long white_h_side;
        if (white_castling){
            white_h_side = BB_SQUARES[msb(white_castling)];
        } else{
            white_h_side = BB_EMPTY;
        }
        if (bool(white_a_side) && (msb(white_a_side) > msb(white_king_mask))){
            white_a_side = BB_EMPTY;
        }
        if (bool(white_h_side) && (msb(white_h_side) < msb(white_king_mask))){
            white_h_side = BB_EMPTY;
        }
        unsigned long long black_a_side = (black_castling & -black_castling);
        unsigned long long black_h_side;
        if (black_castling){
            black_h_side = BB_SQUARES[msb(black_castling)];
        } else{
            black_h_side = BB_EMPTY;
        }
        if (bool(black_a_side) && (msb(black_a_side) > msb(black_king_mask))){
            black_a_side = BB_EMPTY;
        }
        if (bool(black_h_side) && (msb(black_h_side) < msb(black_king_mask))){
            black_h_side = BB_EMPTY;
        }
        return black_a_side | black_h_side | white_a_side | white_h_side;
    }
}
Move Board::_from_chess960(bool chess960, unsigned int from_square, unsigned int to_square, unsigned int promotion, unsigned int drop) const{
    if (!(chess960 || bool(promotion) || bool(drop))){
        if ((from_square == E1) && bool(_kings & BB_E1)){
            if (to_square == H1){
                return Move(E1, G1);
            } else if (to_square == A1){
                return Move(E1, C1);
            }
        } else if ((from_square == E8) && bool(_kings & BB_E8)){
            if (to_square == H8){
                return Move(E8, G8);
            } else if (to_square == A8){
                return Move(E8, C8);
            }
        }
    }
    return Move(from_square, to_square, promotion, drop);
}
Move Board::_to_chess960(const Move &move) const{
    if (move._from_square == E1 && bool(_kings & BB_E1)){
        if (move._to_square == G1 && !(bool(_rooks & BB_G1))){
            return Move(E1, H1);
        } else if (move._to_square == C1 && !(bool(_rooks & BB_C1))){
            return Move(E1, A1);
        }
    } else if (move._from_square == E8 && bool(_kings & BB_E8)){
        if (move._to_square == G8 && !(bool(_rooks & BB_G8))){
            return Move(E8, H8);
        } else if (move._to_square == C8 && !(bool(_rooks & BB_C8))){
            return Move(E8, A8);
        }
    }
    return move;
}
vector<Move> Board::generate_castling_moves(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    unsigned long long backrank = _turn ? BB_RANK_1 : BB_RANK_8;
    unsigned long long king = occupied_co(_turn) & _kings & ~_promoted & backrank & from_mask;
    king = king & -king;
    if (!(king)){
        return moves_vector;
    }
    unsigned long long bb_c = BB_FILE_C & backrank;
    unsigned long long bb_d = BB_FILE_D & backrank;
    unsigned long long bb_f = BB_FILE_F & backrank;
    unsigned long long bb_g = BB_FILE_G & backrank;
    SquareSet squareset(clean_castling_rights() & backrank & to_mask);
    for (unsigned int candidate = squareset.start(); squareset.squares_left(); squareset.next(candidate)){
        unsigned long long rook = BB_SQUARES[candidate];
        bool a_side = rook < king;
        unsigned long long king_to;
        unsigned long long rook_to;
        if (a_side){
            king_to = bb_c;
            rook_to = bb_d;
        } else{
            king_to = bb_g;
            rook_to = bb_f;
        }
        unsigned long long king_path = between(msb(king), msb(king_to));
        unsigned long long rook_path = between(candidate, msb(rook_to));
        if (!((_occupied ^ king ^ rook) & (king_path | rook_path | king_to | rook_to) ||
            _attacked_for_king(king_path | king, _occupied ^ king) ||
            _attacked_for_king(king_to, _occupied ^ king ^ rook ^ rook_to))){
            moves_vector.push_back(_from_chess960(_chess960, msb(king), candidate));
        }
    }
    return moves_vector;
}
unsigned long long Board::_attacks_mask(Square square, unsigned long long occupied) const{
    unsigned long long bb_square = BB_SQUARES[square];
    if (bb_square & _pawns){
        bool color = color_at(square);
        return BB_PAWN_ATTACKS[color][square];
    } else if (bb_square & _knights){
        return BB_KNIGHT_ATTACKS[square];
    } else if (bb_square & _kings){
        return BB_KING_ATTACKS[square];
    } else{
        if (bb_square & _bishops){
            return BB_DIAG_ATTACKS[square][BB_DIAG_MASKS[square] & occupied];
        }
        if (bb_square & _rooks){
            return BB_RANK_ATTACKS[square][BB_RANK_MASKS[square] & occupied] | BB_FILE_ATTACKS[square][BB_FILE_MASKS[square] & occupied];
        }
        if (bb_square & _queens){
            return BB_DIAG_ATTACKS[square][BB_DIAG_MASKS[square] & occupied] | BB_RANK_ATTACKS[square][BB_RANK_MASKS[square] & occupied] | BB_FILE_ATTACKS[square][BB_FILE_MASKS[square] & occupied];
        }
        return 0;
    }
}
unsigned long long Board::attacks_mask(Square square){
    return _attacks_mask(square, _occupied);
}
vector<Move> Board::generate_pseudo_legal_ep(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    if (_ep_square == NO_SQUARE){
        return moves_vector;
    }
    if (!(BB_SQUARES[_ep_square] & to_mask)){
        return moves_vector;
    }
    if (BB_SQUARES[_ep_square] & _occupied){
        return moves_vector;
    }
    unsigned int rank;
    if (_turn){
        rank = 4;
    } else{
        rank = 3;
    }
    unsigned long long capturers = _pawns & occupied_co(_turn) & from_mask & BB_PAWN_ATTACKS[!(_turn)][_ep_square] & BB_RANKS[rank];
    SquareSet squareset(capturers);
    for (unsigned int capturer = squareset.start(); squareset.squares_left(); squareset.next(capturer)){
        moves_vector.push_back(Move(capturer, _ep_square));
    }
    return moves_vector;
}
vector<Move> Board::generate_pseudo_legal_moves(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    unsigned long long our_pieces;
    unsigned long long opponent_pieces;
    if (_turn){
        our_pieces = _white_occupied;
        opponent_pieces = _black_occupied;
    } else{
        our_pieces = _black_occupied;
        opponent_pieces = _white_occupied;
    }
    unsigned long long non_pawns = our_pieces & ~_pawns & from_mask;
    SquareSet non_pawns_squareset = SquareSet(non_pawns);
    for (unsigned int from_square = non_pawns_squareset.start(); non_pawns_squareset.squares_left(); non_pawns_squareset.next(from_square)){
        unsigned long long moves = attacks_mask(from_square) & ~our_pieces & to_mask;
        SquareSet move_squareset = SquareSet(moves);
        for (unsigned int to_square = move_squareset.start(); move_squareset.squares_left(); move_squareset.next(to_square)){
            moves_vector.push_back(Move(from_square, to_square));
        }
    }
    if (from_mask & _kings){
        vector<Move> castling_moves_vector = generate_castling_moves(from_mask, to_mask);
        copy (castling_moves_vector.begin(), castling_moves_vector.end(), back_inserter(moves_vector));
    }
    unsigned long long pawns = _pawns & our_pieces & from_mask;
    if (!(pawns)){
        return moves_vector;
    }
    unsigned long long capturers = pawns;
    SquareSet capturers_squareset = SquareSet(capturers);
    for (unsigned int from_square = capturers_squareset.start(); capturers_squareset.squares_left(); capturers_squareset.next(from_square)){
        unsigned long long targets = BB_PAWN_ATTACKS[_turn][from_square] & opponent_pieces & to_mask;
        SquareSet targets_squareset = SquareSet(targets);
        for (unsigned int to_square = targets_squareset.start(); targets_squareset.squares_left(); targets_squareset.next(to_square)){
            if (!(square_rank(to_square) % 7)){
                for (unsigned int piece_type = 5; piece_type > 1; piece_type--){
                    moves_vector.push_back(Move(from_square, to_square, piece_type));
                }
            } else{
                moves_vector.push_back(Move(from_square, to_square));
            }
        }
    }
    unsigned long long single_moves;
    unsigned long long double_moves;
    if (_turn){
        single_moves = pawns << 8 & ~_occupied;
        double_moves = single_moves << 8 & ~_occupied & (BB_RANK_3 | BB_RANK_4);
    } else{
        single_moves = pawns >> 8 & ~_occupied;
        double_moves = single_moves >> 8 & ~_occupied & (BB_RANK_6 | BB_RANK_5);
    }
    single_moves &= to_mask;
    double_moves &= to_mask;
    SquareSet single_moves_squareset = SquareSet(single_moves);
    for (unsigned int to_square = single_moves_squareset.start(); single_moves_squareset.squares_left(); single_moves_squareset.next(to_square)){
        unsigned int from_square;
        if (_turn){
            from_square = to_square - 8;
        } else{
            from_square = to_square + 8;
        }
        if (!(square_rank(to_square) % 7)){
            for (unsigned int piece_type = 5; piece_type > 1; piece_type--){
                moves_vector.push_back(Move(from_square, to_square, piece_type));
            }
        } else{
            moves_vector.push_back(Move(from_square, to_square));
        }
    }
    SquareSet double_moves_squareset = SquareSet(double_moves);
    for (unsigned int to_square = double_moves_squareset.start(); double_moves_squareset.squares_left(); double_moves_squareset.next(to_square)){
        unsigned int from_square;
        if (_turn){
            from_square = to_square - 16;
        } else{
            from_square = to_square + 16;
        }
        moves_vector.push_back(Move(from_square, to_square));
    }
    if (_ep_square != NO_SQUARE){
        vector<Move> pseudo_legal_ep_vector = generate_pseudo_legal_ep(from_mask, to_mask);
        copy (pseudo_legal_ep_vector.begin(), pseudo_legal_ep_vector.end(), back_inserter(moves_vector));
    }
    return moves_vector;
}
unsigned long long Board::_slider_blockers(int king){
    unsigned long long rooks_and_queens = _rooks | _queens;
    unsigned long long bishops_and_queens = _bishops | _queens;
    unsigned long long snipers = (BB_RANK_ATTACKS[king][0] & rooks_and_queens) | (BB_FILE_ATTACKS[king][0] & rooks_and_queens) | (BB_DIAG_ATTACKS[king][0] & bishops_and_queens);
    unsigned long long blockers = 0;
    SquareSet squareset(snipers & occupied_co(!(_turn)));
    for (unsigned int sniper = squareset.start(); squareset.squares_left(); squareset.next(sniper)){
        unsigned long long b = between(king, sniper) & _occupied;
        if (bool(b) && BB_SQUARES[msb(b)] == b){
            blockers |= b;
        }
    }
    return blockers & occupied_co(_turn);
}
vector<Move> Board::_generate_evasions(int king, unsigned long long checkers, unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    unsigned long long sliders = checkers & (_bishops | _rooks | _queens);
    unsigned long long attacked = 0;
    SquareSet sliders_squareset = SquareSet(sliders);
    for (unsigned int checker = sliders_squareset.start(); sliders_squareset.squares_left(); sliders_squareset.next(checker)){
        attacked |= ray(king, checker) & ~BB_SQUARES[checker];
    }
    if (BB_SQUARES[king] & from_mask){
        SquareSet squareset(BB_KING_ATTACKS[king] & ~occupied_co(_turn) & ~attacked & to_mask);
        for (unsigned int to_square = squareset.start(); squareset.squares_left(); squareset.next(to_square)){
            moves_vector.push_back(Move(king, to_square));
        }
    }
    unsigned int checker = msb(checkers);
    if (BB_SQUARES[checker] == checkers){
        unsigned long long target = between(king, checker) | checkers;
        vector<Move> pseudo_legal_moves_vector = generate_pseudo_legal_moves(~_kings & from_mask, target & to_mask);
        copy (pseudo_legal_moves_vector.begin(), pseudo_legal_moves_vector.end(), back_inserter(moves_vector));
        if (_ep_square != NO_SQUARE && !(bool(BB_SQUARES[_ep_square] & target))){
            unsigned int last_double = _turn ? _ep_square - 8 : _ep_square + 8;
            if (last_double == checker){
                vector<Move> pseudo_legal_ep_vector = generate_pseudo_legal_ep(from_mask, to_mask);
                copy (pseudo_legal_ep_vector.begin(), pseudo_legal_ep_vector.end(), back_inserter(moves_vector));
            }
        }
    }
    return moves_vector;
}
bool Board::is_castling(const Move &move){
    if (_kings & BB_SQUARES[move._from_square]){
        unsigned int from_file = square_file(move._from_square);
        unsigned int to_file = square_file(move._to_square);
        unsigned int diff = (from_file > to_file) ? from_file - to_file : to_file - from_file;
        if (diff > 1){
            return true;
        }
        return _rooks & occupied_co(_turn) & BB_SQUARES[move._to_square];
    }
    return false;
}
bool Board::is_kingside_castling(const Move &move){
    if (square_file(move._to_square) > square_file(move._from_square)){
        return is_castling(move);
    }
    return false;
}
bool Board::is_queenside_castling(const Move &move){
    if (square_file(move._to_square) < square_file(move._from_square)){
        return is_castling(move);
    }
    return false;
}
bool Board::is_attacked_by(bool color, Square square){
        return attackers_mask(color, square);
}
bool Board::is_en_passant(const Move &move) const{
    if (!(bool(_ep_square == move._to_square))){
        return false;
    }
    if (!(bool(_pawns & BB_SQUARES[move._from_square]))){
        return false;
    }
    if (_occupied & BB_SQUARES[move._to_square]){
        return false;
    }
    Square square_diff;
    if (move._from_square > move._to_square){
        square_diff = move._from_square - move._to_square;
    } else{
        square_diff = move._to_square - move._from_square;
    }
    return  square_diff == 7 || square_diff == 9;
}
bool Board::_ep_skewered(int king, int capturer){
    int last_double = _turn ? _ep_square - 8 : _ep_square + 8;
    unsigned long long occupancy = _occupied & ~BB_SQUARES[last_double] & (~BB_SQUARES[capturer] | BB_SQUARES[_ep_square]);
    unsigned long long horizontal_attackers = occupied_co(!(_turn)) & (_rooks | _queens);
    if (BB_RANK_ATTACKS[king][BB_RANK_MASKS[king] & occupancy] & horizontal_attackers){
        return true;
    }
    unsigned long long diagonal_attackers = occupied_co(!(_turn)) & (_bishops | _queens);
    if( BB_DIAG_ATTACKS[king][BB_DIAG_MASKS[king] & occupancy] & diagonal_attackers){
        return true;
    }
    return false;
}
unsigned long long Board::pin_mask(bool color, Square square) const{
    int king = find_king_square(color);
    unsigned long long square_mask = BB_SQUARES[square];
    map<unsigned long long, unsigned long long>* attacks_pointers_array[3] = {BB_FILE_ATTACKS, BB_RANK_ATTACKS, BB_DIAG_ATTACKS};
    const unsigned long long sliders_array[3] = {_rooks | _queens, _rooks | _queens, _bishops | _queens};
    for (unsigned int i = 0; i < 3; i++){
        const unsigned long long &rays = attacks_pointers_array[i][king][0];
        if (rays & square_mask){
            unsigned long long snipers = rays & sliders_array[i] & occupied_co(!(color));
            SquareSet squareset(snipers);
            for (unsigned int sniper = squareset.start(); squareset.squares_left(); squareset.next(sniper)){
                if ((between(sniper, king) & (_occupied | square_mask)) == square_mask){
                    return ray(king, sniper);
                }
            }
            break;
        }
    }
    return BB_ALL;
}
bool Board::is_pinned(bool color, Square square) const{
    return pin_mask(color, square) != BB_ALL;
}
bool Board::_is_safe(unsigned int king, unsigned long long blockers, const Move &move){
    if (move._from_square == king){
        if (is_castling(move)){
            return true;
        }
        return !(bool(is_attacked_by(!(_turn), move._to_square)));
    } else if (is_en_passant(move)){
        return bool(pin_mask(_turn, move._from_square) & BB_SQUARES[move._to_square] && !(_ep_skewered(king, move._from_square)));
    } else{
        return !(bool(blockers & BB_SQUARES[move._from_square])) || bool(ray(move._from_square, move._to_square) & BB_SQUARES[king]);
    }
}
vector<Move> Board::generate_legal_moves(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    unsigned long long king_mask = _kings & occupied_co(_turn);
    if (king_mask){
        unsigned int king = msb(king_mask);
        unsigned long long blockers = _slider_blockers(king);
        vector<Move> possible_moves_vector = _checkers ? _generate_evasions(king, _checkers, from_mask, to_mask) : generate_pseudo_legal_moves(from_mask, to_mask);
        copy_if(possible_moves_vector.begin(), possible_moves_vector.end(), back_inserter(moves_vector), [this, king, blockers] (const Move &move){return _is_safe(king, blockers, move);});
        return moves_vector;
    } else{
        return generate_pseudo_legal_moves(from_mask, to_mask);
    }
}
vector<Move> Board::generate_legal_checks(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    for (Move move : generate_legal_moves(from_mask, to_mask)){
        push(move);
        if (is_check()){
            moves_vector.push_back(move);
        }
        pop();
    }
    return moves_vector;
}
_BoardState Board::_board_state(){
    return _BoardState(*this);
}
bool Board::is_zeroing(const Move &move){
    unsigned long long touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return bool(touched & _pawns) || bool(touched & occupied_co(!(_turn))) || move._drop == 1;
}
void Board::increase_repetition_map(unsigned int increment){
    _repetition_map.try_emplace(_transposition_key, 0);
    _repetition_map[_transposition_key] += increment;
}
void Board::decrease_repetition_map(unsigned int decrement){
    if (DEBUG){
        if (_repetition_map.find(_transposition_key) == _repetition_map.end()){
            cout << "Trying to decrease repetition on a position which is not in the repetition map!" << endl << endl;
            raise_error();
        }
    }
    unsigned int &num_repetitions = _repetition_map[_transposition_key];
    if (DEBUG){
        if (num_repetitions < decrement){
            cout << "Trying to decrease repetition " << decrement << " times on a position which has repeated " << _repetition_map[_transposition_key] << " times!" << endl;
            raise_error();
        }
    }
    if (num_repetitions == decrement){
        _repetition_map.erase(_transposition_key);
        return;
    }
    num_repetitions -= decrement;
}
unsigned int Board::get_repetition_count(){
    if (_repetition_map.find(_transposition_key) == _repetition_map.end()){
        return 0;
    }
    return _repetition_map[_transposition_key];
}
void Board::update_checkers(){
    unsigned long long king_mask = _kings & occupied_co(_turn);
    _checkers = king_mask ? attackers_mask(!(_turn), msb(king_mask)) : 0;
}
void Board::_push_capture(const Move &move, int capture_square, int piece_type, bool was_promoted){}
void Board::push(Move move){
    move = _to_chess960(move);
    _BoardState board_state = _board_state();
    _castling_rights = clean_castling_rights(); // Before pushing stack
    _move_stack.push(_from_chess960(_chess960, move._from_square, move._to_square, move._promotion, move._drop));
    _stack.push(board_state);
    const unsigned int ep_square = _ep_square;
    _ep_square = NO_SQUARE;
    _halfmove_clock++;
    if (!(_turn)){
        _fullmove_number++;
    }
    if (!(move.is_valid())){
        swap_turn();
        increase_repetition_map();
        return;
    }
    if (move._drop){
        _set_piece_at(move._to_square, move._drop, _turn);
        swap_turn();
        increase_repetition_map();
        return;
    }
    if (is_zeroing(move)){
        _halfmove_clock = 0;
    }
    unsigned long long from_bb = BB_SQUARES[move._from_square];
    unsigned long long to_bb = BB_SQUARES[move._to_square];
    bool promoted = bool(_promoted & from_bb);
    int piece_type = _remove_piece_at(move._from_square);
    if (DEBUG){
        if (!(piece_type)){
            cout << endl <<"push() expects move to be pseudo-legal, but got " << move.uci() << " in " << board_fen() << endl << endl << "Board:\n" << string_representation() << endl;
            for (Move m : generate_legal_moves()){
                if (m == move){
                    cout << move.uci() << endl;
                }
            }
            for (Move m : generate_legal_captures()){
                if (m == move){
                    cout << move.uci() << endl;
                }
            }
            raise_error();
        }
    }
    int capture_square = move._to_square;
    int captured_piece_type = piece_type_at(capture_square);
    unsigned long long old_castling_rights = _castling_rights;
    _castling_rights &= ~to_bb & ~from_bb;
    if (piece_type == 6 && !(promoted)){
        if (_turn){
            _castling_rights &= ~BB_RANK_1;
        } else{
            _castling_rights &= ~BB_RANK_8;
        }
    } else if (captured_piece_type == 6 && !(bool(_promoted & to_bb))){
        if (_turn && square_rank(move._to_square) == 7){
            _castling_rights &= ~BB_RANK_8;
        } else if (!(_turn) && !(square_rank(move._to_square))){
            _castling_rights &= ~BB_RANK_1;
        }
    }
    SquareSet changed_castling_rights(old_castling_rights ^ _castling_rights);
    for (Square square = changed_castling_rights.start(); changed_castling_rights.squares_left(); changed_castling_rights.next(square)){
        _transposition_key ^= ZOBRIST_CASTLING_KEY[square];
    }
    if (piece_type == 1){
        int diff = move._to_square - move._from_square;
        if (diff == 16 && square_rank(move._from_square) == 1){
            _ep_square = move._from_square + 8;
        } else if (diff == -16 && square_rank(move._from_square) == 6){
            _ep_square = move._from_square - 8;
        } else if (move._to_square == ep_square && (diff == -9 || diff == -7 || diff == 7 || diff == 9) && !(captured_piece_type)){
            int down = _turn ? -8 : 8;
            capture_square = ep_square + down;
            captured_piece_type = _remove_piece_at(capture_square);
        }
    }
    _transposition_key ^= ZOBRIST_ENPASSANT_KEY[ep_square] ^ ZOBRIST_ENPASSANT_KEY[_ep_square];
    if (move._promotion){
        promoted = true;
        piece_type = move._promotion;
    }
    bool castling = piece_type == 6 && bool(occupied_co(_turn) & to_bb);
    if (castling){
        bool a_side = square_file(move._to_square) < square_file(move._from_square);
        _remove_piece_at(move._from_square);
        _remove_piece_at(move._to_square);
        if (a_side){
            if (_turn){
                _set_piece_at(C1, 6, true);
                _set_piece_at(D1, 4, true);
                _white_castling_status = 2;
            } else{
                _set_piece_at(C8, 6, false);
                _set_piece_at(D8, 4, false);
                _black_castling_status = 2;
            }
        } else{
            if (_turn){
                _set_piece_at(G1, 6, true);
                _set_piece_at(F1, 4, true);
                _white_castling_status = 1;
            } else{
                _set_piece_at(G8, 6, false);
                _set_piece_at(F8, 4, false);
                _black_castling_status = 1;
            }
        }
    }
    if (!(castling)){
        bool was_promoted = bool(_promoted & to_bb);
        _set_piece_at(move._to_square, piece_type, _turn, promoted);
        if (captured_piece_type){
            _push_capture(move, capture_square, captured_piece_type, was_promoted);
        }
    }
    swap_turn();
    update_checkers();
    increase_repetition_map();
}
Move Board::pop(){
    decrease_repetition_map();
    const Move &move = _move_stack.top();
    _BoardState board_state = _stack.top();
    _move_stack.pop();
    _stack.pop();
    board_state.restore(*this);
    return move;
}
bool Board::is_capture(const Move &move){
    unsigned long long touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return bool(touched & occupied_co(!(_turn))) || is_en_passant(move);
}
unsigned int Board::get_capture_piece_square(const Move &move){
    if (DEBUG){
        if (!(is_capture(move))){
            cout << "Non capture move has no capture square!" << endl;
            raise_error();
        }
    }
    if (is_en_passant(move)){
        if (_turn){
            return move._to_square - 8;
        } else{
            return move._to_square + 8;
        }
        return 1;
    }
    return move._to_square;
}
unsigned int Board::get_capture_piece_type(const Move &move){
    if (DEBUG){
        if (!(is_capture(move))){
            cout << "Non capture move has no capture type!" << endl;
            raise_error();
        }
    }
    if (is_en_passant(move)){
        return 1;
    }
    return piece_type_at(move._to_square);
}
vector<Move> Board::generate_pseudo_legal_captures(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> captures_vector = generate_pseudo_legal_moves(from_mask, to_mask & occupied_co(!(_turn)));
    vector<Move> ep_captures_vector = generate_pseudo_legal_ep(from_mask, to_mask);
    copy (ep_captures_vector.begin(), ep_captures_vector.end(), back_inserter(captures_vector));
    return captures_vector;
}
bool Board::has_castling_rights(bool color){
    if ((color && _white_castling_status) || (!(color) && _black_castling_status)){
        return false;
    }
    unsigned long long backrank = color ? BB_RANK_1 : BB_RANK_8;
    return bool(clean_castling_rights() & backrank);
}
bool Board::is_into_check(const Move &move){
    unsigned int king = find_king_square(_turn);
    if (king == NO_SQUARE){
        return false;
    }
    if (_checkers){
        vector<Move> evasions_vector = _generate_evasions(king, _checkers, BB_SQUARES[move._from_square], BB_SQUARES[move._to_square]);
        if (!(any_of(evasions_vector.begin(), evasions_vector.end(), [move] (const Move &m){return m == move;}))){
            return true;
        }
    }
    return !(_is_safe(king, _slider_blockers(king), move));
}
vector<Move> Board::generate_legal_ep(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    vector<Move> pseudo_legal_ep_moves = generate_pseudo_legal_ep(from_mask, to_mask);
    copy_if(pseudo_legal_ep_moves.begin(), pseudo_legal_ep_moves.end(), back_inserter(moves_vector), [this] (const Move &move){return !(is_into_check(move));});
    return moves_vector;
}
vector<Move> Board::generate_legal_captures(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> moves_vector = generate_legal_moves(from_mask, to_mask & occupied_co(!(_turn)));
    vector<Move> legal_ep_vector = generate_legal_ep(from_mask, to_mask);
    copy (legal_ep_vector.begin(), legal_ep_vector.end(), back_inserter(moves_vector));
    return moves_vector;
}
bool Board::_is_halfmoves(unsigned int n){
    if (_halfmove_clock >= n){
        if (!(generate_legal_moves().empty())){
            return true;
        }
    }
    return false;
}
bool Board::is_seventyfive_moves(){
    return _is_halfmoves(150);
}
bool Board::_reduces_castling_rights(const Move &move){
    unsigned long long cr = clean_castling_rights();
    unsigned long long touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return ((touched & cr) ||
            (cr & BB_RANK_1 && touched & _kings & occupied_co(true) & ~_promoted) ||
            (cr & BB_RANK_8 && touched & _kings & occupied_co(false) & ~_promoted));
}
bool Board::has_legal_en_passant(){
    return _ep_square != NO_SQUARE && !(generate_legal_ep().empty());
}
bool Board::is_irreversible(const Move &move){
    return is_zeroing(move) || _reduces_castling_rights(move) || has_legal_en_passant();
}
bool Board::is_repetition(unsigned int count){
    return get_repetition_count() >= count;
}
bool Board::is_threefold_repetition(){
    return is_repetition(3);
}
bool Board::is_fivefold_repetition(){
    return is_repetition(5);
}
bool Board::is_fifty_moves(){
    return _is_halfmoves(100);
}
bool Board::can_claim_fifty_moves(){
    if (is_fifty_moves()){
        return true;
    }
    if (_halfmove_clock >= 99){
        for (Move move : generate_legal_moves()){
            if (!(is_zeroing(move))){
                push(move);
                try{
                    if (is_fifty_moves()){
                        pop();
                        return true;
                    }
                } catch (...){}
                pop();
            }
        }
    }
    return false;
}
bool Board::can_claim_threefold_repetition(){
    TranspositionKeyCounter transpositions = TranspositionKeyCounter();
    transpositions.update(_transposition_key);
    stack<Move> switchyard;
    while (!(_move_stack.empty())){
        Move move = pop();
        switchyard.push(move);
        if (is_irreversible(move)){
            break;
        }
        transpositions.update(_transposition_key);
    }
    while (!(switchyard.empty())){
        push(switchyard.top());
        switchyard.pop();
    }
    if (transpositions.get_count(_transposition_key) >= 3){
        return true;
    }
    for (Move move : generate_legal_moves()){
        push(move);
        try{
            if (transpositions.get_count(_transposition_key) >= 2){
                pop();
                return true;
            }
        } catch(...){}
        pop();
    }
    return false;
}
unsigned int Board::outcome(bool claim_draw){
    if (is_checkmate()){
        return 1; // checkmate
    }
    if (is_insufficient_material()){
        return 2; // insufficient material
    }
    if (generate_legal_moves().empty()){
        return 3; // stalemate
    }
    if (is_fifty_moves()){
        return 4; // fifty moves
    }
    if (is_threefold_repetition()){
        return 5; // threefold repetition
    }
    if (is_variant_loss()){
        return 8; // variant loss
    }
    if (is_variant_win()){
        return 9; // variant win
    }
    if (is_variant_draw()){
        return 10; // variant draw
    }
    if (claim_draw){
        if (can_claim_fifty_moves()){
            return 11;
        }
        if (can_claim_threefold_repetition()){
            return 12;
        }
    }
    return 0;
}
bool Board::is_game_over(bool claim_draw){
    return outcome(claim_draw);
}
bool Board::has_insufficient_material(bool color) const{
    if (occupied_co(color) & (_pawns | _rooks | _queens)){
        return false;
    }
    if (occupied_co(color) & _knights){
        return (popcount(occupied_co(color)) <= 2 && !(occupied_co(!(color)) & ~_kings & ~_queens));
    }
    if (occupied_co(color) & _bishops){
        bool same_color = !(_bishops & BB_DARK_SQUARES) || !(_bishops & BB_LIGHT_SQUARES);
        return same_color &&  !(_pawns) && !(_knights);
    }
    return true;
}
bool Board::is_insufficient_material() const{
    if (has_insufficient_material(true)){
        if (has_insufficient_material(false)){
            return true;
        }
    }
    return false;
}
bool Board::is_checkmate(){
    if (!(is_check())){
        return false;
    }
    return generate_legal_moves().empty();
}
unsigned long long Board::pieces_mask(unsigned int piece_type, bool color) const{
    unsigned long long bb;
    switch (piece_type){
        case 1:
            bb = _pawns;
            break;
        case 2:
            bb = _knights;
            break;
        case 3:
            bb = _bishops;
            break;
        case 4:
            bb = _rooks;
            break;
        case 5:
            bb = _queens;
            break;
        case 6:
            bb = _kings;
            break;
        default:
            cout << "expected PieceType, got " << piece_type << endl;
            raise_error();
    }
    return bb & occupied_co(color);
}
bool Board::is_passed_pawn(Square square, bool color) const{
    if (_pawns & BB_SQUARES[square] & occupied_co(color)){
        return !(PASSED_PAWN_MASKS[int(color)][square] & _pawns & occupied_co(!(color)));
    }
    return false;
}
string Board::_algebraic_without_suffix(const Move &move, bool _long){
    if (!(move.is_valid())){
        return "--";
    }
    if (move._drop){
        string san_string = "";
        if (move._drop != 1){
            san_string = Piece(move._drop, true).symbol();
        }
        san_string += "@" + SQUARE_NAMES[move._to_square];
        return san_string;
    }
    if (is_castling(move)){
        if (square_file(move._to_square) < square_file(move._from_square)){
            return "O-O-O";
        } else{
            return "O-O";
        }
    }
    unsigned int piece_type = piece_type_at(move._from_square);
    if (!(piece_type)){
        cout << "san() and lan() expect move to be legal or null, but got " << uci(move) << " in " << get_fen() << endl;
        raise_error();
    }
    bool capture = is_capture(move);
    string san_string;
    if (piece_type == 1){
        san_string = "";
    } else{
        san_string = Piece(piece_type, true).symbol();
    }
    if (_long){
        san_string += SQUARE_NAMES[move._from_square];
    } else if (piece_type != 1){
        unsigned long long from_mask = pieces_mask(piece_type, _turn);
        from_mask &= ~BB_SQUARES[move._from_square];
        unsigned long long to_mask = BB_SQUARES[move._to_square];
        vector<Move> moves_vector = generate_legal_moves(from_mask, to_mask);
        unsigned long long others = accumulate(moves_vector.begin(), moves_vector.end(), 0, [](unsigned long long bb, const Move &move){return bb | BB_SQUARES[move._from_square];});
        if (others){
            bool row = false;
            bool column = false;
            if (others & BB_RANKS[square_rank(move._from_square)]){
                column = true;
            }
            if (others & BB_FILES[square_file(move._from_square)]){
                row = true;
            } else{
                column = true;
            }
            if (column){
                san_string += FILE_NAMES[square_file(move._from_square)];
            }
            if (row){
                san_string += RANK_NAMES[square_rank(move._from_square)];
            }
        }
    } else if (capture){
        san_string += FILE_NAMES[square_file(move._from_square)];
    }
    if (capture){
        san_string += "x";
    } else if (_long){
        san_string += "-";
    }
    san_string += SQUARE_NAMES[move._to_square];
    if (move._promotion){
        san_string += "=";
        san_string += Piece(move._promotion, true).symbol();
    }
    return san_string;
}
string Board::_algebraic_and_push(const Move &move, bool _long){
    string san_string = _algebraic_without_suffix(move, _long);
    push(move);
    bool king_in_check = is_check();
    bool king_in_checkmate = (king_in_check && is_checkmate()) || is_variant_loss() || is_variant_win();
    if (king_in_checkmate && move.is_valid()){
        return san_string + "#";
    } else if (king_in_check && move.is_valid()){
        return san_string + "+";
    } else{
        return san_string;
    }
}
string Board::_algebraic(const Move &move, bool _long){
    string san_string = _algebraic_and_push(move, _long);
    pop();
    return san_string;
}
string Board::san(const Move &move){
    return _algebraic(move);
}
string Board::san_and_push(const Move &move){
    return _algebraic_and_push(move);
}
Board Board::copy_board(bool copy_stack) const{
    Board board;
    board._pawns = _pawns;
    board._knights = _knights;
    board._bishops = _bishops;
    board._rooks = _rooks;
    board._queens = _queens;
    board._kings = _kings;
    board._white_occupied = _white_occupied;
    board._black_occupied = _black_occupied;
    board._occupied = _occupied;
    board._promoted = _promoted;
    board._chess960 = _chess960;
    board._ep_square = _ep_square;
    board._castling_rights = _castling_rights;
    board._turn = _turn;
    board._fullmove_number = _fullmove_number;
    board._halfmove_clock = _halfmove_clock;
    if (copy_stack){
        board._stack =  _stack;
        board._move_stack = _move_stack;
    }
    return board;
}
bool Board::is_pseudo_legal(const Move &move){
    if (!(move.is_valid())){
        return false;
    }
    if (move._drop){
        return false;
    }
    unsigned int piece = piece_type_at(move._from_square);
    if (!(piece)){
        return false;
    }
    unsigned long long from_mask = BB_SQUARES[move._from_square];
    unsigned long long to_mask = BB_SQUARES[move._to_square];
    if (!(occupied_co(_turn) & from_mask)){
        return false;
    }
    if (move._promotion){
        if (piece != 1){
            return false;
        }
        if (_turn && square_rank(move._to_square) != 7){
            return false;
        }
        else if (!(_turn) && square_rank(move._to_square) != 0){
            return false;
        }
    }
    if (piece == 6){
        Move chess960_move = _from_chess960(_chess960, move._from_square, move._to_square);
        vector<Move> castling_moves_vector = generate_castling_moves();
        if (any_of(castling_moves_vector.begin(), castling_moves_vector.end(), [chess960_move] (const Move &m){return m == chess960_move;})){
            return true;
        }
    }
    if (occupied_co(_turn) & to_mask){
        return false;
    }
    if (piece == 1){
        vector<Move> pseudo_legal_moves_vector = generate_pseudo_legal_moves(from_mask, to_mask);
        if (any_of(pseudo_legal_moves_vector.begin(), pseudo_legal_moves_vector.end(), [move] (const Move &m){return m == move;})){
            return true;
        }
        return false;
    }
    return bool(attacks_mask(move._from_square) & to_mask);
}
bool Board::is_legal(const Move &move){
    return !(is_variant_end()) && is_pseudo_legal(move) && !(is_into_check(move));
}
string Board::variation_san(vector<Move> variation) const{
    Board board = copy_board();
    vector<string> san_vector;
    for (Move move : variation){
        if (!(board.is_legal(move))){
            cout << "illegal move " << move.uci() << " in position " << board.get_fen() << endl;
            raise_error();
        }
        string s = "";
        if (board._turn){
            s += to_str(board._fullmove_number);
            s += ". ";
            s += board.san_and_push(move);
        } else if (san_vector.empty()){
            s += to_str(board._fullmove_number);
            s += "...";
            s += board.san_and_push(move);
        } else{
            s = board.san_and_push(move);
        }
        san_vector.push_back(s);
    }
    if (san_vector.empty()){
        return "";
    }
    string variation_san_str = "";
    for (unsigned int i = 0; i < san_vector.size() - 1; i++){
        variation_san_str += san_vector[i];
        variation_san_str += " ";
    }
    variation_san_str += san_vector[san_vector.size() - 1];
    return variation_san_str;
}
string Board::game_pgn() const{
    vector<Move> moves_vector;
    deque<Move>* d;
    d = (deque<Move>*) &_move_stack;
    for (unsigned int i = 0; i < _move_stack.size(); i++){
        moves_vector.push_back((*d)[i]);
    }
    Board board;
    return board.variation_san(moves_vector);
}
Move Board::parse_san(const string &san_string){
    vector<Move> moves = generate_legal_moves();
    moves.push_back(Move::null());
    for (Move move : moves){
        if (san(move) == san_string){
            return move;
        }
    }
    cout << "illegal san: " << san_string << " in " << get_fen() << endl;
    raise_error();
    return Move::null();
}
Move Board::push_san(const string &san_string){
    Move move = parse_san(san_string);
    push(move);
    return move;
}
string Board::uci(const Move &move) const{
    Move chess960_move = _to_chess960(move);
    chess960_move = _from_chess960(_chess960, chess960_move._from_square, chess960_move._to_square, chess960_move._promotion, chess960_move._drop);
    return chess960_move.uci();
}
Move Board::parse_uci(const string &uci){
    Move move = Move::from_uci(uci);
    if (!(move.is_valid())){
        return move;
    }
    move = _to_chess960(move);
    move = _from_chess960(_chess960, move._from_square, move._to_square, move._promotion, move._drop);
    if (!(is_legal(move))){
        cout << "illegal uci: " << uci << " in " << get_fen() << endl;
        raise_error();
    }
    return move;
}
Move Board::push_uci(const string &uci){
    const Move &move = parse_uci(uci);
    push(move);
    return move;
}
Perft::Perft(Board &board, bool enable_transposition_table){
    _board_pointer = &board;
    _enable_transposition_table = enable_transposition_table;
}
unsigned long long Perft::perft(int depth, bool print){
    unsigned long long key;
    if (_enable_transposition_table){
        key = _board_pointer->_transposition_key;
        key += depth;
        if (_dict.find(key) != _dict.end()){
            return _dict[key];
        }
    }
    unsigned long long nodes = 0;
    vector<Move> moves_vector = _board_pointer->generate_legal_moves();
    if (depth == 1){
        if (print){
            for (Move move : moves_vector){
                cout << move.uci() << ": " << 1 << endl;
            }
        }
        return moves_vector.size();
    }
    for (Move move : moves_vector){
        _board_pointer->push(move);
        unsigned long long p_nodes = perft(depth - 1, false);
        nodes += p_nodes;
        if (print){
            cout << move.uci() << ": " << p_nodes << endl;
        }
        _board_pointer->pop();
    }
    if (_enable_transposition_table){
        _dict[key] = nodes;
    }
    return nodes;
}
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
    unsigned long long masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    const int initial_num_pieces_of_piece_type[7] = {0, 16, 4, 4, 4, 2, 2};
    double initial_material_sum = 0;
    double current_material_sum = 0;
    for (unsigned int piece_type = 1; piece_type < 6; piece_type++){
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
    unsigned long long self_attackers_mask = board->attackers_mask(board->_turn, square);
    unsigned long long opponent_attackers_mask = board->attackers_mask(!(board->_turn), square);
    unsigned int opponent_last_attacker_piece_type = 0;
    double quick_see_score = 0;
    for (unsigned int piece_type = 1; piece_type < 7; piece_type++){
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
    return evaluate_mvv_lva(move);
}
double BoardEvaluator::evaluate_piece(unsigned int piece_type) const{
    return (1 - _game_phase) * opening_material_weights[piece_type] + _game_phase * endgame_material_weights[piece_type];
}
double BoardEvaluator::evaluate_piece_position(unsigned int piece_type, bool color, Square square){
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
double BoardEvaluator::evaluate_piece_at(int piece_type, bool color, Square square, unsigned long long mobility_mask){
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
unsigned long long BoardEvaluator::get_king_side_board_mask(unsigned int king_file){
    if (king_file > 4){
        return BB_FILE_F | BB_FILE_G | BB_FILE_H;
    }
    if (king_file < 3){
        return BB_FILE_A | BB_FILE_B | BB_FILE_C;
    }
    return BB_FILE_D | BB_FILE_E;
}
bool BoardEvaluator::is_uncovered_king(bool color, Square square){
    unsigned int king_file = square_file(square);
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
double BoardEvaluator::evaluate_king_safety(unsigned int white_king_square, unsigned int black_king_square, unsigned int white_king_rank, unsigned int black_king_rank, unsigned int white_king_file, unsigned int black_king_file, double material_score){
    unsigned long long white_king_side_board_mask = BB_KING_ATTACKS[white_king_file];
    unsigned long long black_king_side_board_mask = BB_KING_ATTACKS[black_king_file];
    double castling_point = 0;
    double rank_position_point = 0;
    double file_position_point = 0;
    double pawn_protection_point = 0;
    double attackers_point = 0;
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
    if (white_king_file < 3 || white_king_file > 4){
        unsigned long long protecting_pawns_mask = white_king_side_board_mask & (BB_RANK_2 | BB_RANK_3) & board->_pawns & board->_white_occupied;
        SquareSet protecting_pawns_squareset(protecting_pawns_mask);
        unsigned long long king_side_board_mask = 0;
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
        unsigned long long protecting_pawns_mask = black_king_side_board_mask & (BB_RANK_6 | BB_RANK_7) & board->_pawns & board->_black_occupied;
        SquareSet protecting_pawns_squareset(protecting_pawns_mask);
        unsigned long long king_side_board_mask = 0;
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
    unsigned long long white_king_surrounding_mask = get_surrounding_mask(white_king_square);
    unsigned long long black_king_surrounding_mask = get_surrounding_mask(black_king_square);
    SquareSet white_king_surrounding_mask_squareset(white_king_surrounding_mask | BB_SQUARES[white_king_square]);
    for (Square square = white_king_surrounding_mask_squareset.start(); white_king_surrounding_mask_squareset.squares_left(); white_king_surrounding_mask_squareset.next(square)){
        attackers_point -= popcount(board->_attackers_mask(false, square, board->_pawns));
    }
    SquareSet black_king_surrounding_mask_squareset(black_king_surrounding_mask | BB_SQUARES[black_king_square]);
    for (Square square = black_king_surrounding_mask_squareset.start(); black_king_surrounding_mask_squareset.squares_left(); black_king_surrounding_mask_squareset.next(square)){
        attackers_point += popcount(board->_attackers_mask(true, square, board->_pawns));
    }
    attackers_point /= 8;
    return (5 * castling_point + 7 * rank_position_point + 4 * file_position_point + 20 * pawn_protection_point + 6 * attackers_point) / 40;
}
double BoardEvaluator::evaluate_king_endgame_forcing_checkmate(unsigned int white_king_square, unsigned int black_king_square, unsigned int white_king_rank, unsigned int black_king_rank, unsigned int white_king_file, unsigned int black_king_file, double material_score){
    unsigned int min_white_king_corner_distance = 16;
    unsigned int min_black_king_corner_distance = 16;
    unsigned int min_white_king_center_distance = 16;
    unsigned int min_black_king_center_distance = 16;
    for (unsigned int corner_square : {A1, H1, A8, H8}){
        unsigned int black_king_corner_distance = rank_file_distance_sum(corner_square, black_king_square);
        unsigned int white_king_corner_distance = rank_file_distance_sum(corner_square, white_king_square);
        if (min_black_king_corner_distance > black_king_corner_distance){
            min_black_king_corner_distance = black_king_corner_distance;
        }
        if (min_white_king_corner_distance > white_king_corner_distance){
            min_white_king_corner_distance = white_king_corner_distance;
        }
    }
    for (unsigned int center_square : {D1, E1, D2, E2}){
        unsigned int black_king_center_distance = rank_file_distance_sum(center_square, black_king_square);
        unsigned int white_king_center_distance = rank_file_distance_sum(center_square, white_king_square);
        if (min_black_king_center_distance > black_king_center_distance){
            min_black_king_center_distance = black_king_center_distance;
        }
        if (min_white_king_center_distance > white_king_center_distance){
            min_white_king_center_distance = white_king_center_distance;
        }
    }
    unsigned int distance_between_kings = rank_file_distance_sum(white_king_square, black_king_square);
    double forcing_towards_corner_score = 0;
    if (material_score > 3){
        forcing_towards_corner_score += 3 * (16 - distance_between_kings) + (16 - min_black_king_corner_distance);
    } else if (material_score < 3){
        forcing_towards_corner_score -= 3 * (16 - distance_between_kings) + (16 - min_white_king_corner_distance);
    }
    forcing_towards_corner_score /= 5;
    return forcing_towards_corner_score;
}
double BoardEvaluator::evaluate_rook_position(int white_king_square, int black_king_square, int white_king_rank, int black_king_rank, int white_king_file, int black_king_file){
    double open_file_point = 0;
    double double_rook_point = 0;
    double connected_rook_point = 0;
    vector<unsigned int> white_rook_squares = SquareSet(board->_rooks & board->_white_occupied).get_vector();
    for (Square square : white_rook_squares){
        open_file_point -= popcount(board->_pawns & BB_FILES[square_file(square)] & board->_white_occupied);
    }
    vector<unsigned int> black_rook_squares = SquareSet(board->_rooks & board->_black_occupied).get_vector();
    for (Square square : black_rook_squares){
        open_file_point += popcount(board->_pawns & BB_FILES[square_file(square)] & board->_black_occupied);
    }
    if (white_rook_squares.size() == 2){
        if (!(square_rank(white_rook_squares[0])) && !(square_rank(white_rook_squares[1]))){
            if (!(between(white_rook_squares[0], white_rook_squares[1]) & board->_kings)){
                connected_rook_point += 1;
            }
        } else{
            double_rook_point += int(square_file(white_rook_squares[0]) == square_file(white_rook_squares[1]));
        }
    }
    if (black_rook_squares.size() == 2){
        if (square_rank(black_rook_squares[0]) == 7 && square_rank(black_rook_squares[1]) == 7){
            if (!(between(black_rook_squares[0], black_rook_squares[1]) & board->_kings)){
                connected_rook_point -= 1;
            }
        } else{
            double_rook_point -= int(square_file(black_rook_squares[0]) == square_file(black_rook_squares[1]));
        }
    }
    return (2 * open_file_point + 10 * double_rook_point + 5 * connected_rook_point) / 10;
}
double BoardEvaluator::evaluate_pawn_structures(){
    double double_pawns_point = 0;
    double isolated_pawns_point = 0;
    double passed_pawn_point = 0;
    unsigned long long white_occupied = board->_white_occupied;
    unsigned long long black_occupied = board->_black_occupied;
    unsigned long long all_pawns = board->_pawns;
    unsigned long long white_pawns = all_pawns & white_occupied;
    unsigned long long black_pawns = all_pawns & black_occupied;
    for (unsigned int file = 0; file < 8; file++){
        unsigned long long file_mask = BB_FILES[file];
        unsigned long long white_pawns_in_current_file = white_pawns & file_mask;
        unsigned long long black_pawns_in_current_file = black_pawns & file_mask;
        if (white_pawns_in_current_file){
            double_pawns_point -= double(popcount(white_pawns_in_current_file)) - 1;
        }
        if (black_pawns_in_current_file){
            double_pawns_point += double(popcount(black_pawns_in_current_file)) - 1;
        }
    }
    SquareSet white_pawns_squareset(white_pawns);
    for (Square square = white_pawns_squareset.start(); white_pawns_squareset.squares_left(); white_pawns_squareset.next(square)){ // WHITE
        if (!(ADJACENT_FILE_MASKS[square] & white_pawns)){
            isolated_pawns_point -= 1;
        }
        if (board->is_passed_pawn(square, true)){
            passed_pawn_point += 1;
        }
    }
    SquareSet black_pawns_squareset(black_pawns);
    for (Square square = black_pawns_squareset.start(); black_pawns_squareset.squares_left(); black_pawns_squareset.next(square)){ // BLACK
        if (!(ADJACENT_FILE_MASKS[square] & black_pawns)){
            isolated_pawns_point += 1;
        }
        if (board->is_passed_pawn(square, false)){
            passed_pawn_point -= 1;
        }
    }
    return (3 * double_pawns_point + 2 * isolated_pawns_point + 10 * passed_pawn_point) / 10;
}
double BoardEvaluator::evaluate_opening_board(bool print_scores_seperately){
    int white_king_square = board->find_king_square(true);
    int black_king_square = board->find_king_square(false);
    unsigned long long white_occupied_mask = board->_white_occupied;
    unsigned long long black_occupied_mask = board->_black_occupied;
    int white_king_rank = square_rank(white_king_square);
    int black_king_rank = square_rank(black_king_square);
    int white_king_file = square_file(white_king_square);
    int black_king_file = square_file(black_king_square);
    const unsigned long long masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    unsigned long long develop_pieces_mask = board->_bishops | board->_knights;
    unsigned long long rook_development_file = BB_FILE_D | BB_FILE_E;
    double material_score = 0;
    double center_control_point = 0;
    double positional_point = 0;
    double piece_developmnt = double(popcount(develop_pieces_mask & black_occupied_mask & BB_RANK_8)) - double(popcount(develop_pieces_mask & white_occupied_mask & BB_RANK_1));
    piece_developmnt += double(popcount(board->_rooks & white_occupied_mask & rook_development_file)) - double(popcount(board->_rooks & black_occupied_mask & rook_development_file));
    piece_developmnt /= 4;
    for (unsigned int piece_type = 1; piece_type < 7; piece_type++){
        SquareSet white_pieces_squareset(masks_array[piece_type] & white_occupied_mask);
        for (Square square = white_pieces_squareset.start(); white_pieces_squareset.squares_left(); white_pieces_squareset.next(square)){
            unsigned long long mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score += evaluate_piece_at(piece_type, true, square, mobility_mask);
            if (piece_type != 6){
                center_control_point += (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
            }
            positional_point += evaluate_piece_position(piece_type, true, square);
        }
        SquareSet black_pieces_squareset(masks_array[piece_type] & black_occupied_mask);
        for (Square square = black_pieces_squareset.start(); black_pieces_squareset.squares_left(); black_pieces_squareset.next(square)){
            unsigned long long mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score -= evaluate_piece_at(piece_type, false, square, mobility_mask);
            if (piece_type != 6){
                center_control_point -= (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
            }
            positional_point -= evaluate_piece_position(piece_type, false, square);
        }
    }
    center_control_point /= 50;
    positional_point /= 100;
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }
    double king_safety_score = evaluate_king_safety(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double pawn_structure_point = evaluate_pawn_structures();
    double material_score_weight = 1000000;
    double score = material_score_weight * (material_score + king_safety_score / 2 + bishop_pair_advantage_point / 5) + 1000 * piece_developmnt + 500 * center_control_point + 500 * positional_point + 1000 * pawn_structure_point;
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
    int white_king_square = board->find_king_square(true);
    int black_king_square = board->find_king_square(false);
    unsigned long long white_occupied_mask = board->_white_occupied;
    unsigned long long black_occupied_mask = board->_black_occupied;
    int white_king_rank = square_rank(white_king_square);
    int black_king_rank = square_rank(black_king_square);
    int white_king_file = square_file(white_king_square);
    int black_king_file = square_file(black_king_square);
    const unsigned long long masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    double material_score = 0;
    double center_control_point = 0;
    double positional_point = 0;
    double attack_threat = 0;
    for (unsigned int piece_type = 1; piece_type < 7; piece_type++){
        SquareSet white_pieces_squareset(masks_array[piece_type] & white_occupied_mask);
        for (Square square = white_pieces_squareset.start(); white_pieces_squareset.squares_left(); white_pieces_squareset.next(square)){
            unsigned long long mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
            material_score += evaluate_piece_at(piece_type, true, square, mobility_mask);
            if (piece_type != 6){
                center_control_point += (double(popcount(mobility_mask & CENTER_SQUARES_BB)) + double(popcount(mobility_mask & PSEUDO_CENTER_SQUARES_BB)) / 3) * (10 - material_weights[piece_type]);
                attack_threat += popcount(mobility_mask & board->_black_occupied & ~board->_pawns);
            }
            positional_point += evaluate_piece_position(piece_type, true, square);
        }
        SquareSet black_pieces_squareset(masks_array[piece_type] & black_occupied_mask);
        for (Square square = black_pieces_squareset.start(); black_pieces_squareset.squares_left(); black_pieces_squareset.next(square)){
            unsigned long long mobility_mask = board->_attacks_mask(square, board->_pawns) | BB_SQUARES[square];
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
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }
    double king_safety_score = evaluate_king_safety(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double rooks_evaluation_point = evaluate_rook_position(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file);
    double pawn_structure_point = evaluate_pawn_structures();
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
    int white_king_square = board->find_king_square(true);
    int black_king_square = board->find_king_square(false);
    unsigned long long white_occupied_mask = board->_white_occupied;
    unsigned long long black_occupied_mask = board->_black_occupied;
    int white_king_rank = square_rank(white_king_square);
    int black_king_rank = square_rank(black_king_square);
    int white_king_file = square_file(white_king_square);
    int black_king_file = square_file(black_king_square);
    const unsigned long long masks_array[7] = {0, board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings};
    double material_score = 0;
    double positional_point = 0;
    for (unsigned int piece_type = 1; piece_type < 7; piece_type++){
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
    double insufficient_material_score = 0;
    if (_game_phase > ENDGAME_PERCENTAGE){
        if (board->has_insufficient_material(true)){
            insufficient_material_score -= 1;
        }
        if (board->has_insufficient_material(false)){
            insufficient_material_score += 1;
        }
    }
    double bishop_pair_advantage_point = 0;
    if (popcount(board->_bishops & board->_white_occupied) == 2){
        bishop_pair_advantage_point += 1;
    }
    if (popcount(board->_bishops & board->_black_occupied) == 2){
        bishop_pair_advantage_point -= 1;
    }
    double king_checkmate_score = evaluate_king_endgame_forcing_checkmate(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file, material_score);
    double rooks_evaluation_point = evaluate_rook_position(white_king_square, black_king_square, white_king_rank, black_king_rank, white_king_file, black_king_file);
    double pawn_structure_point = evaluate_pawn_structures();
    double king_participation_point = evaluate_piece_position(6, true, white_king_square) - evaluate_piece_position(6, false, black_king_square);
    double pawn_push_point = 0;
    SquareSet white_pawns_squareset(board->_pawns & white_occupied_mask);
    for (Square square = white_pawns_squareset.start(); white_pawns_squareset.squares_left(); white_pawns_squareset.next(square)){
        unsigned int pawn_promotion_distance = 7 - square_rank(square);
        if (board->is_passed_pawn(square, true)){
            pawn_push_point += pow(10 - pawn_promotion_distance, 2);
        } else{
            pawn_push_point += pow(10 - pawn_promotion_distance, 1.5);
        }
    }
    SquareSet black_pawns_squareset(board->_pawns & black_occupied_mask);
    for (Square square = black_pawns_squareset.start(); black_pawns_squareset.squares_left(); black_pawns_squareset.next(square)){
        unsigned int pawn_promotion_distance = 7 - square_rank(square);
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
Score BoardEvaluator::evaluate_board(bool reverse_score, bool print_scores_seperately){
    if (DEBUG){
        if (popcount(board->_kings) < 2){
            cout << "King capture not possible" << endl;
            raise_error();
        }
    }
    _num_times_board_evaluated++;
    double score;
    if (_game_phase < OPENING_PERCENTAGE){
        score = evaluate_opening_board(print_scores_seperately);
    } else if (_game_phase > ENDGAME_PERCENTAGE){
        score = evaluate_endgame_board(print_scores_seperately);
    } else{
        score = evaluate_midgame_board(print_scores_seperately);
    }
    if (reverse_score && !(board->_turn)){
        score = -score;
    }
    return Score(score);
}
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
    for (unsigned int i = 0; i < MAX_DEPTH; i++){
        _pv_length[i] = 0;
        for (unsigned int j = 0; j < MAX_DEPTH; j++){
            _pv_table[i][j] = Move::null();
        }
    }
    _follow_pv = false;
    _score_pv = false;
    for (unsigned int i = 0; i < NUM_KILLER_MOVES; i++){
        for (unsigned int j = 0; j < MAX_DEPTH; j++){
            _killer_moves[i][j] = Move::null();
        }
    }
    for (unsigned int i = 0; i < 7; i++){
        for (unsigned int j = 0; j < 2; j++){
            for (unsigned int k = 0; k < 64; k++){
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
    for (unsigned int i = NUM_KILLER_MOVES - 1; i > 0; i--){
        _killer_moves[i][_ply] = _killer_moves[i-1][_ply];
    }
    _killer_moves[0][_ply] = killer_move;
}
Score Engine::evaluate_board(bool reverse_score, bool print_scores_seperately){
    return evaluator.evaluate_board(reverse_score, print_scores_seperately);
}
Score Engine::read_transposition_table(const Score &alpha, const Score &beta, const unsigned long long &key, Move &best_move, unsigned int depth){
    if (DISABLE_T_TABLE){
        return INVALID_SCORE;
    }
    if (_transposition_table.find(key) != _transposition_table.end()){
        const TranspositionData &transposition_data = _transposition_table[key];
        best_move = transposition_data._best_move;
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
void Engine::write_transposition_table(unsigned int flag, const Score &score, const unsigned long long &key, const Move &best_move, unsigned int depth){
    if (DISABLE_T_TABLE){
        return;
    }
    _transposition_table.try_emplace(key, TranspositionData());
    update_transposition_data(_transposition_table[key], depth, flag, score, best_move);
}
vector<Move> Engine::get_ordered_moves(unsigned long long from_mask, unsigned long long to_mask, const Move &best_move){
    vector<Move> possible_moves = board->generate_legal_moves(from_mask, to_mask);
    if (_follow_pv){
        enable_pv_scoring(possible_moves);
    }
    for (Move move : possible_moves){
        _random_move_values[move.get_hash()] = move_value(move, true, best_move);
    }
    sort(possible_moves.begin(), possible_moves.end(), [this] (const Move &move1, const Move &move2){return _random_move_values[move1.get_hash()] > _random_move_values[move2.get_hash()];});
    _random_move_values.clear();
    return possible_moves;
}
vector<Move> Engine::get_ordered_captures(unsigned long long from_mask, unsigned long long to_mask){
    vector<Move> capture_moves = board->generate_legal_captures(from_mask, to_mask);
    for (Move move : capture_moves){
        double score = 100 * see(move._to_square) + evaluator.evaluate_capture(move);
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
Score Engine::get_game_over_score(unsigned int outcome, const Score &current_evaluation) const{
    if (outcome == 1){
        return Score(-_ply, 2) + current_evaluation;
    }
    Score draw_point = current_evaluation / 100;
    if (_game_phase < ENDGAME_PERCENTAGE){
        draw_point += DRAW_POINT;
    }
    return draw_point;
}
bool Engine::can_apply_lmr(const Move &move) const{
    if (move._promotion){
        return false;
    }
    for (unsigned int i = 0; i < NUM_KILLER_MOVES; i++){
        if (_killer_moves[i][_ply] == move){
            return false;
        }
    }
    return true;
}
void Engine::update_pv_table(const Move &move){
    _pv_table[_ply][_ply] = move;
    for (unsigned int next_ply = _ply + 1; next_ply < _pv_length[_ply + 1]; next_ply++){
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
    unsigned int num_push = 0;
    for (unsigned int i = 0; i < _pv_length[0]; i++){
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
Move Engine::get_best_move(unsigned int depth, bool print){
    reset_variables();
    _transposition_table.clear();
    Score score;
    unsigned int current_depth = 1;
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
            cout << "info depth " << current_depth << " score " << score << " nodes " << _num_nodes_searched << " nps " << _num_nodes_searched / time_passed << " time " << time_passed << " pv " << get_pv_line() << endl;
        }
        current_depth++;
        if (score._checkmate){
            break;
        }
    } while (current_depth < depth + 1 || (_game_phase > ENDGAME_PERCENTAGE && time_passed < 1));
    current_depth--;
    _last_predicted_score = score;
    _last_depth_searched = current_depth;
    return _pv_table[0][0];
}
double Engine::move_value(const Move &move, bool allow_pv_scoring, const Move &best_move){
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
        return 50000 + move._promotion;
    }
    push(move);
    bool gives_check = board->is_check();
    if (!(ENABLE_CHECK_EXTENSION) && gives_check){
        pop();
        return 45000;
    }
    unsigned long long piece_attack_mask = board->attacks_mask(move._to_square) & ~board->_kings;
    pop();
    if (board->is_capture(move)){
        if (board->is_passed_pawn(board->get_capture_piece_square(move), !(board->_turn))){
            return 40000;
        }
        return 35000 + 100 * see(move._to_square) + evaluator.evaluate_capture(move);
    }
    for (unsigned int i = 0; i < NUM_KILLER_MOVES; i++){
        if (_killer_moves[i][_ply] == move){
            return 30000 - i;
        }
    }
    unsigned int num_attack_threats = popcount(piece_attack_mask & board->occupied_co(!(board->_turn)));
    if (num_attack_threats){
        return 20000 + num_attack_threats;
    }
    unsigned int num_defend_pieces = popcount(piece_attack_mask & board->occupied_co(board->_turn));
    if (num_defend_pieces){
        return 25000 + num_defend_pieces;
    }
    if (board->is_castling(move)){
        return 15000;
    }
    if (ENABLE_CHECK_EXTENSION && gives_check){
        return -10000;
    }
    double history_moves_score = _history_moves[board->piece_type_at(move._from_square)][int(board->color_at(move._from_square))][move._to_square] / 5;
    double passed_pawn_point = double(board->is_passed_pawn(move._from_square, board->_turn));
    return 100 * history_moves_score + 35 * passed_pawn_point;
}
Score Engine::alpha_beta(unsigned int depth, Score alpha, Score beta, bool apply_null_move){
    _num_nodes_searched++;
    _pv_length[_ply] = _ply;
    if (_ply){
        unsigned int outcome = board->outcome();
        if (outcome){
            return get_game_over_score(outcome, evaluate_board() / 100);
        }
    }
    bool not_in_check = !(board->is_check());
    if (ENABLE_CHECK_EXTENSION && _ply > 2 && !(not_in_check)){
        depth++;
    }
    if (depth > MAX_DEPTH - 1){
        depth = 0;
    }
    Move best_move;
    unsigned long long key = board->_transposition_key;
    bool is_pvs_node = (beta - alpha) > PVS_CUTOFF;
    Score t_score = read_transposition_table(alpha, beta, key, best_move, depth);
    bool transposition_allowed = bool(_ply) && !(board->is_repetition(2) || board->_is_halfmoves(98)) && !(is_pvs_node);
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
    Score mate_score = Score(1, 2) - _ply;
    if (mate_score < beta){
        beta = mate_score;
        if (alpha >= mate_score){
            return mate_score;
        }
    }
    bool futility_pruning = false;
    if (not_in_check){
        Score static_evaluation = evaluate_board();
        const double pawn_evaluation = 100 * evaluator.evaluate_piece(1);
        if (depth < 3 && abs(beta - 1) > -mate_score + 100){
            double evaluation_margin = pawn_evaluation * depth;
            if (static_evaluation - evaluation_margin >= beta){
                return static_evaluation - evaluation_margin;
            }
        }
        if (apply_null_move){
            if (_ply && depth > NULL_MOVE_REDUCTION_LIMIT){
                push(Move::null());
                Score score = -alpha_beta(depth - 1 - NULL_MOVE_REDUCTION_LIMIT, -beta, -beta + PVS_CUTOFF, false);
                pop();
                if (score >= beta){
                    return beta;
                }
            }
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
        const double knight_evaluation = 100 * evaluator.evaluate_piece(2);
        const double rook_evaluation = 100 * evaluator.evaluate_piece(4);
        const double futility_margin[4] = {0, pawn_evaluation, knight_evaluation, rook_evaluation};
        if (depth < 4 && alpha < mate_score && static_evaluation + futility_margin[depth] <= alpha){
            futility_pruning = true;
        }
    }
    unsigned int hash_flag = HASH_ALPHA;
    vector<Move> moves = get_ordered_moves(BB_ALL, BB_ALL, best_move);
    for (unsigned int move_index = 0; move_index < moves.size(); move_index++){
        const Move &move = moves[move_index];
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
                score = -alpha_beta(depth - REDUCTION_LIMIT_LMR, -alpha - PVS_CUTOFF, -alpha);
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
                _history_moves[board->piece_type_at(move._from_square)][int(board->color_at(move._from_square))][move._to_square] += depth;
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
double Engine::see(Square square){
    return 0;
    unsigned long long attackers_mask = board->attackers_mask(board->_turn, square);
    if (!(attackers_mask)){
        return 0;
    }
    Move move;
    unsigned int attacker_piece_type = 0;
    for (unsigned long long pieces_mask : {board->_pawns, board->_knights, board->_bishops, board->_rooks, board->_queens, board->_kings}){
        unsigned long long piece_type_attackers_mask = attackers_mask & pieces_mask;
        attacker_piece_type++;
        if (piece_type_attackers_mask){
            move = Move(msb(piece_type_attackers_mask), square);
            break;
        }
    }
    unsigned int captured_piece_type = board->get_capture_piece_type(move);
    double score = evaluator.evaluate_piece(captured_piece_type);
    push(move);
    score -= see(square);
    pop();
    return max(0.0, score);
}
Score Engine::quiescence(Score alpha, Score beta){
    _num_nodes_searched++;
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
int main(){
    initialize_constants();
    Engine engine;
    engine.set_fen(STARTING_FEN);
    string input;
    while (true){
        getline(cin, input);
        if (input == "q"){
            break;
        } else if (input == "d"){
            cout << endl;
            engine.board->print_board();
            cout << endl;
        } else if (input.rfind("push") == 0){
            Move move = Move::from_uci(input.substr(5));
            engine.board->push(move);
        } else if (input.rfind("position fen") == 0){
            engine.set_fen(input.substr(13));
        } else if (input.rfind("perft") == 0){
            int depth = input[6] - '0';
            cout << Perft(*engine.board, false).perft(depth, true) << endl << endl;
        } else if (input.rfind("go depth") == 0){
            int depth = stoi(input.substr(9));
            cout << engine.get_best_move(depth, false).uci() << " " << engine._last_predicted_score << " " << engine.evaluate_board(false) << " " << engine._num_nodes_searched << " " << engine.evaluator.get_game_phase() << " " << engine._last_depth_searched << "  " << engine.get_pv_line() << endl;
        }
    }
    return 0;
}