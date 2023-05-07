import os, subprocess, pygame, string
from chess import Board, Move, STARTING_FEN
from pprint import pprint
from bot import Bot as MyBot
from stockfish_bot import Bot as StockfishBot
from statistics import mean, stdev

if os.path.isfile("timecat"):
    os.remove("timecat")

print("Compiling ...")
MyBot.compile()
print("Compiled!")

if not os.path.isfile("timecat"):
    exit()

def natural_number_generator_func():
    n = 0
    while True:
        n += 1
        yield n

natural_number_generator = natural_number_generator_func()

class ChessBoardGUI(Board):

    resolution = (900, 900)
    # resolution = (800, 400)
    assets_dir = os.path.abspath("assets")
    max_fps = 60
    board_colors = ["brown", "yellow"][::-1]
    selected_cell_color = "green"
    last_move_cell_color = "indigo"
    possible_moves_circle_color = "grey"
    is_capture_color = "red"
    pieces = "BKNPQRbknpqr"
    pieces_types = ["white", "black"]

    def __init__(self, first_player: MyBot = None, second_player: StockfishBot = None, reverse_board = None, delay_fps = True, play_online = True, stockfish_rating = None, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.first_player = first_player
        self.second_player = second_player
        if stockfish_rating:
            for bot in (first_player, second_player):
                if isinstance(bot, StockfishBot):
                    bot.set_rating(stockfish_rating)
        if reverse_board is None:
            if first_player and second_player:
                self.reverse_board = False
            elif first_player and not second_player:
                self.reverse_board = True
                if play_online:
                    self.reverse_board = not self.reverse_board
            elif not first_player and second_player:
                self.reverse_board = False
                if play_online:
                    self.reverse_board = not self.reverse_board
            else:
                self.reverse_board = False
        else:
            self.reverse_board = reverse_board
        if self.first_player and self.second_player and delay_fps:
            self.max_fps = 1
        self._last_move_uci = None
        self.cell_dimension = tuple(i/8 for i in self.resolution)
        self._initialize_important_variables()

    def _generate_pieces(self):
        self.images = {}
        for piece in self.pieces:
            image_path = os.path.join(self.assets_dir, "pieces", f"{piece}.png")
            self.images[piece] = pygame.transform.scale(
                # pygame.image.load(image_path),
                # pygame.image.load(image_path).convert(),
                pygame.image.load(image_path).convert_alpha(),
                self.cell_dimension,
            )

    def _initialize_important_variables(self):
        self._running_gui = False
        self._board_redraw_needed = False
        self._selected_cell = None
        self._game_over = False
        self.pgn = ""

    def _draw_board(self):
        pieces_unordered_map = self.piece_map()
        coordinate = self.uci_to_coordinate(self._selected_cell) if self._selected_cell else None
        if self.reverse_board:
            pieces_unordered_map = {63-i:j for i, j in pieces_unordered_map.items()}
            if coordinate:
                coordinate = (7-i for i in coordinate)
        if self._last_move_uci:
            _from, _to = (self.uci_to_coordinate(i) for i in (self._last_move_uci[:2], self._last_move_uci[2:]))
        for r in range(8):
            for c in range(8):
                color = self.board_colors[(r+c)%2] if coordinate != (c, r) else self.selected_cell_color
                if self._last_move_uci:
                    if ((7-c, 7-r) if self.reverse_board else (c, r)) in (_from, _to):
                        color = self.last_move_cell_color
                pygame.draw.rect(
                    self.screen,
                    color,
                    pygame.Rect(
                        r*self.cell_dimension[0],
                        c*self.cell_dimension[1],
                        self.cell_dimension[0],
                        self.cell_dimension[1],
                    ),
                )
                try:
                    piece = pieces_unordered_map[self.coordinate_to_pygame_number((r, c))]
                except KeyError:
                    pass
                else:
                    symbol = piece.symbol()
                    self.screen.blit(
                        self.images[symbol],
                        pygame.Rect(
                            r*self.cell_dimension[0],
                            c*self.cell_dimension[1],
                            self.cell_dimension[0],
                            self.cell_dimension[1],
                        ),
                    )

    def _redraw_board(self):
        self._draw_board()
        if self._selected_cell:
            for move in self.legal_moves:
                uci = move.uci()
                if uci[:2] == self._selected_cell:
                    row, col = self.uci_to_coordinate(uci[2:])
                    if self.reverse_board:
                        row, col = 7-row, 7-col
                    color = self.is_capture_color if self.is_capture(Move.from_uci(uci)) else self.possible_moves_circle_color
                    pygame.draw.circle(
                        self.screen,
                        color,
                        [(col+0.5)*self.resolution[0]/8, (row+0.5)*self.resolution[1]/8],
                        min(self.resolution)/16*0.3,
                        0,
                    )

    def _choose_piece_for_promotion(self): # not implemented properly
        return "q"

    def pawn_promotion_possible(self, move):
        return not self.is_legal(move) and self.is_legal(Move.from_uci(move.uci() + "q"))

    def _do_event_on_click(self):
        location = pygame.mouse.get_pos()
        if self.reverse_board:
            location = tuple(i-j for i, j in zip(self.resolution, location))
        col = int(location[0] // self.cell_dimension[0])
        row = int(location[1] // self.cell_dimension[1])
        clicked_cell = self.coordinate_to_uci((row, col))
        clicked_cell_piece = self.piece_at(self.uci_to_number(clicked_cell))
        if self._selected_cell:
            if self._selected_cell != clicked_cell:
                move = Move.from_uci(self._selected_cell + clicked_cell)
                # print(move, self.is_legal(move))
                # self.push(move)
                # print(self)
                if move.uci() in (i.uci() for i in self.legal_moves):
                    self.push_uci(move.uci())
                    self._selected_cell = None
                elif self.pawn_promotion_possible(move):
                    piece = self._choose_piece_for_promotion()
                    self.push_uci(self._selected_cell + clicked_cell + piece.lower())
                    self._selected_cell = None
                else:
                    if clicked_cell_piece:
                        if clicked_cell_piece.symbol().isupper() == self.turn:
                            self._selected_cell = clicked_cell
            else:
                self._selected_cell = None
        else:
            if clicked_cell_piece:
                if clicked_cell_piece.symbol().isupper() == self.turn:
                    self._selected_cell = clicked_cell
        self._board_redraw_needed = True

    def _handle_events(self, event):
        # print(event.type)
        if event.type == pygame.QUIT:
            self._running_gui = False
        elif event.type == pygame.MOUSEBUTTONDOWN and (not self.second_player or self.turn) and not self._game_over:
            self._do_event_on_click()

    @staticmethod
    def coordinate_to_uci(coordinate):
        return string.ascii_lowercase[coordinate[1]] + str(8-coordinate[0])

    @staticmethod
    def uci_to_coordinate(uci):
        return 7-(int(uci[1])-1), ord(uci[0])-97

    @staticmethod
    def uci_to_number(uci):
        row, col = (int(uci[1]))-1, ord(uci[0])-97
        return row*8+col

    @staticmethod
    def number_to_uci(uci):
        pass

    @staticmethod
    def coordinate_to_pygame_number(coordinate):
        return coordinate[0]+56-8*coordinate[1]

    @staticmethod
    def pygame_number_to_coordinate(number):
        return (number%8, 7-number//8)

    @staticmethod
    def coordinate_to_number(coordinate):
        return (7-coordinate[0])*8+coordinate[1]

    @staticmethod
    def number_to_coordinate(number):
        print("Hi", number, (7-(number//8), number%8))
        return (7-(number//8), number%8)
    
    def handle_game_over(self, font):
        if self.is_game_over():
            self._game_over = True
            if self.is_checkmate():
                statement, color, background_color = "Checkmate! {} wins!".format("Black" if self.turn else "White"), "red", "white"
            elif self.is_stalemate():
                statement, color, background_color = "Stalemate!", "green", "white"
            else:
                statement, color, background_color = "Draw!", "green", "white"
            print(statement)
            text = font.render(statement, True, color, background_color)
            text_rect = text.get_rect()
            text_rect.center = tuple(i/2 for i in self.resolution)
            self.screen.blit(text, text_rect)

    def run_gui(self):
        pygame.init()
        pygame.font.init()
        self.initial_turn = self.turn
        self.screen = pygame.display.set_mode(self.resolution)
        pygame.display.set_caption("Chess")
        font = pygame.font.SysFont("Comic Sans MS", 30)
        self._generate_pieces()
        self.clock = pygame.time.Clock()
        self.screen.fill(pygame.Color(255, 255, 255))
        self._draw_board()
        self._running_gui = True
        while self._running_gui:
            for event in pygame.event.get():
                self._handle_events(event)
            if self._board_redraw_needed:
                self._redraw_board()
                self._board_redraw_needed = False
            if not self._game_over:
                self.handle_game_over(font)
            pygame.display.flip()
            self.clock.tick(self.max_fps)
            if self.first_player and self.turn and not self._game_over:
                self.push_uci(self.first_player.get_best_move())
                continue
            if self.second_player and not self.turn and not self._game_over:
                self.push_uci(self.second_player.get_best_move())
                continue
            if save_game_moves:
                with open(file, "w") as wf:
                    wf.write(self.pgn.strip())
        pygame.quit()

    def push_uci(self, uci):
        move = self.parse_uci(uci)
        move_san = self.san(move)
        move_uci = move.uci()
        print(f"{'white' if self.turn else 'black'} played", move_san)
        self._last_move_uci = move_uci
        if self.first_player:
            self.first_player.apply_move(self._last_move_uci)
        if self.second_player:
            self.second_player.apply_move(self._last_move_uci)
        self._board_redraw_needed = True
        if save_game_moves:
            self.pgn += f"{str(next(natural_number_generator)) + '. ' if self.turn == self.initial_turn else ''}{move_san} "
        super().push(move)

    def set_fen(self, fen: str) -> None:
        super().set_fen(fen)
        if self.first_player:
            self.first_player.set_fen(fen)
        if self.second_player:
            self.second_player.set_fen(fen)

    @property
    def _turn(self):
        return self.turn

file = os.path.abspath(f".{os.sep}game_moves.txt")
save_game_moves = False
save_game_moves = True

stockfish_rating = None

# rd = 10
rd = 8
first_player = second_player = reverse_board = None
# first_player = MyBot(rd)
# first_player = MyBot(rd)
# second_player = StockfishBot(20)
# second_player = MyBot(rd)

# first_player = MyBot(rd, use_book_moves = False)
# second_player = StockfishBot(15)
# reverse_board = False

# first_player = StockfishBot(rd)
# second_player = MyBot(rd, use_book_moves = False)
# reverse_board = True

stockfish_rating = 2400

second_player = MyBot(rd, use_book_moves = False)
reverse_board = False

board = ChessBoardGUI(first_player = first_player, second_player = second_player, delay_fps = False, reverse_board = reverse_board, stockfish_rating = stockfish_rating)
board.set_fen(STARTING_FEN)
# board.set_fen("8/2Q3K1/8/8/8/8/4pk2/8 w - - 0 1")
# board.set_fen("8/8/8/8/4k3/8/8/Q6K w - - 0 1")
# board.set_fen("8/8/8/8/4k3/8/8/R6K w - - 0 1")
# board.set_fen("rr6/7p/2pk2p1/2Rp4/P7/1P6/2P2PPP/R4K2 w - - 1 28")
# board.set_fen("8/8/7p/4b2P/2P1Pk2/3K4/2B5/8 w - - 0 1")
# board.set_fen("7R/8/8/3k4/8/8/8/K7 w - - 3 8")

board.run_gui()
print(board.pgn.strip())

for player in (first_player, second_player):
    if isinstance(player, MyBot):
        player.kill()