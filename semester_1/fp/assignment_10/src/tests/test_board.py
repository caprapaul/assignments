import unittest

from board import Board, BoardError, OutOfBoundsError


class TestBoard(unittest.TestCase):
    def test_board(self):
        board = Board(3, 4)

        self.assertEqual(board.width, 3)
        self.assertEqual(board.height, 4)
        self.assertEqual(len(board.cells), 4)
        self.assertEqual(len(board.cells[0]), 3)

        self.assertTrue(board.is_empty(0, 0))
        board.set_cell(0, 0, 1)
        self.assertFalse(board.is_empty(0, 0))

        with self.assertRaises(BoardError):
            board = Board(0, 1)

        with self.assertRaises(OutOfBoundsError):
            board.is_empty(10, 0)

        with self.assertRaises(OutOfBoundsError):
            board.set_cell(10, 0, 1)
