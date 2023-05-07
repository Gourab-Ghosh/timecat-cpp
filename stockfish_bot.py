import os
from stockfish import Stockfish

class Bot:

    def __init__(self, recursion_depth = 18) -> None:
        self.stockfish = Stockfish("/usr/bin/stockfish", recursion_depth)

    def get_best_move(self):
        return self.stockfish.get_best_move()

    def apply_move(self, uci):
        self.stockfish.make_moves_from_current_position([uci])
    
    def set_fen(self, fen):
        self.stockfish.set_fen_position(fen)
    
    def set_rating(self, rating):
        self.stockfish.set_elo_rating(rating)