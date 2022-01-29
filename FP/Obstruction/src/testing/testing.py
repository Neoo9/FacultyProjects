import unittest
from src.board.board import Board
from src.game.game import Game
from src.strategy.minimax import Minimax


class Testing(unittest.TestCase):
    def setUp(self):
        self.test_game = Game(5, 6)
        self.test_strategy = Minimax()
        self.test_board = Board(5, 6)

    def test_get_free_cells(self):
        free = self.test_board.get_free_cells()
        self.assertEqual(30, len(free))

    def test_move(self):
        affected = self.test_board.move(3, 3, 'X')
        self.assertEqual(9, len(affected))
        free = self.test_board.get_free_cells()
        self.assertEqual(21, len(free))
        try:
            self.test_board.move(0, 0, 'a')
            self.assertFalse("not nice")
        except Exception:
            self.assertTrue("nice")
        try:
            self.test_board.move(4, 4, 'X')
            self.assertFalse("not nice")
        except Exception:
            self.assertTrue("nice")

    def test_free(self):
        affected = self.test_board.move(4, 4, 'X')
        self.test_board.free(affected)
        self.assertEqual(30, self.test_board.get_nr_free_cells)

    def test_human_move(self):
        self.test_game.human_move(3, 3, 'X')
        self.assertEqual(21, self.test_game.board.get_nr_free_cells)

    def test_minimax_root(self):
        self.assertEqual([1, 1], self.test_strategy.minimax_root(self.test_board, '0', 4, True))

    def test_minimax(self):
        self.assertEqual(-(self.test_board.get_nr_free_cells / 9 + 1),
                         self.test_strategy.minimax(self.test_board, 'X', 0, True, 0, 0))

