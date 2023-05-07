import time
from chess import *

board = Board()
def perft(board, n):
    nodes = 0
    if n == 1:
        for move in board.legal_moves:
            nodes += 1
        return nodes
    for move in board.legal_moves:
        board.push(move)
        nodes += perft(board, n-1)
        board.pop()
    return nodes

t = time.time()
print(perft(board, 5))
print(time.time() - t)