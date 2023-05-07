#ifndef _NNUE_WRAPPER_H
#define _NNUE_WRAPPER_H

#include <string>
#include "nnue-probe/nnue.cpp"
#include "../constants.hpp"
using namespace std;

Square nnue_squares[64];

unsigned char nnue_piece(PieceType piece_type, bool color);
double eval_position_nnue(const Board *board);

#endif