// #include <iostream>
// #include <cmath>
// #include <algorithm>
// #include <numeric>
// #include <chrono>
// #include "board.hpp"
// #include "constants.hpp"
// #include "utils.hpp"
// using namespace std;
// using namespace std::chrono;

// _BoardState::_BoardState(const Board &board){
//     _pawns = board._pawns;
//     _knights = board._knights;
//     _bishops = board._bishops;
//     _rooks = board._rooks;
//     _queens = board._queens;
//     _kings = board._kings;
//     _occupied_w = board._white_occupied;
//     _occupied_b = board._black_occupied;
//     _occupied = board._occupied;
//     _promoted = board._promoted;
//     _turn = board._turn;
//     _castling_rights = board._castling_rights;
//     _ep_square = board._ep_square;
//     _fullmove_number = board._fullmove_number;
//     _halfmove_clock = board._halfmove_clock;
//     _white_castling_status = board._white_castling_status;
//     _black_castling_status = board._black_castling_status;
//     _transposition_key = board._transposition_key;
//     _checkers = board._checkers;
// }

// void _BoardState::restore(Board &board) const{
//     board._pawns = _pawns;
//     board._knights = _knights;
//     board._bishops = _bishops;
//     board._rooks = _rooks;
//     board._queens = _queens;
//     board._kings = _kings;
//     board._white_occupied = _occupied_w;
//     board._black_occupied = _occupied_b;
//     board._occupied = _occupied;
//     board._promoted = _promoted;
//     board._turn = _turn;
//     board._castling_rights = _castling_rights;
//     board._ep_square = _ep_square;
//     board._fullmove_number = _fullmove_number;
//     board._halfmove_clock = _halfmove_clock;
//     board._white_castling_status = _white_castling_status;
//     board._black_castling_status = _black_castling_status;
//     board._transposition_key = _transposition_key;
//     board._checkers = _checkers;
// }

// PieceType _BoardState::piece_type_at(Square square) const{
//     Bitboard bb = BB_SQUARES[square];
//     if (bb & _pawns){
//         return 1;
//     } else if (bb & _knights){
//         return 2;
//     } else if (bb & _bishops){
//         return 3;
//     } else if (bb & _rooks){
//         return 4;
//     } else if (bb & _queens){
//         return 5;
//     } else if (bb & _kings){
//         return 6;
//     } else {
//         return 0;
//     }
// }


// Board::Board(const string &fen, bool chess960){
//     if (fen.empty()){
//         reset_board();
//     } else{
//         set_fen(fen);
//     }
//     _chess960 = chess960;
// }

// unsigned long long Board::generate_transposition_key(){return 0;}
// void Board::set_fen(string fen){}
// bool Board::is_variant_end(){return true;}
// bool Board::is_variant_win(){return true;}
// bool Board::is_variant_loss(){return true;}
// bool Board::is_variant_draw(){return true;}
// Bitboard Board::occupied_co(bool color) const{return 0;}
// void Board::_clear_board(){}
// PieceType Board::_remove_piece_at(Square square){return 0;}
// void Board::_set_piece_at(Square square, PieceType piece_type, bool color, bool promoted){}
// void Board::set_turn(bool turn){}
// void Board::swap_turn(){}
// string Board::board_fen(bool promoted) const{return "";}
// void Board::_set_board_fen(string fen){}
// void Board::_set_castling_fen(string castling_fen){}
// void Board::clear_stack(){}
// void Board::reset_board(){}
// string Board::get_checkers_squares(){return "";}
// string Board::string_representation(bool color, Bitboard hilight_bb, bool use_unicode, bool invert_color) const{return "";}
// string Board::string_unicode_representation(bool color, Bitboard hilight_bb, bool invert_color) const{return "";}
// void Board::print_board(bool color, bool use_unicode){}
// void Board::print_unicode_board(bool color){}
// bool Board::is_check(){return true;}
// Bitboard Board::_attackers_mask(bool color, Square square, Bitboard occupied) const{return 0;}
// Bitboard Board::attackers_mask(bool color, Square square){return 0;}
// Bitboard Board::get_least_attackers_mask(Square square){return 0;}
// bool Board::_attacked_for_king(Bitboard path, Bitboard occupied){return true;}
// Bitboard Board::clean_castling_rights(){return 0;}
// Move Board::_from_chess960(bool chess960, Square from_square, Square to_square, PieceType promotion, PieceType drop) const{return Move();}
// Move Board::_to_chess960(const Move &move) const{return Move();}
// vector<Move> Board::generate_castling_moves(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// Bitboard Board::_attacks_mask(Square square, Bitboard occupied) const{return 0;}
// Bitboard Board::attacks_mask(Square square){return 0;}
// vector<Move> Board::generate_pseudo_legal_ep(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// vector<Move> Board::generate_pseudo_legal_moves(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// vector<Move> Board::generate_legal_checks(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// string Board::castling_xfen(){return "";}
// string Board::get_fen(bool promoted){return "";}
// PieceType Board::piece_type_at(Square square) const{return 0;}
// bool Board::color_at(Square square) const{return true;}
// Piece Board::piece_at(Square square) const{return Piece(0, true);}
// Square Board::find_king_square(bool color) const{return 0;}
// Bitboard Board::_slider_blockers(Square king){return 0;}
// vector<Move> Board::_generate_evasions(Square king, Bitboard checkers, Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// bool Board::is_castling(const Move &move){return true;}
// bool Board::is_kingside_castling(const Move &move){return true;}
// bool Board::is_queenside_castling(const Move &move){return true;}
// bool Board::is_attacked_by(bool color, Square square){return true;}
// bool Board::is_en_passant(const Move &move) const{return true;}
// bool Board::_ep_skewered(Square king, Square capturer){return true;}
// Bitboard Board::pin_mask(bool color, Square square) const{return 0;}
// bool Board::is_pinned(bool color, Square square) const{return true;}
// bool Board::_is_safe(Square king, Bitboard blockers, const Move &move){return true;}
// vector<Move> Board::generate_legal_moves(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// _BoardState Board::_board_state(){return _BoardState(*this);}
// bool Board::is_zeroing(const Move &move){return true;}
// void Board::increase_repetition_map(unsigned short int increment){}
// void Board::decrease_repetition_map(unsigned short int decrement){}
// unsigned short int Board::get_repetition_count(){return 0;}
// void Board::update_checkers(){}
// void Board::_push_capture(const Move &move, Square capture_square, PieceType piece_type, bool was_promoted){}
// void Board::push(Move move){}
// Move Board::pop(){return Move();}
// bool Board::is_capture(const Move &move){return true;}
// Square Board::get_capture_piece_square(const Move &move){return 0;}
// PieceType Board::get_capture_piece_type(const Move &move){return 0;}
// vector<Move> Board::generate_pseudo_legal_captures(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// bool Board::has_castling_rights(bool color){return true;}
// bool Board::is_into_check(const Move &move){return true;}
// vector<Move> Board::generate_legal_ep(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// vector<Move> Board::generate_legal_captures(Bitboard from_mask, Bitboard to_mask){vector<Move> v; return v;}
// bool Board::_is_halfmoves(unsigned short int n){return true;}
// bool Board::is_seventyfive_moves(){return true;}
// bool Board::_reduces_castling_rights(const Move &move){return true;}
// bool Board::has_legal_en_passant(){return true;}
// bool Board::is_irreversible(const Move &move){return true;}
// bool Board::is_repetition(unsigned short int count){return true;}
// bool Board::is_threefold_repetition(){return true;}
// bool Board::is_fivefold_repetition(){return true;}
// bool Board::is_fifty_moves(){return true;}
// bool Board::can_claim_fifty_moves(){return true;}
// bool Board::can_claim_threefold_repetition(){return true;}
// unsigned char Board::outcome(bool claim_draw){return 0;}
// bool Board::is_game_over(bool claim_draw){return true;}
// bool Board::has_insufficient_material(bool color) const{return true;}
// bool Board::is_insufficient_material() const{return true;}
// bool Board::is_checkmate(){return true;}
// Bitboard Board::pieces_mask(PieceType piece_type) const{return 0;}
// Bitboard Board::pieces_mask(PieceType piece_type, bool color) const{return 0;}
// bool Board::is_passed_pawn(Square square, bool color) const{return true;}
// string Board::_algebraic_without_suffix(const Move &move, bool _long){return "";}
// string Board::_algebraic_and_push(const Move &move, bool _long){return "";}
// string Board::_algebraic(const Move &move, bool _long){return "";}
// string Board::san(const Move &move){return "";}
// string Board::san_and_push(const Move &move){return "";}
// Board Board::copy_board(bool copy_stack) const{return Board();}
// bool Board::is_pseudo_legal(const Move &move){return true;}
// bool Board::is_legal(const Move &move){return true;}
// string Board::variation_san(vector<Move> variation) const{return "";}
// string Board::game_pgn() const{return "";}
// Move Board::parse_san(const string &san_string){return Move();}
// Move Board::push_san(const string &san_string){return Move();}
// string Board::uci(const Move &move) const{return "";}
// Move Board::parse_uci(const string &uci){return Move();}
// Move Board::push_uci(const string &uci){return Move();}

// Perft::Perft(Board &board, bool enable_transposition_table){
//     _board_pointer = &board;
//     _enable_transposition_table = enable_transposition_table;
// }

// unsigned long long Perft::perft(unsigned short int depth, bool print){
//     unsigned long long key = _board_pointer->_transposition_key;
//     if (_enable_transposition_table){
//         key += depth;
//         if (_dict.find(key) != _dict.end()){
//             return _dict[key];
//         }
//     }
//     unsigned long long nodes = 0;
//     vector<Move> moves_vector = _board_pointer->generate_legal_moves();
//     if (depth == 1){
//         if (print){
//             for (Move move : moves_vector){
//                 cout << move.uci() << ": " << 1 << endl;
//             }
//         }
//         return moves_vector.size();
//     }
//     for (Move move : moves_vector){
//         _board_pointer->push(move);
//         unsigned long long p_nodes = perft(depth - 1, false);
//         nodes += p_nodes;
//         if (print){
//             cout << move.uci() << ": " << p_nodes << endl;
//         }
//         _board_pointer->pop();
//     }
//     if (_enable_transposition_table){
//         _dict[key] = nodes;
//     }
//     return nodes;
// }




#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <chrono>
#include "board.hpp"
#include "constants.hpp"
#include "utils.hpp"
using namespace std;
using namespace std::chrono;

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

PieceType _BoardState::piece_type_at(Square square) const{
    Bitboard bb = BB_SQUARES[square];
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

Bitboard Board::occupied_co(bool color) const{
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
    for (bool color : {false, true}){
        for (PieceType piece_type = 1; piece_type < 7; piece_type++){
            Bitboard piece_mask = pieces_mask(piece_type, color);
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

PieceType Board::_remove_piece_at(Square square){
    PieceType piece_type = piece_type_at(square);
    Bitboard mask = BB_SQUARES[square];
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
    _transposition_key ^= ZOBRIST_PIECE_KEY[color_at(square)][piece_type][square];
    _white_occupied &= ~mask;
    _black_occupied &= ~mask;
    _promoted &= ~mask;
    return piece_type;
}

void Board::_set_piece_at(Square square, PieceType piece_type, bool color, bool promoted){
    _remove_piece_at(square);
    Bitboard mask = BB_SQUARES[square];
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
    _transposition_key ^= ZOBRIST_PIECE_KEY[color][piece_type][square];
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
    unsigned short int empty = 0;
    for (Square i = 0; i < 64; i++){
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
    // Clear the board.
    _clear_board();

    // Put pieces on the board.
    Square square_index = 0;
    string digits = "12345678";
    string pieces ="pnbrqkPNBRQK";
    for (unsigned short int i = 0; i < fen.length(); i++){
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
    for (unsigned short int i = 0; i < castling_fen.length(); i++){
        char flag = castling_fen[i];
        bool color = isupper(flag);
        flag = tolower(flag);
        Bitboard backrank = color ? BB_RANK_1 : BB_RANK_8;
        Bitboard rooks = occupied_co(color) & _rooks & backrank;
        Square king = find_king_square(color);

        if (flag == 'q'){
            // Select the leftmost rook.
            if (king != NO_SQUARE && lsb(rooks) < king){
                _castling_rights |= rooks & -rooks;
            } else{
                _castling_rights |= BB_FILE_A & backrank;
            }
        } else if (flag == 'k'){
            // Select the rightmost rook.
            Square rook = msb(rooks);
            if (king != NO_SQUARE && king < rook){
                _castling_rights |= BB_SQUARES[rook];
            } else{
                _castling_rights |= BB_FILE_H & backrank;
            }
        } else{
            for (Ray j = 0; j < 8; j++){
                if (FILE_NAMES[j][0] == flag){
                    _castling_rights |= BB_FILES[j] & backrank;
                    break;
                }
            }
        }
    }
}

void Board::clear_stack(){
    // Clears the move stack.
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
    for (bool color : {true, false}){
        Square king = find_king_square(color);
        if (!(king)){
            continue;
        }
        Ray king_file = square_file(king);
        Bitboard backrank = color ? BB_RANK_1 : BB_RANK_8;

        SquareSet castling_squares_squarset(clean_castling_rights() & backrank);
        for (Square rook_square = castling_squares_squarset.start(); castling_squares_squarset.squares_left(); castling_squares_squarset.next(rook_square)){
            Square rook_file = square_file(rook_square);
            bool a_side = rook_file < king_file;
            Square other_rooks = occupied_co(color) & _rooks & backrank & ~BB_SQUARES[rook_square];
            SquareSet other_rooks_squareset(other_rooks);
            char ch = a_side ? 'q' : 'k';
            for (Square other = other_rooks_squareset.start(); other_rooks_squareset.squares_left(); other_rooks_squareset.next(other)){
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
        for (unsigned short int i = 0; i < 4; i++){
            char ch = chars[i];
            for (unsigned short int j = 0; j < builder.length(); j++){
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
    // Parses a FEN and sets the position from it.

    // :raises: :exc:`ValueError` if syntactically invalid. Use
    //     :func:`~chess.Board.is_valid()` to detect invalid positions.
    string board_part = "";
    string turn_part = "";
    string castling_part = "";
    string ep_part = "";
    string halfmove_part = "";
    string fullmove_part = "";
    string remaining_part = "";

    // Board part.
    unsigned short int n = 0;
    for (unsigned short int i = 0; i < fen.length(); i++){
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

    // Turn.
    if (turn_part.empty()){
        set_turn(true);
    } else{
        if (turn_part == "w"){
            set_turn(true);
        } else if (turn_part == "b"){
            set_turn(false);
        }
    }

    // Validate castling part.
    if (castling_part.empty()){
        castling_part = "-";
    }   

    // En passant square.
    _ep_square = NO_SQUARE;
    if (!(ep_part.empty() || ep_part == "-")){
        for (Square square = 0; square < 64; square++){
            if (SQUARE_NAMES[square] == ep_part){
                _ep_square = square;
                break;
            }
        }
    }

    // Check that the half-move part is valid.
    if (halfmove_part.empty()){
        _halfmove_clock = 0;
    } else{
        _halfmove_clock = stoi(halfmove_part);
    }

    // Check that the full-move number part is valid.
    // 0 is allowed for compatibility, but later replaced with 1.
    if (fullmove_part.empty()){
        _fullmove_number = 1;
    } else{
        _fullmove_number = stoi(fullmove_part);
        if (_fullmove_number < 1){
            _fullmove_number = 1;
        }
    }

    // Set board part.
    _set_board_fen(board_part);
    _set_castling_fen(castling_part);
    _white_castling_status = 0;
    _black_castling_status = 0;
    _transposition_key = generate_transposition_key();
    Bitboard king_mask = _kings & occupied_co(_turn);
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

PieceType Board::piece_type_at(Square square) const{
    Bitboard bb = BB_SQUARES[square];
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

Square Board::find_king_square(bool color) const{
        // Finds the king square of the given side. Returns -1 if there
        // is no king of that color.

        // In variants with king promotions, only non-promoted kings are
        // considered.
        
        Bitboard king_mask = occupied_co(color) & _kings & ~_promoted;
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

string Board::string_representation(bool color, Bitboard hilight_bb, bool use_unicode, bool invert_color) const{
    string border_color = color ? COLOR_GREEN : NO_COLOR;
    string black_piece_color = color ? COLOR_BOLDMAGENTA : NO_COLOR;
    string white_piece_color = color ? COLOR_BOLDWHITE : NO_COLOR;
    string lebel_color = color ? COLOR_BOLDRED : NO_COLOR;
    string highlight_color = color ? COLOR_BOLDYELLOW : NO_COLOR;
    string line_sep = "+---+---+---+---+---+---+---+---+";
    string s = color_output(line_sep + "\n| ", border_color);
    for (Square square = 63; square < 64; square--){
        Square mirror_square = square ^ 7;
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

string Board::string_unicode_representation(bool color, Bitboard hilight_bb, bool invert_color) const{
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

Bitboard Board::_attackers_mask(bool color, Square square, Bitboard occupied) const{
    Bitboard rank_pieces = BB_RANK_MASKS[square] & occupied;
    Bitboard file_pieces = BB_FILE_MASKS[square] & occupied;
    Bitboard diag_pieces = BB_DIAG_MASKS[square] & occupied;
    Bitboard queens_and_rooks = _queens | _rooks;
    Bitboard queens_and_bishops = _queens | _bishops;
    Bitboard attackers = (BB_KING_ATTACKS[square] & _kings) | (BB_KNIGHT_ATTACKS[square] & _knights) | (BB_RANK_ATTACKS[square][rank_pieces] & queens_and_rooks) | (BB_FILE_ATTACKS[square][file_pieces] & queens_and_rooks) | (BB_DIAG_ATTACKS[square][diag_pieces] & queens_and_bishops) | (BB_PAWN_ATTACKS[!(color)][square] & _pawns);
    return attackers & occupied_co(color);
}

Bitboard Board::attackers_mask(bool color, Square square){
    return _attackers_mask(color, square, _occupied);
}

Bitboard Board::get_least_attackers_mask(Square square){
    const Bitboard current_attackers_mask = attackers_mask(_turn, square);
    if (!(current_attackers_mask)){
        return 0;
    }
    for (Bitboard pieces_mask : {_pawns, _knights, _bishops, _rooks, _queens, _kings}){
        Bitboard piece_type_attackers_mask = current_attackers_mask & pieces_mask;
        if (piece_type_attackers_mask){
            return piece_type_attackers_mask;
        }
    }
    return 0;
}

bool Board::_attacked_for_king(Bitboard path, Bitboard occupied){
    SquareSet squareset(path);
    for (Square sq = squareset.start(); squareset.squares_left(); squareset.next(sq)){
        if (_attackers_mask(!(_turn), sq, occupied)){
            return true;
        }
    }
    return false;
}

Bitboard Board::clean_castling_rights(){
    // Returns valid castling rights filtered from
    // :data:`~chess.Board.castling_rights`.
    if (!(_stack.empty())){
        // No new castling rights are assigned in a game, so we can assume
        // they were filtered already.
        return _castling_rights;
    }

    Bitboard castling = _castling_rights & _rooks;
    Bitboard white_castling = castling & BB_RANK_1 & _white_occupied;
    Bitboard black_castling = castling & BB_RANK_8 & _black_occupied;

    if (!(_chess960)){
        // The rooks must be on a1, h1, a8 or h8.
        white_castling &= (BB_A1 | BB_H1);
        black_castling &= (BB_A8 | BB_H8);

        // The kings must be on e1 or e8.
        if (!(bool(_white_occupied & _kings & ~_promoted & BB_E1))){
            white_castling = BB_EMPTY;
        }
        if (!(bool(_black_occupied & _kings & ~_promoted & BB_E8))){
            black_castling = BB_EMPTY;
        }
        return white_castling | black_castling;
    } else{
        // The kings must be on the back rank.
        Bitboard white_king_mask = _white_occupied & _kings & BB_RANK_1 & ~_promoted;
        Bitboard black_king_mask = _black_occupied & _kings & BB_RANK_8 & ~_promoted;
        if (!(white_king_mask)){
            white_castling = BB_EMPTY;
        }
        if (!(black_king_mask)){
            black_castling = BB_EMPTY;
        }

        // There are only two ways of castling, a-side and h-side, and the
        // king must be between the rooks.
        Bitboard white_a_side = white_castling & -white_castling;
        Bitboard white_h_side = white_castling ? BB_SQUARES[msb(white_castling)] : BB_EMPTY;
        if (bool(white_a_side) && (msb(white_a_side) > msb(white_king_mask))){
            white_a_side = BB_EMPTY;
        }
        if (bool(white_h_side) && (msb(white_h_side) < msb(white_king_mask))){
            white_h_side = BB_EMPTY;
        }

        Bitboard black_a_side = (black_castling & -black_castling);
        Bitboard black_h_side = black_castling ? BB_SQUARES[msb(black_castling)] : BB_EMPTY;
        if (bool(black_a_side) && (msb(black_a_side) > msb(black_king_mask))){
            black_a_side = BB_EMPTY;
        }
        if (bool(black_h_side) && (msb(black_h_side) < msb(black_king_mask))){
            black_h_side = BB_EMPTY;
        }

        // Done.
        return black_a_side | black_h_side | white_a_side | white_h_side;
    }
}

Move Board::_from_chess960(bool chess960, Square from_square, Square to_square, PieceType promotion, PieceType drop) const{
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

vector<Move> Board::generate_castling_moves(Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    Bitboard backrank = _turn ? BB_RANK_1 : BB_RANK_8;
    Bitboard king = occupied_co(_turn) & _kings & ~_promoted & backrank & from_mask;
    king = king & -king;
    if (!(king)){
        return moves_vector;
    }

    SquareSet squareset(clean_castling_rights() & backrank & to_mask);
    for (Square candidate = squareset.start(); squareset.squares_left(); squareset.next(candidate)){
        Bitboard rook = BB_SQUARES[candidate];
        bool a_side = rook < king;
        Bitboard king_to = (a_side ? BB_FILE_C : BB_FILE_G) & backrank;
        Bitboard rook_to = (a_side ? BB_FILE_D : BB_FILE_F) & backrank;
        Bitboard king_path = between(msb(king), msb(king_to));
        Bitboard rook_path = between(candidate, msb(rook_to));
        if (!((_occupied ^ king ^ rook) & (king_path | rook_path | king_to | rook_to) ||
            _attacked_for_king(king_path | king, _occupied ^ king) ||
            _attacked_for_king(king_to, _occupied ^ king ^ rook ^ rook_to))){
            moves_vector.push_back(_from_chess960(_chess960, msb(king), candidate));
        }
    }
    return moves_vector;
}

Bitboard Board::_attacks_mask(Square square, Bitboard occupied) const{
    Bitboard bb_square = BB_SQUARES[square];
    if (bb_square & _pawns){
        return BB_PAWN_ATTACKS[color_at(square)][square];
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

Bitboard Board::attacks_mask(Square square){
    return _attacks_mask(square, _occupied);
}

vector<Move> Board::generate_pseudo_legal_ep(Bitboard from_mask, Bitboard to_mask){
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

    Ray rank = _turn ? 4 : 3;
    Bitboard capturers = _pawns & occupied_co(_turn) & from_mask & BB_PAWN_ATTACKS[!(_turn)][_ep_square] & BB_RANKS[rank];

    SquareSet squareset(capturers);
    for (Square capturer = squareset.start(); squareset.squares_left(); squareset.next(capturer)){
        moves_vector.push_back(Move(capturer, _ep_square));
    }
    return moves_vector;
}

vector<Move> Board::generate_pseudo_legal_moves(Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector;
    Bitboard our_pieces;
    Bitboard opponent_pieces;
    if (_turn){
        our_pieces = _white_occupied;
        opponent_pieces = _black_occupied;
    } else{
        our_pieces = _black_occupied;
        opponent_pieces = _white_occupied;
    }

    // Generate piece moves.
    Bitboard non_pawns = our_pieces & ~_pawns & from_mask;
    SquareSet non_pawns_squareset = SquareSet(non_pawns);
    for (Square from_square = non_pawns_squareset.start(); non_pawns_squareset.squares_left(); non_pawns_squareset.next(from_square)){
        Bitboard moves = attacks_mask(from_square) & ~our_pieces & to_mask;
        SquareSet move_squareset = SquareSet(moves);
        for (Square to_square = move_squareset.start(); move_squareset.squares_left(); move_squareset.next(to_square)){
            moves_vector.push_back(Move(from_square, to_square));
        }
    }

    // Generate castling moves.
    if (from_mask & _kings){
        vector<Move> castling_moves_vector = generate_castling_moves(from_mask, to_mask);
        copy (castling_moves_vector.begin(), castling_moves_vector.end(), back_inserter(moves_vector));
    }

    // The remaining moves are all pawn moves.
    Bitboard pawns = _pawns & our_pieces & from_mask;
    if (!(pawns)){
        return moves_vector;
    }

    // Generate pawn captures.
    Bitboard capturers = pawns;
    SquareSet capturers_squareset = SquareSet(capturers);
    for (Square from_square = capturers_squareset.start(); capturers_squareset.squares_left(); capturers_squareset.next(from_square)){
        Bitboard targets = BB_PAWN_ATTACKS[_turn][from_square] & opponent_pieces & to_mask;
        SquareSet targets_squareset = SquareSet(targets);
        for (Square to_square = targets_squareset.start(); targets_squareset.squares_left(); targets_squareset.next(to_square)){
            if (!(square_rank(to_square) % 7)){
                for (PieceType piece_type = 5; piece_type > 1; piece_type--){
                    moves_vector.push_back(Move(from_square, to_square, piece_type));
                }
            } else{
                moves_vector.push_back(Move(from_square, to_square));
            }
        }
    }

    // Prepare pawn advance generation.
    Bitboard single_moves = _turn ? pawns << 8 & ~_occupied : pawns >> 8 & ~_occupied;
    Bitboard double_moves = _turn ? single_moves << 8 & ~_occupied & (BB_RANK_3 | BB_RANK_4) : single_moves >> 8 & ~_occupied & (BB_RANK_6 | BB_RANK_5);
    single_moves &= to_mask;
    double_moves &= to_mask;

    // Generate single pawn moves.
    SquareSet single_moves_squareset = SquareSet(single_moves);
    for (Square to_square = single_moves_squareset.start(); single_moves_squareset.squares_left(); single_moves_squareset.next(to_square)){
        Square from_square = _turn ? to_square - 8 : to_square + 8;
        if (!(square_rank(to_square) % 7)){
            for (PieceType piece_type = 5; piece_type > 1; piece_type--){
                moves_vector.push_back(Move(from_square, to_square, piece_type));
            }
        } else{
            moves_vector.push_back(Move(from_square, to_square));
        }
    }

    // Generate double pawn moves.
    SquareSet double_moves_squareset(double_moves);
    for (Square to_square = double_moves_squareset.start(); double_moves_squareset.squares_left(); double_moves_squareset.next(to_square)){
        Square from_square = _turn ? to_square - 16 : to_square + 16;
        moves_vector.push_back(Move(from_square, to_square));
    }

    // Generate en passant captures.
    if (_ep_square != NO_SQUARE){
        vector<Move> pseudo_legal_ep_vector = generate_pseudo_legal_ep(from_mask, to_mask);
        copy (pseudo_legal_ep_vector.begin(), pseudo_legal_ep_vector.end(), back_inserter(moves_vector));
    }

    return moves_vector;
}

Bitboard Board::_slider_blockers(Square king){
    Bitboard rooks_and_queens = _rooks | _queens;
    Bitboard bishops_and_queens = _bishops | _queens;
    Bitboard snipers = (BB_RANK_ATTACKS[king][0] & rooks_and_queens) | (BB_FILE_ATTACKS[king][0] & rooks_and_queens) | (BB_DIAG_ATTACKS[king][0] & bishops_and_queens);
    Bitboard blockers = 0;

    SquareSet squareset(snipers & occupied_co(!(_turn)));
    for (Square sniper = squareset.start(); squareset.squares_left(); squareset.next(sniper)){
        Bitboard b = between(king, sniper) & _occupied;
        // Add to blockers if exactly one piece in-between.
        if (bool(b) && BB_SQUARES[msb(b)] == b){
            blockers |= b;
        }
    }

    return blockers & occupied_co(_turn);
}

vector<Move> Board::_generate_evasions(Square king, Bitboard checkers, Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector;
    Bitboard sliders = checkers & (_bishops | _rooks | _queens);
    Bitboard attacked = 0;

    SquareSet sliders_squareset = SquareSet(sliders);
    for (Square checker = sliders_squareset.start(); sliders_squareset.squares_left(); sliders_squareset.next(checker)){
        attacked |= ray(king, checker) & ~BB_SQUARES[checker];
    }

    if (BB_SQUARES[king] & from_mask){
        SquareSet squareset(BB_KING_ATTACKS[king] & ~occupied_co(_turn) & ~attacked & to_mask);
        for (Square to_square = squareset.start(); squareset.squares_left(); squareset.next(to_square)){
            moves_vector.push_back(Move(king, to_square));
        }
    }

    Square checker = msb(checkers);
    if (BB_SQUARES[checker] == checkers){
        // Capture or block a single checker.
        Bitboard target = between(king, checker) | checkers;
        vector<Move> pseudo_legal_moves_vector = generate_pseudo_legal_moves(~_kings & from_mask, target & to_mask);
        copy (pseudo_legal_moves_vector.begin(), pseudo_legal_moves_vector.end(), back_inserter(moves_vector));

        // Capture the checking pawn en passant (but avoid yielding duplicate moves).
        if (_ep_square != NO_SQUARE && !(bool(BB_SQUARES[_ep_square] & target))){
            Square last_double = _turn ? _ep_square - 8 : _ep_square + 8;
            if (last_double == checker){
                vector<Move> pseudo_legal_ep_vector = generate_pseudo_legal_ep(from_mask, to_mask);
                copy (pseudo_legal_ep_vector.begin(), pseudo_legal_ep_vector.end(), back_inserter(moves_vector));
            }
        }
    }
    return moves_vector;
}

bool Board::is_castling(const Move &move){
    // Checks if the given pseudo-legal move is a castling move.
    if (_kings & BB_SQUARES[move._from_square]){
        Ray from_file = square_file(move._from_square);
        Ray to_file = square_file(move._to_square);
        unsigned char diff = (from_file > to_file) ? from_file - to_file : to_file - from_file;
        if (diff > 1){
            return true;
        }
        return _rooks & occupied_co(_turn) & BB_SQUARES[move._to_square];
    }
    return false;
}

bool Board::is_kingside_castling(const Move &move){
    // Checks if the given pseudo-legal move is a kingside castling move.
    if (square_file(move._to_square) > square_file(move._from_square)){
        return is_castling(move);
    }
    return false;
}

bool Board::is_queenside_castling(const Move &move){
    // Checks if the given pseudo-legal move is a queenside castling move.
    if (square_file(move._to_square) < square_file(move._from_square)){
        return is_castling(move);
    }
    return false;
}

bool Board::is_attacked_by(bool color, Square square){
        return attackers_mask(color, square);
}

bool Board::is_en_passant(const Move &move) const{
    ///Checks if the given pseudo-legal move is an en passant capture.
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

bool Board::_ep_skewered(Square king, Square capturer){
    Square last_double = _turn ? _ep_square - 8 : _ep_square + 8;
    Bitboard occupancy = _occupied & ~BB_SQUARES[last_double] & (~BB_SQUARES[capturer] | BB_SQUARES[_ep_square]);

    // Horizontal attack on the fifth or fourth rank.
    Bitboard horizontal_attackers = occupied_co(!(_turn)) & (_rooks | _queens);
    if (BB_RANK_ATTACKS[king][BB_RANK_MASKS[king] & occupancy] & horizontal_attackers){
        return true;
    }

    Bitboard diagonal_attackers = occupied_co(!(_turn)) & (_bishops | _queens);
    if( BB_DIAG_ATTACKS[king][BB_DIAG_MASKS[king] & occupancy] & diagonal_attackers){
        return true;
    }
    return false;
}

Bitboard Board::pin_mask(bool color, Square square) const{
    Square king = find_king_square(color);
    Bitboard square_mask = BB_SQUARES[square];
    map<Bitboard, Bitboard>* attacks_pointers_array[3] = {BB_FILE_ATTACKS, BB_RANK_ATTACKS, BB_DIAG_ATTACKS};
    const Bitboard sliders_array[3] = {_rooks | _queens, _rooks | _queens, _bishops | _queens};
    for (unsigned short int i = 0; i < 3; i++){
        const Bitboard &rays = attacks_pointers_array[i][king][0];
        if (rays & square_mask){
            Bitboard snipers = rays & sliders_array[i] & occupied_co(!(color));
            SquareSet squareset(snipers);
            for (Square sniper = squareset.start(); squareset.squares_left(); squareset.next(sniper)){
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
    // Detects if the given square is pinned to the king of the given color.
    return pin_mask(color, square) != BB_ALL;
}

bool Board::_is_safe(Square king, Bitboard blockers, const Move &move){
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

vector<Move> Board::generate_legal_moves(Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    Bitboard king_mask = _kings & occupied_co(_turn);
    if (king_mask){
        Square king = msb(king_mask);
        Bitboard blockers = _slider_blockers(king);
        vector<Move> possible_moves_vector = _checkers ? _generate_evasions(king, _checkers, from_mask, to_mask) : generate_pseudo_legal_moves(from_mask, to_mask);
        copy_if(possible_moves_vector.begin(), possible_moves_vector.end(), back_inserter(moves_vector), [this, king, blockers] (const Move &move){return _is_safe(king, blockers, move);});
        return moves_vector;
    } else{
        return generate_pseudo_legal_moves(from_mask, to_mask);
    }
}

vector<Move> Board::generate_legal_checks(Bitboard from_mask, Bitboard to_mask){
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
    // Checks if the given pseudo-legal move is a capture or pawn move.
    Bitboard touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return bool(touched & _pawns) || bool(touched & occupied_co(!(_turn))) || move._drop == 1;
}

void Board::increase_repetition_map(unsigned short int increment){
    _repetition_map.try_emplace(_transposition_key, 0);
    _repetition_map[_transposition_key] += increment;
}

void Board::decrease_repetition_map(unsigned short int decrement){
    if (DEBUG){
        if (_repetition_map.find(_transposition_key) == _repetition_map.end()){
            cout << "Trying to decrease repetition on a position which is not in the repetition map!" << endl << endl;
            raise_error();
        }
    }
    unsigned short int &num_repetitions = _repetition_map[_transposition_key];
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

unsigned short int Board::get_repetition_count(){
    if (_repetition_map.find(_transposition_key) == _repetition_map.end()){
        return 0;
    }
    return _repetition_map[_transposition_key];
}

void Board::update_checkers(){
    Bitboard king_mask = _kings & occupied_co(_turn);
    _checkers = king_mask ? attackers_mask(!(_turn), msb(king_mask)) : 0;
}

void Board::_push_capture(const Move &move, Square capture_square, PieceType piece_type, bool was_promoted){}

void Board::push(Move move){
    // Push move and remember board state.
    move = _to_chess960(move);
    _BoardState board_state = _board_state();
    _castling_rights = clean_castling_rights(); // Before pushing stack
    _move_stack.push(_from_chess960(_chess960, move._from_square, move._to_square, move._promotion, move._drop));
    _stack.push(board_state);

    // Reset en passant square.
    const Square ep_square = _ep_square;
    _ep_square = NO_SQUARE;

    // Increment move counters.
    _halfmove_clock++;
    if (!(_turn)){
        _fullmove_number++;
    }

    // On a null move, simply swap turns and reset the en passant square.
    if (!(move.is_valid())){
        swap_turn();
        increase_repetition_map();
        return;
    }

    // Drops.
    if (move._drop){
        _set_piece_at(move._to_square, move._drop, _turn);
        swap_turn();
        increase_repetition_map();
        return;
    }

    // Zero the half-move clock.
    if (is_zeroing(move)){
        _halfmove_clock = 0;
    }

    Bitboard from_bb = BB_SQUARES[move._from_square];
    Bitboard to_bb = BB_SQUARES[move._to_square];

    bool promoted = bool(_promoted & from_bb);
    PieceType piece_type = _remove_piece_at(move._from_square);
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
    Square capture_square = move._to_square;
    PieceType captured_piece_type = piece_type_at(capture_square);

    // Update castling rights.
    Bitboard old_castling_rights = _castling_rights;
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

    // Handle special pawn moves.
    if (piece_type == 1){
        char diff = move._to_square - move._from_square;
        if (diff == 16 && square_rank(move._from_square) == 1){
            _ep_square = move._from_square + 8;
        } else if (diff == -16 && square_rank(move._from_square) == 6){
            _ep_square = move._from_square - 8;
        } else if (move._to_square == ep_square && (diff == -9 || diff == -7 || diff == 7 || diff == 9) && !(captured_piece_type)){
            // Remove pawns captured en passant.
            char down = _turn ? -8 : 8;
            capture_square = ep_square + down;
            captured_piece_type = _remove_piece_at(capture_square);
        }
    }
    _transposition_key ^= ZOBRIST_ENPASSANT_KEY[ep_square] ^ ZOBRIST_ENPASSANT_KEY[_ep_square];

    // Promotion.
    if (move._promotion){
        promoted = true;
        piece_type = move._promotion;
    }

    // Castling.
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

    // Put the piece on the target square.
    if (!(castling)){
        bool was_promoted = bool(_promoted & to_bb);
        _set_piece_at(move._to_square, piece_type, _turn, promoted);
        if (captured_piece_type){
            _push_capture(move, capture_square, captured_piece_type, was_promoted);
        }
    }

    // Swap turn.
    swap_turn();

    // update checkers
    update_checkers();

    // update repetition
    increase_repetition_map();
    // if (DEBUG){
    //     if (_transposition_key != generate_transposition_key()){
    //         cout << "Transposition key error!" << endl;
    //         // pop();
    //         print_board();
    //         cout << endl << uci(_move_stack.top()) << endl;
    //         cout << hexadeimal(generate_transposition_key()) << endl;
    //         raise_error();
    //     }
    // }
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
    // Checks if the given pseudo-legal move is a capture.
    Bitboard touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return bool(touched & occupied_co(!(_turn))) || is_en_passant(move);
}

Square Board::get_capture_piece_square(const Move &move){
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

PieceType Board::get_capture_piece_type(const Move &move){
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

vector<Move> Board::generate_pseudo_legal_captures(Bitboard from_mask, Bitboard to_mask){
    vector<Move> captures_vector = generate_pseudo_legal_moves(from_mask, to_mask & occupied_co(!(_turn)));
    vector<Move> ep_captures_vector = generate_pseudo_legal_ep(from_mask, to_mask);
    copy (ep_captures_vector.begin(), ep_captures_vector.end(), back_inserter(captures_vector));
    return captures_vector;
}

bool Board::has_castling_rights(bool color){
    // Checks if the given side has castling rights.
    if ((color && _white_castling_status) || (!(color) && _black_castling_status)){
        return false;
    }
    Bitboard backrank = color ? BB_RANK_1 : BB_RANK_8;
    return bool(clean_castling_rights() & backrank);
}

bool Board::is_into_check(const Move &move){
    Square king = find_king_square(_turn);
    if (king == NO_SQUARE){
        return false;
    }
    // If already in check, look if it is an evasion.
    if (_checkers){
        vector<Move> evasions_vector = _generate_evasions(king, _checkers, BB_SQUARES[move._from_square], BB_SQUARES[move._to_square]);
        if (!(any_of(evasions_vector.begin(), evasions_vector.end(), [move] (const Move &m){return m == move;}))){
            return true;
        }
    }
    return !(_is_safe(king, _slider_blockers(king), move));
}

vector<Move> Board::generate_legal_ep(Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector;
    if (is_variant_end()){
        return moves_vector;
    }
    vector<Move> pseudo_legal_ep_moves = generate_pseudo_legal_ep(from_mask, to_mask);
    copy_if(pseudo_legal_ep_moves.begin(), pseudo_legal_ep_moves.end(), back_inserter(moves_vector), [this] (const Move &move){return !(is_into_check(move));});
    return moves_vector;
}

vector<Move> Board::generate_legal_captures(Bitboard from_mask, Bitboard to_mask){
    vector<Move> moves_vector = generate_legal_moves(from_mask, to_mask & occupied_co(!(_turn)));
    vector<Move> legal_ep_vector = generate_legal_ep(from_mask, to_mask);
    copy (legal_ep_vector.begin(), legal_ep_vector.end(), back_inserter(moves_vector));
    return moves_vector;
}

bool Board::_is_halfmoves(unsigned short int n){
    if (_halfmove_clock >= n){
        if (!(generate_legal_moves().empty())){
            return true;
        }
    }
    return false;
}

bool Board::is_seventyfive_moves(){
    // Since the 1st of July 2014, a game is automatically drawn (without
    // a claim by one of the players) if the half-move clock since a capture
    // or pawn move is equal to or greater than 150. Other means to end a game
    // take precedence.
    return _is_halfmoves(150);
}

bool Board::_reduces_castling_rights(const Move &move){
    Bitboard cr = clean_castling_rights();
    Bitboard touched = BB_SQUARES[move._from_square] ^ BB_SQUARES[move._to_square];
    return ((touched & cr) ||
            (cr & BB_RANK_1 && touched & _kings & occupied_co(true) & ~_promoted) ||
            (cr & BB_RANK_8 && touched & _kings & occupied_co(false) & ~_promoted));
}

bool Board::has_legal_en_passant(){
    return _ep_square != NO_SQUARE && !(generate_legal_ep().empty());
}

bool Board::is_irreversible(const Move &move){
    // Checks if the given pseudo-legal move is irreversible.

    // In standard chess, pawn moves, captures, moves that destroy castling
    // rights and moves that cede en passant are irreversible.

    // This method has false-negatives with forced lines. For example, a check
    // that will force the king to lose castling rights is not considered
    // irreversible. Only the actual king move is.
    return is_zeroing(move) || _reduces_castling_rights(move) || has_legal_en_passant();
}

bool Board::is_repetition(unsigned short int count){
    return get_repetition_count() >= count;
}

bool Board::is_threefold_repetition(){
    return is_repetition(3);
}

bool Board::is_fivefold_repetition(){
    // Since the 1st of July 2014 a game is automatically drawn (without
    // a claim by one of the players) if a position occurs for the fifth time.
    // Originally this had to occur on consecutive alternating moves, but
    // this has since been revised.
    return is_repetition(5);
}

bool Board::is_fifty_moves(){
    // Checks that the clock of halfmoves since the last capture or pawn move
    // is greater or equal to 100, and that no other means of ending the game
    // (like checkmate) take precedence.
    return _is_halfmoves(100);
}

bool Board::can_claim_fifty_moves(){
    // Checks if the player to move can claim a draw by the fifty-move rule.

    // In addition to :func:`~chess.Board.is_fifty_moves()`, the fifty-move
    // rule can also be claimed if there is a legal move that achieves this
    // condition.
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
    // Checks if the player to move can claim a draw by threefold repetition.

    // Draw by threefold repetition can be claimed if the position on the
    // board occurred for the third time or if such a repetition is reached
    // with one of the possible legal moves.

    // Note that checking this can be slow: In the worst case
    // scenario, every legal move has to be tested and the entire game has to
    // be replayed because there is no incremental transposition table.
    TranspositionKeyCounter transpositions = TranspositionKeyCounter();
    transpositions.update(_transposition_key);
    // Count positions.
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
    // Threefold repetition occurred.
    if (transpositions.get_count(_transposition_key) >= 3){
        return true;
    }
    // The next legal move is a threefold repetition.
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

unsigned char Board::outcome(bool claim_draw){
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

    // Claimable draws.
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
    // Checks if *color* has insufficient winning material.

    // This is guaranteed to return ``false`` if *color* can still win the
    // game.

    // The converse does not necessarily hold:
    // The implementation only looks at the material, including the colors
    // of bishops, but not considering piece positions. So fortress
    // positions or positions with forced lines may return ``false``, even
    // though there is no possible winning line.
    if (occupied_co(color) & (_pawns | _rooks | _queens)){
        return false;
    }

    // Knights are only insufficient material if:
    // (1) We do not have any other pieces, including more than one knight.
    // (2) The opponent does not have pawns, knights, bishops or rooks.
    //     These would allow selfmate.
    if (occupied_co(color) & _knights){
        return (popcount(occupied_co(color)) <= 2 && !(occupied_co(!(color)) & ~_kings & ~_queens));
    }

    // Bishops are only insufficient material if:
    // (1) We do not have any other pieces, including bishops of the
    //     opposite color.
    // (2) The opponent does not have bishops of the opposite color,
    //     pawns or knights. These would allow selfmate.
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
    // Checks if the current position is a checkmate.
    if (!(is_check())){
        return false;
    }
    return generate_legal_moves().empty();
}

Bitboard Board::pieces_mask(PieceType piece_type) const{
    switch (piece_type){
        case 1:
            return _pawns;
        case 2:
            return _knights;
        case 3:
            return _bishops;
        case 4:
            return _rooks;
        case 5:
            return _queens;
        case 6:
            return _kings;
        default:
            cout << "expected PieceType, got " << piece_type << endl;
            raise_error();
    }
    return 0;
}

Bitboard Board::pieces_mask(PieceType piece_type, bool color) const{
    Bitboard bb;
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
        return !(PASSED_PAWN_MASKS[color][square] & _pawns & occupied_co(!(color)));
    }
    return false;
}

string Board::_algebraic_without_suffix(const Move &move, bool _long){
    // Null move.
    if (!(move.is_valid())){
        return "--";
    }

    // Drops.
    if (move._drop){
        string san_string = "";
        if (move._drop != 1){
            san_string = Piece(move._drop, true).symbol();
        }
        san_string += "@" + SQUARE_NAMES[move._to_square];
        return san_string;
    }

    // Castling.
    if (is_castling(move)){
        if (square_file(move._to_square) < square_file(move._from_square)){
            return "O-O-O";
        } else{
            return "O-O";
        }
    }

    PieceType piece_type = piece_type_at(move._from_square);
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
        // Get ambiguous move candidates.
        // Relevant candidates: not exactly the current move,
        // but to the same square.
        Bitboard from_mask = pieces_mask(piece_type, _turn);
        from_mask &= ~BB_SQUARES[move._from_square];
        Bitboard to_mask = BB_SQUARES[move._to_square];
        vector<Move> moves_vector = generate_legal_moves(from_mask, to_mask);
        Bitboard others = accumulate(moves_vector.begin(), moves_vector.end(), 0, [](Bitboard bb, const Move &move){return bb | BB_SQUARES[move._from_square];});

        // Disambiguate.
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

    // Captures.
    if (capture){
        san_string += "x";
    } else if (_long){
        san_string += "-";
    }

    // Destination square.
    san_string += SQUARE_NAMES[move._to_square];

    // Promotion.
    if (move._promotion){
        san_string += "=";
        san_string += Piece(move._promotion, true).symbol();
    }

    return san_string;
}

string Board::_algebraic_and_push(const Move &move, bool _long){
    string san_string = _algebraic_without_suffix(move, _long);

    // Look ahead for check or checkmate.
    push(move);
    bool king_in_check = is_check();
    bool king_in_checkmate = (king_in_check && is_checkmate()) || is_variant_loss() || is_variant_win();

    // Add check or checkmate suffix.
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
    // Gets the standard algebraic notation of the given move in the context
    // of the current position.
    return _algebraic(move);
}

string Board::san_and_push(const Move &move){
    return _algebraic_and_push(move);
}

Board Board::copy_board(bool copy_stack) const{
    // Creates a copy of the board.
    // Defaults to copying the entire move stack. Alternatively, *stack* can
    // be ``false``, or an integer to copy a limited number of moves.
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
    // Null moves are not pseudo-legal.
    if (!(move.is_valid())){
        return false;
    }
    // Drops are not pseudo-legal.
    if (move._drop){
        return false;
    }
    // Source square must not be vacant.
    PieceType piece = piece_type_at(move._from_square);
    if (!(piece)){
        return false;
    }
    // Get square masks.
    Bitboard from_mask = BB_SQUARES[move._from_square];
    Bitboard to_mask = BB_SQUARES[move._to_square];
    // Check turn.
    if (!(occupied_co(_turn) & from_mask)){
        return false;
    }
    // Only pawns can promote and only on the backrank.
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
    // Handle castling.
    if (piece == 6){
        Move chess960_move = _from_chess960(_chess960, move._from_square, move._to_square);
        vector<Move> castling_moves_vector = generate_castling_moves();
        if (any_of(castling_moves_vector.begin(), castling_moves_vector.end(), [chess960_move] (const Move &m){return m == chess960_move;})){
            return true;
        }
    }
    // Destination square can not be occupied.
    if (occupied_co(_turn) & to_mask){
        return false;
    }
    // Handle pawn moves.
    if (piece == 1){
        vector<Move> pseudo_legal_moves_vector = generate_pseudo_legal_moves(from_mask, to_mask);
        if (any_of(pseudo_legal_moves_vector.begin(), pseudo_legal_moves_vector.end(), [move] (const Move &m){return m == move;})){
            return true;
        }
        return false;
    }
    // Handle all other pieces.
    return bool(attacks_mask(move._from_square) & to_mask);
}

bool Board::is_legal(const Move &move){
    return !(is_variant_end()) && is_pseudo_legal(move) && !(is_into_check(move));
}

string Board::variation_san(vector<Move> variation) const{
    // Given a sequence of moves, returns a string representing the sequence
    // in standard algebraic notation (e.g., ``1. e4 e5 2. Nf3 Nc6`` or
    // ``37...Bg6 38. fxg6``).
    // The board will not be modified as a result of calling this.
    // :raises: :exc:`ValueError` if any moves in the sequence are illegal.
    // Board board = copy_board(false);
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
    for (unsigned short int i = 0; i < san_vector.size() - 1; i++){
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
    for (unsigned short int i = 0; i < _move_stack.size(); i++){
        moves_vector.push_back((*d)[i]);
    }
    Board board;
    return board.variation_san(moves_vector);
}

// Move Board::parse_san(string san_string){
//     // Uses the current position as the context to parse a move in standard
//     // algebraic notation and returns the corresponding move object.

//     // Ambiguous moves are rejected. Overspecified moves (including long
//     // algebraic notation) are accepted.

//     // The returned move is guaranteed to be either legal or a null move.

//     // :raises: :exc:`ValueError` if the SAN is invalid, illegal or ambiguous.

//     // Castling.
//     vector<Move> castling_moves_vector = generate_castling_moves();
//     if (san == "O-O" || san == "O-O+" || san == "O-O#" || san == "0-0" || san == "0-0+" || san == "0-0#"){
//         for (Move move : castling_moves_vector){
//             if (is_kingside_castling(move)){
//                 return move;
//             }
//         }
//     } else if (san == "O-O-O" || san == "O-O-O+" || san == "O-O-O#" || san == "0-0-0" || san == "0-0-0+" || san == "0-0-0#"){
//         for (Move move : castling_moves_vector){
//             if (is_queenside_castling(move)){
//                 return move;
//             }
//         }
//     } else{
//         cout << "illegal san: " << san << " in " << get_fen() << endl;
//         raise_error();
//     }

//     // Match normal moves.
//     match = SAN_REGEX.match(san)
//     if not match:
//         // Null moves.
//         if san in ["--", "Z0", "0000", "@@@@"]:
//             return Move.null()
//         elif "," in san:
//             raise ValueError(f"unsupported multi-leg move: {san!r}")
//         else:
//             raise ValueError(f"invalid san: {san!r}")

//     // Get target square. Mask our own pieces to exclude castling moves.
//     to_square = SQUARE_NAMES.index(match.group(4))
//     to_mask = BB_SQUARES[to_square] & ~occupied_co(_turn)

//     // Get the promotion piece type.
//     p = match.group(5)
//     promotion = PIECE_SYMBOLS.index(p[-1].lower()) if p else None

//     // Filter by original square.
//     from_mask = BB_ALL
//     if match.group(2):
//         from_file = FILE_NAMES.index(match.group(2))
//         from_mask &= BB_FILES[from_file]
//     if match.group(3):
//         from_rank = int(match.group(3)) - 1
//         from_mask &= BB_RANKS[from_rank]

//     // Filter by piece type.
//     if match.group(1):
//         piece_type = PIECE_SYMBOLS.index(match.group(1).lower())
//         from_mask &= pieces_mask(piece_type, _turn)
//     elif match.group(2) and match.group(3):
//         // Allow fully specified moves, even if they are not pawn moves,
//         // including castling moves.
//         move = find_move(square(from_file, from_rank), to_square, promotion)
//         if move._promotion == promotion:
//             return move
//         else:
//             raise ValueError(f"missing promotion piece type: {san!r} in {get_fen()}")
//     else:
//         from_mask &= pawns

//         // Do not allow pawn captures if file is not specified.
//         if not match.group(2):
//             from_mask &= BB_FILES[square_file(to_square)]

//     // Match legal moves.
//     matched_move = None
//     for move in generate_legal_moves(from_mask, to_mask):
//         if move._promotion != promotion:
//             continue

//         if matched_move:
//             raise ValueError(f"ambiguous san: {san!r} in {get_fen()}")

//         matched_move = move

//     if not matched_move:
//         raise ValueError(f"illegal san: {san!r} in {get_fen()}")

//     return matched_move
// }

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
    // Parses a move in standard algebraic notation, makes the move and puts
    // it onto the move stack.
    // Returns the move.

    // :raises: :exc:`ValueError` if neither legal nor a null move.
    Move move = parse_san(san_string);
    push(move);
    return move;
}

string Board::uci(const Move &move) const{
    // Gets the UCI notation of the move.
    Move chess960_move = _to_chess960(move);
    chess960_move = _from_chess960(_chess960, chess960_move._from_square, chess960_move._to_square, chess960_move._promotion, chess960_move._drop);
    return chess960_move.uci();
}

Move Board::parse_uci(const string &uci){
    // Parses the given move in UCI notation.
    // Supports both Chess960 and standard UCI notation.
    // The returned move is guaranteed to be either legal or a null move.
    // :raises: :exc:`ValueError` if the move is invalid or illegal in the
    //     current position (but not a null move).
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
    // Parses a move in UCI notation and puts it on the move stack.
    // Returns the move.
    // :raises: :exc:`ValueError` if the move is invalid or illegal in the
    //     current position (but not a null move).
    const Move &move = parse_uci(uci);
    push(move);
    return move;
}

Perft::Perft(Board &board, bool enable_transposition_table){
    _board_pointer = &board;
    _enable_transposition_table = enable_transposition_table;
}

unsigned long long Perft::perft(unsigned short int depth, bool print){
    unsigned long long key = _board_pointer->_transposition_key;
    if (_enable_transposition_table){
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