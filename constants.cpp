#include <stdio.h>
#include <unordered_map>
#include "constants.hpp"
#include "utils.hpp"
using namespace std;

void initialize_squares(){
    BB_SQUARES[0] = 1;
    for (Square square = 1; square < 64; square++){
        BB_SQUARES[square] = BB_SQUARES[square-1] << 1;
    }
}

void initialize_ranks(){
    BB_RANKS[0] = 0xff;
    for (Square rank = 1; rank < 8; rank++){
        BB_RANKS[rank] = BB_RANKS[rank-1] << 8;
    }
}

void initialize_files(){
    for (Square file = 0; file < 8; file++){
        BB_FILES[file] = 0x0101010101010101 << file;
    }
}

Bitboard _edges(Square square){
    return (((BB_RANK_1 | BB_RANK_8) & ~BB_RANKS[square_rank(square)]) | ((BB_FILE_A | BB_FILE_H) & ~BB_FILES[square_file(square)]));
}

Bitboard _sliding_attacks(Square square, Bitboard occupied, char deltas[], unsigned char size){
    Bitboard attacks = BB_EMPTY;
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

map<Bitboard, Bitboard>* _attack_table(char deltas[], unsigned char size){
    map<Bitboard, Bitboard>* attack_table = new map<Bitboard, Bitboard>[64];
    for (Square square = 0; square < 64; square++){
        map<Bitboard, Bitboard> attacks;
        Bitboard mask = _sliding_attacks(square, 0, deltas, size) & ~_edges(square);
        Bitboard subset = 0;
        while (true){
            attacks[subset] = _sliding_attacks(square, subset, deltas, size);
            // cout << subset << " " << attacks[subset] << endl;
            subset = (subset - mask) & mask;
            if (!(subset)){
                break;
            }
        }
        attack_table[square] = attacks;
    }
    return attack_table;
}

Bitboard _step_attacks(Square square, char deltas[], unsigned char size){return _sliding_attacks(square, BB_ALL, deltas, size);}

unsigned char _old_popcount(Bitboard bb){
    // using Brain Kernighan's algorithm
    unsigned char c = 0;
    while (bb){
        bb &= (bb - 1);
        c++;
    }
    return c;
}

Square _old_msb(Bitboard bb){
    Square n = NO_SQUARE;
    while (bb){
        bb >>= 1;
        n++;
    }
    return n;
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
    // PIECE_SYMBOLS[0] = '.';
    PIECE_SYMBOLS[0] = ' ';
    PIECE_SYMBOLS[1] = 'p';
    PIECE_SYMBOLS[2] = 'n';
    PIECE_SYMBOLS[3] = 'b';
    PIECE_SYMBOLS[4] = 'r';
    PIECE_SYMBOLS[5] = 'q';
    PIECE_SYMBOLS[6] = 'k';
    // UNICODE_PIECE_SYMBOLS[PIECE_SYMBOLS[0]] = "•";
    UNICODE_PIECE_SYMBOLS[PIECE_SYMBOLS[0]] = " ";
    // UNICODE_PIECE_SYMBOLS[PIECE_SYMBOLS[0]] = "⭘";
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
    char arbl1[8] = {17, 15, 10, 6, -17, -15, -10, -6};  // KNIGHT ATTACKS
    char arbl2[8] = {9, 8, 7, 1, -9, -8, -7, -1};  // KING ATTACKS
    char arbl3[2] = {-7, -9};  // PAWN ATTACKS
    char arbl4[2] = {7, 9};  // PAWN ATTACKS
    char arbl5[4] = {-9, -7, 7, 9};  // DIAG ATTACKS
    char arbl6[2] = {-8, 8};  // FILE ATTACKS
    char arbl7[2] = {-1, 1};  // RANK ATTACKS
    for (Square sq = 0; sq < 64; sq++){
        BB_KNIGHT_ATTACKS[sq] = _step_attacks(sq, arbl1, 8);
        BB_KING_ATTACKS[sq] = _step_attacks(sq, arbl2, 8);
        BB_PAWN_ATTACKS[0][sq] = _step_attacks(sq, arbl3, 2);
        BB_PAWN_ATTACKS[1][sq] = _step_attacks(sq, arbl4, 2);
    }
    map<Bitboard, Bitboard> * bb_diag_attacks = _attack_table(arbl5, 4);
    map<Bitboard, Bitboard> * bb_file_attacks = _attack_table(arbl6, 2);
    map<Bitboard, Bitboard> * bb_rank_attacks = _attack_table(arbl7, 2);
    for (Square square = 0; square < 64; square++){
        BB_DIAG_ATTACKS[square] = bb_diag_attacks[square];
        BB_FILE_ATTACKS[square] = bb_file_attacks[square];
        BB_RANK_ATTACKS[square] = bb_rank_attacks[square];
        BB_DIAG_MASKS[square] = BB_DIAG_ATTACKS[square][0] & ~_edges(square);
        BB_FILE_MASKS[square] = BB_FILE_ATTACKS[square][0] & ~_edges(square);
        BB_RANK_MASKS[square] = BB_RANK_ATTACKS[square][0] & ~_edges(square);
    }

    for (Square a = 0; a < 64; a++){
        Bitboard bb_a = BB_SQUARES[a];
        for (Square b = 0; b < 64; b++){
            Bitboard bb_b = BB_SQUARES[b];
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
    for (Ray rank = 0; rank < 8; rank++){
        for (Ray file = 0; file < 8; file++){
            SQUARE_NAMES[8*rank+file] = FILE_NAMES[file] + RANK_NAMES[rank];
        }
    }
    for (Square square = 0; square < 64; square++){
        SQUARES_180[square] = square_mirror(square);
        ADJACENT_FILE_MASKS[square] = adjacet_file_mask(square);
        PASSED_PAWN_MASKS[0][square] = passed_mask(false, square);
        PASSED_PAWN_MASKS[1][square] = passed_mask(true, square);
    }
    for (Bitboard i = 0; i < RESULT_STORING_ARRAY_SIZE; i++){
        NUM_TO_BITS[i] = _old_popcount(i);
        MSB_MAP[i] = _old_msb(i);
    }
    for (Square square = 0; square < 64; square++){
        for (bool color : {false, true}){
            for (Ray piece_type = 0; piece_type < 7; piece_type++){
                ZOBRIST_PIECE_KEY[color][piece_type][square] = piece_type ? rand_64() : 0;
            }
        }
        ZOBRIST_CASTLING_KEY[square] = 0;
    }
    for (Square square = 0; square < NO_SQUARE; square++){
        ZOBRIST_ENPASSANT_KEY[square] = (square < 64 || square == NO_SQUARE) ? rand_64() : 0;
    }
    ZOBRIST_ENPASSANT_KEY[NO_SQUARE] = rand_64();
    for (Square castling_square : {A1, H1, A8, H8}){
        ZOBRIST_CASTLING_KEY[castling_square] = rand_64();
    }
    ZOBRIST_TURN_KEY = rand_64();
}