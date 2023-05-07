#include <iostream>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include "utils.hpp"
#include "constants.hpp"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void raise_error(){
    throw 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string hexadeimal(unsigned long long key){
    ostringstream os;
    os << hex << key;
    string hex_str = os.str();
    transform(hex_str.begin(), hex_str.end(), hex_str.begin(), ::toupper);
    return hex_str;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<short int> range(short int start, short int end){
    vector<short int> v;
    for (short int i = start; i < end; i++){
        v.push_back(i);
    }
    return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long long rand_64(){
    return (unsigned long long)rand() << 32 | rand();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ray square_file(Square square){return square & 7;}
Ray square_rank(Square square){return square >> 3;}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char square_distance(Square a, Square b){
    Ray file_a = square_file(a);
    Ray file_b = square_file(b);
    Ray rank_a = square_rank(a);
    Ray rank_b = square_rank(b);
    unsigned char file_distance = (file_a > file_b) ? file_a - file_b : file_b - file_a;
    unsigned char rank_distance = (rank_a > rank_b) ? rank_a - rank_b : rank_b - rank_a;
    if (file_distance > rank_distance){
        return file_distance;
    }
    return rank_distance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char rank_file_distance_sum(Square a, Square b){
    Ray file_a = square_file(a);
    Ray file_b = square_file(b);
    Ray rank_a = square_rank(a);
    Ray rank_b = square_rank(b);
    unsigned char file_distance = (file_a > file_b) ? file_a - file_b : file_b - file_a;
    unsigned char rank_distance = (rank_a > rank_b) ? rank_a - rank_b : rank_b - rank_a;
    return rank_distance + file_distance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long long index(string *arr_pointer, const string &elem, unsigned long long size){
    const auto &arr = arr_pointer;
    for (unsigned long long i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}
unsigned long long index(char *arr_pointer, const char &elem, unsigned long long size){
    const auto &arr = arr_pointer;
    for (unsigned long long i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}
unsigned long long index(int *arr_pointer, const int &elem, unsigned long long size){
    const auto &arr = arr_pointer;
    for (unsigned long long i = 0; i < size; i++){
        if (arr[i] == elem){
            return i;
        }
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard ray(Square a, Square b){return BB_RAYS[a][b];}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard get_surrounding_mask(Square square){
    Bitboard surrounding_mask = 0;
    for (int offset: {-9, -8, -7, -1, 0, 1, 7, 8, 9}){
        unsigned int offset_square = square + offset;
        if (offset_square < 64){
            surrounding_mask |= BB_SQUARES[offset_square];
        }
    }
    return surrounding_mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard flip_vertical(Bitboard bb){
    // https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating#FlipVertically
    bb = ((bb >> 8) & 0x00ff00ff00ff00ff) | ((bb & 0x00ff00ff00ff00ff) << 8);
    bb = ((bb >> 16) & 0x0000ffff0000ffff) | ((bb & 0x0000ffff0000ffff) << 16);
    bb = (bb >> 32) | ((bb & 0x00000000ffffffff) << 32);
    return bb;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard flip_horizontal(Bitboard bb){
    // https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating#MirrorHorizontally
    bb = ((bb >> 1) & 0x5555555555555555) | ((bb & 0x5555555555555555) << 1);
    bb = ((bb >> 2) & 0x3333333333333333) | ((bb & 0x3333333333333333) << 2);
    bb = ((bb >> 4) & 0x0f0f0f0f0f0f0f0f) | ((bb & 0x0f0f0f0f0f0f0f0f) << 4);
    return bb;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char popcount(Bitboard bb){
    if (bb){
        return NUM_TO_BITS[bb & 0xffff] + popcount(bb >> 16);
    }
    return NUM_TO_BITS[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Square lsb(Bitboard bb){
    return msb(bb & -bb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Square msb(Bitboard bb){
//     bb |= (bb >> 1);
//     bb |= (bb >> 2);
//     bb |= (bb >> 4);
//     bb |= (bb >> 8);
//     bb |= (bb >> 16);
//     bb |= (bb >> 32);
//     bb &= ~(bb >> 1);
//     return OLD_MSB_MAP[bb];
// }

Square _msb(Bitboard bb, unsigned char bb_size){
    if (bb < RESULT_STORING_ARRAY_SIZE){
        return MSB_MAP[bb];
    }
    bb_size >>= 1;
    Bitboard n_bb = bb >> bb_size;
    return (n_bb) ? bb_size + _msb(n_bb, bb_size) : _msb(bb, bb_size);
}

Square msb(Bitboard bb){
    return _msb(bb, 64);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard between(Square a, Square b){
    Bitboard bb = BB_RAYS[a][b] & ((BB_ALL << a) ^ (BB_ALL << b));
    return bb & (bb - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Square square_mirror(Square square){
    // Mirrors the square vertically.
    return square ^ 0x38;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void handle_fen_exceptions(const string &board_part, const string &turn_part, const string &castling_part, const string &ep_part, const string &halfmove_part, const string &fullmove_part, const string &remaining_part){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard adjacet_file_mask(Square square){
    Ray file = square_file(square);
    if (!(file)){
        return BB_FILES[1];
    } else if (file == 7){
        return BB_FILES[6];
    }
    return BB_FILES[file - 1] | BB_FILES[file + 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitboard passed_mask(bool color, Square square){
    Ray rank = square_rank(square);
    if (color){
        if (rank == 7){
            return 0;
        }
    } else{
        if (!(rank)){
            return 0;
        }
    }
    Bitboard file_mask = adjacet_file_mask(square) | BB_FILES[square_file(square)];
    Bitboard upper_rank_mask = 0;
    unsigned char iterator_start = color ? rank + 1 : 0;
    unsigned char iterator_end = color ? 8 : rank;
    for (unsigned char i = iterator_start; i < iterator_end; i++){
        upper_rank_mask |= BB_RANKS[i];
    }
    Bitboard mask = file_mask & upper_rank_mask;
    return mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Move::Move(Square from, Square to, PieceType promotion, PieceType drop){
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
        PieceType drop = index(PIECE_SYMBOLS, promotion_char, 7);
        Square square = index(SQUARE_NAMES, uci.substr(2), 64);
        return Move(square, square, 0, drop);
    } else if (uci.size() == 4 || uci.size() == 5){
        Square from_square = index(SQUARE_NAMES, uci.substr(0, 2), 64);
        Square to_square = index(SQUARE_NAMES, uci.substr(2, 2), 64);
        PieceType promotion;
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
    // Gets a UCI string for the move.
    // For example, a move from a7 to a8 would be ``a7a8`` or ``a7a8q``
    // (if the latter is a promotion to a queen).
    // The UCI representation of a null move is ``0000``.

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Piece::Piece(PieceType type, bool color){
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
    for (PieceType type = 1; type < 7; type++){
        if (tolower(s) == PIECE_SYMBOLS[type]){
            return Piece(type, isupper(s));
        }
    }
    return Piece(0, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SquareSet::SquareSet(Bitboard bb){
    _bb = bb;
    _bb_temp = bb;
}

Square SquareSet::start(){
    Square i = 0;
    while (!(_bb_temp & 1)&&_bb_temp){
        _bb_temp >>= 1;
        i++;
    };
    return i;
}

void SquareSet::next(Square &square){
    do{
        _bb_temp >>= 1;
        square++;
    } while (!(_bb_temp & 1)&&_bb_temp);
}

bool SquareSet::squares_left() const{
    return _bb_temp;
}

void SquareSet::setbb(Bitboard bb){
    _bb = bb;
    _bb_temp = bb;
}

void SquareSet::reset(){
    _bb_temp = _bb;
}

string SquareSet::visualize(){
    Bitboard flipped = flip_horizontal(_bb);
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

vector<Square> SquareSet::get_vector(){
    vector<Square> integers_vector;
    for (Square i = start(); squares_left(); next(i)){
        integers_vector.push_back(i);
    }
    return integers_vector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

short int TranspositionKeyCounter::get_count(unsigned long long key){
    return _counter_table[key];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Score::Score(double score, unsigned char type){
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_transposition_data(TranspositionData &transposition_data, unsigned char depth, unsigned char flag, const Score &score, const Move &best_move){
    transposition_data._depth = depth;
    transposition_data._flag = flag;
    transposition_data._score = score;
    transposition_data._best_move = best_move;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////