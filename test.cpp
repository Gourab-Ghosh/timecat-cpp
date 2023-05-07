#include <iostream>
#include <vector>
#include <chrono>
#include "board.cpp"
#include "constants.cpp"
#include "utils.cpp"
#include "engine.cpp"
#include "nnue/nnue_wrapper.cpp"
using namespace std;
using namespace std::chrono;

void initialize_constants(){
    initialize_squares();
    initialize_ranks();
    initialize_files();
    assign_variable_values();
    initialize_nnue_constants();
}

void test(bool use_hash_table = false){
    unsigned long long nodes;
    Board board;
    string fen = STARTING_FEN;
    bool final_res = true;

    // POSITION 1
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 4865609) << endl << endl;
    final_res = final_res && (nodes == 4865609);

    // POSITION 2
    fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 193690690) << endl << endl;
    final_res = final_res && (nodes == 193690690);

    // POSITION 3
    fen = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 674624) << endl << endl;
    final_res = final_res && (nodes == 674624);

    // POSITION 4
    fen = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 15833292) << endl << endl;
    final_res = final_res && (nodes == 15833292);
    fen = "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1 ";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 15833292) << endl << endl;
    final_res = final_res && (nodes == 15833292);

    // POSITION 5
    fen = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  ";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 89941194) << endl << endl;
    final_res = final_res && (nodes == 89941194);

    // POSITION 6
    fen = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10 ";
    board.set_fen(fen);
    board.print_board();
    cout << endl;
    nodes = Perft(board, use_hash_table).perft(5);
    cout << endl << nodes << " " << (nodes == 164075551) << endl << endl;
    final_res = final_res && (nodes == 164075551);

    cout << final_res << endl;
}

void play(int detph){
    Board board;
    Engine engine(board);
    unsigned long total_nodes_searched = 0;
    while (true){
        if (engine.board->is_game_over()){
        // if (engine.board->is_game_over() || engine.board->is_repetition(3) || engine.board->is_fifty_moves()){
            cout << "Game Over!" << endl;
            break;
        }
        Move move = engine.get_best_move(detph, false);
        if (move._from_square == 0 && move._to_square == 0){
            cout << "Got Null Move!" << endl;
            break;
        }
        cout << "Predicted Score: " << engine._last_predicted_score << endl;
        cout << "Current Score: " << engine.evaluate_board(false, false) << endl;
        // cout << "Current Score: " << engine.evaluate_board(false, true) << endl;
        cout << "Move: " << engine.board->san(move) << endl;
        cout << "Num Nodes Searched: " << engine._num_nodes_searched << endl;
        cout << "Game Phase: " << engine._game_phase << endl;
        cout << "Depth Searched: " << engine._last_depth_searched << endl;
        cout << "PV line: " << engine.get_pv_line() << endl;
        engine.board->push(move);
        engine.board->print_board();
        cout << endl;
        total_nodes_searched += engine._num_nodes_searched;
    }
    cout << endl << "result: " << int(engine.board->outcome()) << endl << endl << engine.board->game_pgn() << endl;
    cout << endl << "Total Nodes Searched: " << total_nodes_searched << endl;
}

int main(){
    cout << "Started main...\n\n";
    initialize_constants();
    Board board;
    Engine engine(board);

    // cout << ADJACENT_FILE_MASKS[15] << endl;

    // unsigned long long k = 0;
    // for (unsigned long long i = 545454154165415ULL; i < (545454154165415ULL + 100000000); i++){
    //     k += popcount(i);
    // }
    // cout << k << endl;

    // cout << popcount(545454154165415) << endl;

    // int rand_arr[] = {1,2,3,4,5,6};
    // // for (auto i : rand_arr){
    // //     cout << i << endl;
    // // }
    // cout << index(rand_arr, 5, 6) << endl;

    // board.push(Move(E2, E4));
    // board.push(Move(E7, E5));
    // board.push(Move(G1, F3));
    // board.push(Move(G8, F6));
    // board.push(Move(F1, E2));
    // board.push(Move(F8, E7));
    // board.push(Move(E1, G1));
    // board.print_board();
    // cout << endl << board._white_has_castled << endl;
    // cout << endl << board.game_pgn() << endl;

    // Move move = engine.get_best_move(5);
    // cout << move.uci() << endl;
    // engine.board->push(move);
    // move = engine.get_best_move(5);
    // cout << move.uci() << endl;

    // board.push(Move(D2, D4));
    // board.push(Move(E7, E5));
    // board.push(Move(G1, F3));
    // board.push(Move(E5, D4));
    // board.push(Move(E2, E4));
    // board.print_board();
    // for (Move move : board.generate_legal_checks()){
    //     cout << move.uci() << endl;
    // }

    // board.push(Move(G2, G3));
    // board.push(Move(G7, G6));
    // board.push(Move(F1, G2));
    // board.push(Move(F8, H6));
    // board.push(Move(G2, B7));
    // board.print_board();
    // for (Move move : board.generate_legal_checks()){
    //     cout << move.uci() << " " << board.is_into_check(move) << endl;
    // }

    // engine.board->push(Move(E2, E3));
    // // engine.board->push(Move(G7, G6));
    // // engine.board->push(Move(E3, E4));
    // // engine.board->push(Move(F8, H6));
    // // engine.board->push(Move(H2, H3));
    // engine.board->print_board();
    // cout << engine.alpha_beta(4, -inf, inf) << endl << engine.board->san(engine._pv_table[0][0]) << endl;
    // // cout << engine.quiescence(inf, -inf) << endl << engine.board->san(engine._pv_table[0][0]) << endl;

    // engine.set_fen("r1bqkb1r/pppp1ppp/2n1pn2/8/3P4/2N2N2/PPP1PPPP/R1BQKB1R w KQkq - 1 4");
    // Move move = Move(E2, E4);
    // for (unsigned long long i = 0; i < 10000; i++){
    //     engine.alpha_beta(1);
    // }

    // board.set_fen("r1bqkb1r/pppp1ppp/2n1pn2/8/3P4/2N2N2/PPP1PPPP/R1BQKB1R w KQkq - 1 4");
    // board.push(Move(E2, E4));
    // board.print_board();

    // const unsigned int a = 5;
    // cout << (a-1) << endl;

    // unsigned long long n = 0;
    // for (unsigned long long i = 1000000000000000000; i < 1000000000000000000 + 1000000000; i++){
    //     if (i & 137){
    //         n += lsb(i >> 2);
    //     } else{
    //         n += msb(i >> 1);
    //     }
    // }
    // cout << n << endl;

    // for (Square square = 63; square < 64; square--){
    //     cout << square << endl;
    // }

    // unsigned int a = 20;
    // int b = a - 30;
    // cout << b << endl;

    // unsigned long long a = BB_ALL & ~BB_SQUARES[63];
    // unsigned long long b = BB_SQUARES[30];
    // b |= -a;
    // cout << b << endl;

    // vector<Score> scores = {Score(-1, 3), Score(-9, 3), -Score(2, 2), -Score(3, 2), Score(7, 2), Score(5, 2), Score(10, 3), Score(-30), Score(1), Score(9, 2) + Score(8), Score(9, 2) + Score(9), -Score(9, 2) + Score(8), -Score(9, 2) + Score(9)};
    // // vector<Score> scores = {Score(-1, 3), Score(-9, 3), -Score(2, 2), -Score(3, 2), Score(7, 2), Score(5, 2), Score(10, 3), Score(-30), Score(1)};
    // sort(scores.begin(), scores.end());
    // for (Score score : scores){
    //     // cout << score << " " << endl;
    //     cout << score << " " << score._is_invalid << " " << score._normal << " " << score._checkmate << " " << score._infinity << endl;
    // }

    // engine.board->print_board();
    // cout << endl << engine.evaluate_board(4) / 100 << endl;
    // cout << endl << engine._num_nodes_searched << endl;

    // cout << (Score(1, 3) > Score(1, 3) - Score(0.00001)) << endl;
    // Score score = Score(1, 3) - 2;
    // cout << score << " " << score._score << " " << score._type << endl;

    // Score score1 = Score(1, 3) - Score(1, 2);
    // Score score2 = Score(1, 3) + Score(2, 2);
    // Score score3 = score1 - score2;
    // cout << score3 << " " << score3._score << endl;

    // // engine.set_fen("r1bqkb1r/pppp1ppp/2n2n2/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4");  // mate in 4 fen
    // // engine.set_fen("2r1q1kr/1b1p1pp1/ppnB1n1p/5P2/4p3/1PN1P1Q1/P1PPB1PP/R4RK1 w - - 3 21");  // random fen
    // // engine.set_fen("2k2b1r/p1p1pppp/p2r1n2/2N5/5q2/1PQ3P1/P4P1P/3R1RK1 b - - 0 1");  // check prediction accuracy fen
    // // engine.set_fen("2r3kr/1b1p2p1/1q1N1p1p/pp2nR2/1B4P1/1P1BP1Q1/P1PP2P1/5RK1 b - - 0 27");  // time consuming search fen 1
    // // engine.set_fen("rn1q1rk1/pbppb1pp/1p2p3/4Pp2/3P1N2/2PB4/P1P2PPP/1RBQ1RK1 w - f6 0 11");  // time consuming search fen 2
    // // engine.set_fen("r2q1rk1/ppp2pbp/1nnp2p1/8/2PP2b1/P2BBP2/1P2N1PP/RN1Q1RK1 b - - 0 11");  // time consuming search fen 3
    // // engine.set_fen("rnbqkbnr/pp3ppp/3p4/8/8/8/PPP1PPPP/RNBQKBNR w KQkq - 0 4");  // time consuming search fen 4
    // engine.set_fen("r1bqk1nr/pp2ppbp/2n3p1/2ppP3/5P2/2P2N2/PP1PB1PP/RNBQK2R b KQkq - 0 6");  // time consuming search fen 5
    // // engine.set_fen("r1bq1rk1/1p3ppn/1np1p2p/p7/P2PP3/3B1N2/1P1B1PPP/R1Q2RK1 w - - 0 16");  // time consuming search fen 6
    // // engine.set_fen("6k1/5p2/8/4Q3/8/7p/q2KN3/8 w - - 6 61");  // endgame fen 1
    // // engine.set_fen("8/8/8/8/5k2/5P1K/8/8 w - - 0 1"); // endgame fen 2
    // // engine.set_fen("8/8/8/8/7k/3n1p1P/4p3/4K3 w - - 4 66"); // endgame fen 3
    // // engine.set_fen("8/8/8/4n1k1/8/4pp2/7P/3K4 w - - 0 63"); // endgame fen 4
    engine.board->print_board();
    cout << endl << engine.board->san(engine.get_best_move(10)) << endl;
    cout << endl << engine._num_nodes_searched << endl;
    cout << engine.evaluator._num_times_board_evaluated << endl;

    // test();
    // cout << Perft(board, false).perft(6) << endl;
    // play(6);

    // // // engine.set_fen("8/8/8/8/4k3/8/8/R6K w - - 0 1");
    // // // engine.set_fen("8/2Q3K1/8/8/8/8/4pk2/8 w - - 0 1");
    // // engine.set_fen("8/p7/8/2b2kp1/2P5/4rN2/P1R3K1/8 b - - 1 45");
    // // engine.set_fen("r2q1rk1/pp2bpp1/2n2n1p/1Bpp4/4p3/1PN1P2b/PBPP1PPP/R2QR1K1 w - - 0 12");
    // engine.set_fen("r5k1/ppq2rbp/2p1Q1p1/5p2/2P5/2N5/PP3PPP/3RR1K1 w - - 0 21");
    // board._white_castling_status = 1;
    // board._black_castling_status = 1;
    // board.push(Move(G2, H3));
    // engine.board->print_board();
    // cout << endl;
    // cout << "Game Phase: " << engine._game_phase << endl;
    // cout << endl;
    // cout << engine.evaluate_board(false, true) << endl;
    // // cout << engine.evaluate_board(false, false) << endl;

    // board.push(Move(G1, F3));
    // board.push(Move(B8, C6));
    // board.push(Move(F3, G1));
    // board.push(Move(C6, B8));
    // board.push(Move(G1, F3));
    // board.push(Move(B8, C6));
    // board.push(Move(F3, G1));
    // board.push(Move(C6, B8));
    // for (int i = 0; i < 6; i++){
    //     board.pop();
    // }
    // board.print_board();
    // cout << endl << board.get_repetition_count() << endl;

    // board.push(Move(E2, E4));
    // board.push(Move(E7, E5));
    // board.push(Move(E1, E2));
    // board.push(Move(E8, E7));
    // board.push(Move(E2, E1));
    // board.push(Move(E7, E8));
    // board.print_board();
    // cout << endl << board.get_repetition_count() << endl;

    // board.set_fen("3r1k1r/6bp/p2P1qp1/1pBP3n/6p1/2N2Q2/PP5P/4RRK1 w - - 0 22");
    // board.print_board();
    // cout << engine.evaluate_board(false, true) << endl;

    // cout << sizeof(BB_ALL) << endl;

    // board.print_board();
    // cout << eval_position(board) << endl;

    // for (bool color : {true, false}){
    //     for (PieceType piece_type = 6; piece_type; piece_type--){
    //         cout << Piece(piece_type, color).symbol() << " " << int(nnue_piece(piece_type, color)) << endl;
    //     }
    // }

    // board.set_fen("rnbq4/pppp1k2/3b1n2/8/3Q4/P4N2/2P1PP1r/RNB1K1R1 w Q - 0 1");
    // board.set_fen("8/6k1/3R4/2P4P/5pB1/3bpP2/8/r5K1 w - - 8 67");
    // board.push_san("Kg2");
    // board.push_san("e2");
    // board.print_board();
    // cout << board.san(engine.get_best_move(10)) << endl;

    // cout << engine.evaluate_board() << endl;

    return 0;
}