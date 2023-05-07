#include "./nnue_wrapper.hpp"
using namespace std;

void initialize_nnue_constants(){
    unsigned char i = 0;
    for (Square square : {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
    }){
        nnue_squares[i] = square;
        i++;
    }
    nnue_init("nnue/nn-eba324f53044.nnue"); // NA
    // nnue_init("nnue/nn-62ef826d1a6d.nnue"); // 20-11-28 15:11:45
    // nnue_init("nnue/nn-8a08400ed089.nnue");
}

unsigned char nnue_piece(PieceType piece_type, bool color){
    if (piece_type){
        return (color ? 7 : 13) - piece_type;
    }
    return 0;
}

double eval_position_nnue(const Board *board){
    int pieces[33];
    int squares[33];
    unsigned char index = 0;
    for (PieceType piece_type : {6, 1, 2, 3, 4, 5}){
        for (bool color : {true, false}){
            SquareSet squareset(board->pieces_mask(piece_type) & board->occupied_co(color));
            for (Square square = squareset.start(); squareset.squares_left(); squareset.next(square)){
                pieces[index] = nnue_piece(piece_type, color);
                squares[index] = nnue_squares[square];
                index++;
            }
        }
    }
    pieces[index] = 0;
    squares[index] = 0;
    return nnue_evaluate(!(board->_turn), pieces, squares);
}

// double eval_position(const Board &board){
//     int pieces[33];
//     int squares[33];
//     unsigned char index = 2;
//     for (bool color : {true, false}){
//         for (PieceType piece_type : {1, 2, 3, 4, 5}){
//             SquareSet squareset(board.pieces_mask(piece_type) & board.occupied_co(color));
//             for (Square square = squareset.start(); squareset.squares_left(); squareset.next(square)){
//                 pieces[index] = nnue_piece(piece_type, color);
//                 squares[index] = nnue_squares[square];
//                 index++;
//             }
//         }
//         pieces[!(color)] = nnue_piece(6, color);
//         squares[!(color)] = nnue_squares[board.find_king_square(color)];
//     }

//     pieces[index] = 0;
//     squares[index] = 0;

//     return nnue_evaluate(!(board._turn), pieces, squares);
// }