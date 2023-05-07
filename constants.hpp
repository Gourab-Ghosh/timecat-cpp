#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define Bitboard uint64_t
#define Square uint8_t
#define Ray uint8_t
#define PieceType uint8_t

#include <stdio.h>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

// const bool DEBUG = true;
const bool DEBUG = false;

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

Bitboard BB_SQUARES[64];
Bitboard BB_RANKS[8];
Bitboard BB_FILES[8];
Bitboard BB_EMPTY = 0;
Bitboard BB_ALL = 0xffffffffffffffff;
Bitboard BB_LIGHT_SQUARES = 0x55aa55aa55aa55aa;
Bitboard BB_DARK_SQUARES = 0xaa55aa55aa55aa55;
Bitboard BB_CORNERS;
Bitboard BB_CENTER;
Bitboard BB_BACKRANKS;
Bitboard BB_BLACK_SQUARES = 0xaa55aa55aa55aa55;
Bitboard BB_WHITE_SQUARES = 0x55aa55aa55aa55aa;
Bitboard BB_UPPER_HALF_BOARD = 0xffffffff00000000;
Bitboard BB_LOWER_HALF_BOARD = 0x00000000ffffffff;
Bitboard BB_LEFT_HALF_BOARD = 0xf0f0f0f0f0f0f0f0;
Bitboard BB_RIGHT_HALF_BOARD = 0x0f0f0f0f0f0f0f0f;

Square A1, B1, C1, D1, E1, F1, G1, H1, A2, B2, C2, D2, E2, F2, G2, H2, A3, B3, C3, D3, E3, F3, G3, H3, A4, B4, C4, D4, E4, F4, G4, H4, A5, B5, C5, D5, E5, F5, G5, H5, A6, B6, C6, D6, E6, F6, G6, H6, A7, B7, C7, D7, E7, F7, G7, H7, A8, B8, C8, D8, E8, F8, G8, H8;
Bitboard BB_A1, BB_B1, BB_C1, BB_D1, BB_E1, BB_F1, BB_G1, BB_H1, BB_A2, BB_B2, BB_C2, BB_D2, BB_E2, BB_F2, BB_G2, BB_H2, BB_A3, BB_B3, BB_C3, BB_D3, BB_E3, BB_F3, BB_G3, BB_H3, BB_A4, BB_B4, BB_C4, BB_D4, BB_E4, BB_F4, BB_G4, BB_H4, BB_A5, BB_B5, BB_C5, BB_D5, BB_E5, BB_F5, BB_G5, BB_H5, BB_A6, BB_B6, BB_C6, BB_D6, BB_E6, BB_F6, BB_G6, BB_H6, BB_A7, BB_B7, BB_C7, BB_D7, BB_E7, BB_F7, BB_G7, BB_H7, BB_A8, BB_B8, BB_C8, BB_D8, BB_E8, BB_F8, BB_G8, BB_H8;
Bitboard BB_FILE_A, BB_FILE_B, BB_FILE_C, BB_FILE_D, BB_FILE_E, BB_FILE_F, BB_FILE_G, BB_FILE_H;
Bitboard BB_RANK_1, BB_RANK_2, BB_RANK_3, BB_RANK_4, BB_RANK_5, BB_RANK_6, BB_RANK_7, BB_RANK_8;

char PIECE_SYMBOLS[7];
map<char, string> UNICODE_PIECE_SYMBOLS;

bool INVERT_UNICODE_COLOR = true;

Bitboard BB_KNIGHT_ATTACKS[64];
Bitboard BB_KING_ATTACKS[64];
Bitboard BB_PAWN_ATTACKS[2][64];

Bitboard BB_DIAG_MASKS[64];
Bitboard BB_FILE_MASKS[64];
Bitboard BB_RANK_MASKS[64];
map<Bitboard, Bitboard> BB_DIAG_ATTACKS[64];
map<Bitboard, Bitboard> BB_FILE_ATTACKS[64];
map<Bitboard, Bitboard> BB_RANK_ATTACKS[64];

Bitboard BB_RAYS[64][64];

string FILE_NAMES[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
string RANK_NAMES[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
string SQUARE_NAMES[64];
Square SQUARES_180[64];

Bitboard CENTER_SQUARES_BB = 0x0000001818000000;
Bitboard PSEUDO_CENTER_SQUARES_BB = 0x00003C24243C0000;

Bitboard ADJACENT_FILE_MASKS[64];
Bitboard PASSED_PAWN_MASKS[2][64];

const unsigned long long RESULT_STORING_ARRAY_SIZE = 1ULL << 16;

Square MSB_MAP[RESULT_STORING_ARRAY_SIZE];
Square NUM_TO_BITS[RESULT_STORING_ARRAY_SIZE];

const Square NO_SQUARE = -1;

Bitboard ZOBRIST_PIECE_KEY[2][7][64];
Bitboard ZOBRIST_ENPASSANT_KEY[NO_SQUARE + 1];
Bitboard ZOBRIST_CASTLING_KEY[64];
Bitboard ZOBRIST_TURN_KEY;

#endif