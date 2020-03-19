import unittest

from board import Board
from game import Game, GameError
from random_computer import RandomComputer


class TestGame(unittest.TestCase):
    def test_game(self):
        board = Board(3, 3)
        players = [RandomComputer(board), RandomComputer(board)]
        game = Game(board, players)

        self.assertFalse(game.is_finished)

        game.start()

        self.assertTrue(game.is_finished)

        with self.assertRaises(GameError):
            game = Game(board, [])
            game.start()
