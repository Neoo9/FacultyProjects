from src.board.board import Board
from src.strategy.minimax import Minimax


class Game:
    def __init__(self, rows, cols):
        self._board = Board(rows, cols)
        self._strategy = Minimax()

    @property
    def board(self):
        return self._board

    def human_move(self, x, y, symbol):
        self._board.move(x, y, symbol)

    def cpu_move(self, symbol):
        """
        Calculates cpu optimal move using minimax, then performs the move
        """
        move = self._strategy.minimax_root(self._board, symbol, 4, True)
        self._board.move(move[0], move[1], symbol)
