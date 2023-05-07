import os, subprocess, time
from chess import *
import chess.polyglot as polyglot

class Bot:

    # compile_command = "/usr/bin/g++ -Ofast -static -mavx2 -funroll-loops -fwhole-program main.cpp -o timecat"
    compile_command = "/usr/bin/g++ -Ofast -static -mavx2 -funroll-loops main.cpp -o timecat"
    book_paths = tuple(os.path.abspath(os.path.join("assets", "books", name)) for name in (
        "pecg_book.bin",
        "human.bin",
        "computer.bin",
    ))

    def __init__(self, rd, use_book_moves = False):
        self.rd = rd
        self.use_book_moves = use_book_moves
        self.board = Board()
        self._timecat = subprocess.Popen(
            "./timecat",
            universal_newlines=True,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        for _ in range(2):
            self._read_line()
        self._has_quit_command_been_sent = False

    def set_fen(self, fen : str) -> None:
        self.board.set_fen(fen)
        self._put(f"position fen {fen}")

    @classmethod
    def compile(cls):
        os.system(cls.compile_command)

    def get_best_move(self, print_move = True, self_time_left = 0, opponent_time_left = 0):
        if self.use_book_moves:
            move = self.get_book_move()
        else:
            move = None
        if move:
            move_uci = move.uci()
            if print_move:
                print(f"Book Move: {self.board.san(move)}")
        if move is None:
            # command = f"./timecat {self.rd} {repr(self.board.fen())}"
            # move_uci = subprocess.getoutput(command).strip()
            start_time = time.time()
            self._put(f"go depth {self.rd}")
            move_uci, predicted_score, current_score, num_nodes_searchd, game_phase, depth_searched, pv_line = self.get_all_informations()
            time_taken = time.time() - start_time
            if print_move:
                print()
                print(f"Fen: {self.board.fen()}")
                print(f"Predicted Move: {self.board.san(Move.from_uci(move_uci))}")
                print(f"predicted score: {predicted_score}")
                print(f"Current Score: {current_score}")
                print(f"Num Nodes Searchd: {num_nodes_searchd}")
                print(f"Nodes Per Second: {round(num_nodes_searchd / time_taken)}")
                print(f"Game Phase: {game_phase}")
                print(f"Depth Searched: {depth_searched}")
                print(f"PV Line: {pv_line}")
                print(f"Time Taken: {round(time_taken, 2)}")
                print()
        return move_uci

    def get_all_informations(self):
        s = self._read_line()
        if s:
            try:
                s, pv_line = s.split("  ")
                move_uci, predicted_score, current_score, num_nodes_searchd, game_phase, depth_searched = s.split(" ")
            except:
                print("\n"*3)
                print(s)
                while True:
                    s = self._read_line()
                    if not s:
                        break
                    print(s)
                self.kill()
                exit()
            return move_uci, predicted_score, current_score, int(num_nodes_searchd), float(game_phase), int(depth_searched), pv_line
        else:
            print("\n"*3)
            print(s)
            while True:
                s = self._read_line()
                if not s:
                    break
                print(s)
            self.kill()
            exit()

    def apply_move(self, move_uci):
        move = Move.from_uci(move_uci)
        self.board.push(move)
        self._put(f"push {move.uci()}")
    
    def get_book_move(self):
        for book in self.book_paths:
            try:
                move = polyglot.MemoryMappedReader(book).weighted_choice(self.board).move
            except:
                pass
            else:
                return move
    
    def kill(self):
        self._put("q")
    
    def _put(self, command: str) -> None:
        if not self._timecat.stdin:
            raise BrokenPipeError()
        if self._timecat.poll() is None and not self._has_quit_command_been_sent:
            self._timecat.stdin.write(f"{command}\n")
            self._timecat.stdin.flush()
            if command == "quit":
                self._has_quit_command_been_sent = True

    def _read_line(self) -> str:
        if not self._timecat.stdout:
            raise BrokenPipeError()
        return self._timecat.stdout.readline().strip()
    
    def __del__(self):
        self.kill()
        del self