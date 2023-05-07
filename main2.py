import os, sys, time, string, chess
# from chess.pgn import 
from pprint import pprint
from statistics import mean, stdev
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains
from bot import Bot
from credentials import USERNAME, PASSWORD

if "--play" in sys.argv:
    if os.path.isfile("timecat"):
        os.remove("timecat")
    print("Compiling ...")
    Bot.compile()
    print("Compiled!")
    if not os.path.isfile("timecat"):
        exit()

def natural_number_generator_func():
    n = 0
    while True:
        n += 1
        yield n

natural_number_generator = natural_number_generator_func()

class Browser:

    def __init__(self) -> None:
        self.driver = webdriver.Firefox()
        self.driver.maximize_window()
        self.driver.get("https://www.chess.com")
        self.logged_in = False
        self.board = chess.Board()
        self.board.initial_turn = self.board.turn
        self.bot = Bot(8, True)
        # self.bot = Bot(10, use_book_moves = False)
        # self.bot = Bot(5, use_book_moves = False)
        self.wait_time_for_finding_object = 60
        self.pgn = ""

    def login(self):
        login_button = self.driver.find_element(By.CSS_SELECTOR, ".button.auth.login.ui_v5-button-component.ui_v5-button-primary")
        login_button.click()
        username_input = self.driver.find_element(By.ID, "username")
        username_input.send_keys(USERNAME)
        password_input = self.driver.find_element(By.ID, "password")
        password_input.send_keys(PASSWORD)
        login_button = self.driver.find_element(By.ID, "login")
        login_button.click()
        self.logged_in = True

    def start_game(self, click_play_button = True):
        time.sleep(5)
        try:
            useless_irritating_shit_close_button = WebDriverWait(self.driver, 5).until(EC.presence_of_element_located((By.CSS_SELECTOR, ".icon-font-chess.x.ui_outside-close-icon")))
        except:
            pass
        else:
            useless_irritating_shit_close_button.click()
        # play_link = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.CSS_SELECTOR, ".nav-link-component.nav-link-new-main-design.nav-link-top-level.sprite.play-top")))
        play_link = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.CSS_SELECTOR, ".nav-link-component.nav-link-main-design.nav-link-top-level.sprite.play-top")))
        # play_link = self.driver.find_element(By.CSS_SELECTOR, ".nav-link-component.nav-link-new-main-design.nav-link-top-level.sprite.play-top")
        play_link.click()
        play_button = self.driver.find_element(By.CSS_SELECTOR, ".direct-menu-item-component.direct-menu-item")
        play_button.click()
        if click_play_button:
            time.sleep(5)
            play_button = self.driver.find_element(By.CSS_SELECTOR, ".ui_v5-button-component.ui_v5-button-primary.ui_v5-button-large.ui_v5-button-full")
            play_button.click()
            if not self.logged_in:
                play_as_guest_button = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.ID, "guest-button")))
                authentication_levels = self.driver.find_elements(By.CLASS_NAME, "authentication-intro-level")
                authentication_level = authentication_levels[-1]
                authentication_level.click()
                play_as_guest_button.click()
                time.sleep(5)
                # WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.CLASS_NAME, "competition-announcements-component")))
                play_button = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.CSS_SELECTOR, ".ui_v5-button-component.ui_v5-button-primary.ui_v5-button-large.ui_v5-button-full")))
                play_button.click()

    def play_game(self):
        print("Game Started...")
        if not self.logged_in:
            time.sleep(5)
        print("Started Playing...")
        self.chess_board = self.driver.find_element(By.TAG_NAME, "chess-board")
        self.board_flipped = "flipped" in self.chess_board.get_attribute("class")
        bot_color = not self.board_flipped
        white_clock = self.driver.find_element(By.CSS_SELECTOR, ".clock-white.player-clock")
        black_clock = self.driver.find_element(By.CSS_SELECTOR, ".clock-black.player-clock")
        detect_move = lambda: self.detect_move(white_clock, black_clock)
        while True:
            if self.is_game_over(True):
                break
            bot_turn = self.board.turn == bot_color
            bot_clock = white_clock if bot_color else black_clock
            opponent_clock = black_clock if bot_color else white_clock
            move = chess.Move.from_uci(self.bot.get_best_move(print_move = True, self_time_left = self.detect_time_left(bot_clock), opponent_time_left = self.detect_time_left(opponent_clock))) if bot_turn else detect_move()
            if move is None:
                break
            # move = chess.Move.from_uci(self.bot.get_best_move(debug=False)) if bot_turn else detect_move()
            self.push(move, bot_turn)

    def get_piece_unordered_map(self):
        pieces = self.driver.find_elements(By.CLASS_NAME, "piece")
        piece_map = {}
        for piece in pieces:
            try:
                classes = piece.get_attribute("class").strip().split(" ")
                detail = position = None
                for cls in classes:
                    if len(cls) == 2 and cls[0] in "wb" and cls[1] in "pnbrqk":
                        detail = cls
                    if cls.startswith("square"):
                        position = cls
                if detail is None or position is None:
                    return self.get_piece_unordered_map()
            except:
                return self.get_piece_unordered_map()
            row, col = tuple(int(i) for i in position[-2:])
            piece_symbol = detail[1].upper() if detail[0] == "w" else detail[1]
            piece = chess.Piece.from_symbol(piece_symbol)
            square = getattr(chess, f"{string.ascii_uppercase[row-1]}{col}")
            # square = f"{string.ascii_lowercase[row-1]}{col}"
            piece_map[square] = piece
        return piece_map

    def detect_turn(self, white_clock, black_clock):
        while True:
            if "clock-player-turn" in white_clock.get_attribute("class"):
                return True
            if "clock-player-turn" in black_clock.get_attribute("class"):
                return False
    
    def detect_time_left(self, clock):
        time_left_str = clock.text.strip()
        m, s = (float(i.strip()) for i in time_left_str.split(":"))
        return 60*m+s

    def detect_move(self, white_clock, black_clock, check_detect_turn = True):
        detect_turn = lambda: self.detect_turn(white_clock, black_clock)
        if check_detect_turn:
            while self.board.turn != detect_turn():
                if self.is_game_over():
                    return None
            # print(detect_turn())
        previous_turn = turn = self.board.turn
        board = self.board.copy()
        while previous_turn == turn:
            if self.is_game_over():
                return None
            turn = detect_turn()
        current_piece_unordered_map = self.get_piece_unordered_map()
        for move in board.legal_moves:
            board.push(move)
            if board.piece_map() == current_piece_unordered_map:
                return move
            board.pop()
        return self.detect_move(white_clock, black_clock, False)

    def close(self):
        self.driver.close()

    def square_to_coordinate(self, square):
        row, col = divmod(square, 8)
        if self.board_flipped:
            col = 7-col
        else:
            row = 7-row
        rect = self.chess_board.rect
        x = rect["x"]
        y = rect["y"]
        width = rect["width"]
        height = rect["height"]
        single_cell_width, single_cell_height = width/8, height/8
        return (col+0.5)*single_cell_width+x, (row+0.5)*single_cell_height+y

    def push(self, move: chess.Move, drag: bool):
        if move == chess.Move.null():
            raise Exception
        self.board.san(move)
        if self.is_game_over():
            return
        if drag:
            if self.is_game_over():
                return
            move_uci = move.uci()
            piece = self.driver.find_element(By.CLASS_NAME, f"square-{string.ascii_lowercase.index(move_uci[0])+1}{int(move_uci[1])}")
            action = ActionChains(self.driver)
            init_coord = self.square_to_coordinate(move.from_square)
            final_coord = self.square_to_coordinate(move.to_square)
            difference = (j-i for i, j in zip(init_coord, final_coord))
            action.drag_and_drop_by_offset(piece, *difference).perform()
            if move.promotion:
                promotion_piece_css_selector = f".promotion-piece.{'w' if self.board.turn else 'b'}{' pkbrqk'[move.promotion]}"
                promotion_piece = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.CSS_SELECTOR, promotion_piece_css_selector)))
                promotion_piece.click()
        self.pgn += f"{str(next(natural_number_generator)) + '. ' if self.board.turn == self.board.initial_turn else ''}{self.board.san(move)} "
        print(f"Move: {self.board.san(move)}")
        self.board.push(move)
        self.bot.apply_move(move.uci())

    def is_game_over(self, ignore_browser_check=False):
        try:
            self.driver.find_element(By.CLASS_NAME, "game-over-modal-content")
        except:
            pass
            # if ignore_browser_check:
            #     return self.board.is_game_over(claim_draw=True)
        else:
            self.pgn += self.pgn.strip()
            return True

    def start_and_play_game(self):
        self.start_game()
        move_list = WebDriverWait(self.driver, self.wait_time_for_finding_object).until(EC.presence_of_element_located((By.ID, "move-list")))
        self.play_game()

browser = Browser()
if "--login" in sys.argv:
    browser.login()
if "--play" in sys.argv:
    browser.start_and_play_game()
    # # time.sleep(3)
    # browser.close()
    # pprint(browser.bot.time_taken_list)
    # if browser.bot.time_taken_list:
    #     print(mean(browser.bot.time_taken_list), "+/-", stdev(browser.bot.time_taken_list), sum(browser.bot.time_taken_list), browser.bot.evaluator.total_nodes_searched, browser.bot.evaluator.total_nodes_searched/sum(browser.bot.time_taken_list))
    print(browser.pgn)

browser.bot.kill()
