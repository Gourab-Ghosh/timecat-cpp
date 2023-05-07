#include <iostream>
#include <string>
#include "board.cpp"
#include "constants.cpp"
#include "utils.cpp"
#include "engine.cpp"
#include "nnue/nnue_wrapper.cpp"
using namespace std;

void initialize_constants(){
    initialize_squares();
    initialize_ranks();
    initialize_files();
    assign_variable_values();
    initialize_nnue_constants();
}

// int main(int argc, char *argv[]){
//     int depth = int(*(argv[1])) - '0';
//     string fen = argv[2];

//     initialize_constants();
//     Board board(fen);
//     Engine engine(board);

//     cout << engine.get_best_move(depth, false).uci() << endl;
//     return 0;
// }

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
            char depth = input[6] - '0';
            cout << Perft(*engine.board, false).perft(depth, true) << endl << endl;
        } else if (input.rfind("go depth") == 0){
            char depth = stoi(input.substr(9));
            cout << engine.get_best_move(depth, false).uci() << " " << engine._last_predicted_score << " " << engine.evaluate_board(false) << " " << engine._num_nodes_searched << " " << engine.evaluator.get_game_phase() << " " << int(engine._last_depth_searched) << "  " << engine.get_pv_line() << endl;
        }
    }
    return 0;
}