#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <vector>
#include <sstream>
using namespace std;

template <typename T> string to_str(const T& t){ 
    ostringstream os;
    os<<t;
    return os.str();
}

void raise_error();
string hexadeimal(unsigned long long key);
vector<short int> range(short int start, short int end);
double interpolate(double start, double end, double alpha);
double inverse_interpolate(double start, double end, double value);
double match_interpolate(double new_start, double new_end, double old_start, double old_end, double old_value);
unsigned long long rand_64();
Ray square_file(Square square);
Ray square_rank(Square square);
unsigned char square_distance(Square a, Square b);
unsigned char rank_file_distance_sum(Square a, Square b);
Bitboard ray(Square a, Square b);
Bitboard get_surrounding_mask(Square square);
Bitboard flip_vertical(Bitboard bb);
Bitboard flip_horizontal(Bitboard bb);
unsigned char popcount(Bitboard bb);
Square lsb(Bitboard bb);
Square msb(Bitboard bb);
Bitboard between(Square a, Square b);
Square square_mirror(Square square);
void handle_fen_exceptions(const string &board_part, const string &turn_part, const string &castling_part, const string &ep_part, const string &halfmove_part, const string &fullmove_part, const string &remaining_part);
Bitboard adjacet_file_mask(Square square);
Bitboard passed_mask(bool color, Square square);
unsigned long long index(string *arr_pointer, const string &elem, unsigned long long size);
unsigned long long index(char *arr_pointer, const char &elem, unsigned long long size);
unsigned long long index(int *arr_pointer, const int &elem, unsigned long long size);
string color_output(string s, const string &color = NO_COLOR);
string color_output(char c, const string &color = NO_COLOR);

class Move{
public:
    Square _from_square;
    Square _to_square;
    PieceType _promotion;
    PieceType _drop;
    Move(Square from = 0, Square to = 0, PieceType promotion = 0, PieceType drop = 0);
    static Move from_uci(string uci);
    string uci() const;
    bool is_valid() const;
    static Move null();
    static Move from_hash(unsigned int hash);
    unsigned int get_hash() const;
    bool operator == (Move move) const;
    bool operator != (Move move) const;
    // void operator=(Move move);
};
ostream& operator << (ostream &os, Move move);

class Piece{
public:
    PieceType _type;
    bool _color;
    Piece(PieceType type, bool color);
    char symbol() const;
    string unicode_symbol(bool invert_color = INVERT_UNICODE_COLOR) const;
    static Piece from_symbol(char s);
};

class SquareSet{
    Bitboard _bb;
    Bitboard _bb_temp;
public:
    SquareSet(Bitboard bb = 0);
    Square start();
    void next(Square &square);
    bool squares_left() const;
    void setbb(Bitboard bb);
    void reset();
    vector<Square> get_vector();
    string visualize();
};

class TranspositionKeyCounter{
    unordered_map<unsigned long long, short int> _counter_table;
public:
    int _start;
    TranspositionKeyCounter(int start = 0);
    void update(unsigned long long key);
    short int get_count(unsigned long long key);
};

class Score{
public:
    // 0 -> invalid
    // 1 -> normal
    // 2 -> checkmate
    // 3 -> infinity
    bool _is_invalid;
    double _normal;
    char _checkmate;
    char _infinity;
    Score(double score = 0, unsigned char type = 1);
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

void update_transposition_data(TranspositionData &transposition_data, unsigned char depth, unsigned char flag, const Score &score, const Move &best_move);

#endif