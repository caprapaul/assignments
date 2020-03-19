import copy

from board import Board, OutOfBoundsError
from player import Player
import random


class RandomComputer(Player):
    def __init__(self, board: Board, name: str = '', symbol: chr = '', order_id: int = -1, difficulty: int = 0):
        super().__init__(board, False, name, symbol, order_id)
        self.__difficulty = difficulty

    def simulate_move(self, x: int, y: int):
        """
        Simulate a move.
        :param x: x coordinate
        :param y: y coordinate
        :return: True if the game is won after the move, False otherwise
        """
        board_copy = copy.deepcopy(self._board)
        for x_n in range(x - 1, x + 2):
            for y_n in range(y - 1, y + 2):
                try:
                    board_copy.set_cell(x_n, y_n, -1)

                except OutOfBoundsError:
                    continue

        board_copy.set_cell(x, y, self.order_id)

        for row in board_copy.cells:
            for cell in row:
                if cell == 0:
                    return False

        return True

    def get_random_move(self, possible_moves):
        rand_i = random.randrange(0, len(possible_moves))
        return possible_moves[rand_i]

    def get_winning_move(self, possible_moves):
        for move in possible_moves:
            x, y = move
            if self.simulate_move(x, y):
                return x, y

        return self.get_random_move(possible_moves)

    def get_move(self) -> (int, int):
        possible_moves = []

        for x in range(self._board.width):
            for y in range(self._board.height):
                if self._board.is_empty(x, y):
                    possible_moves.append((x, y))

        if self.__difficulty == 0:
            return self.get_random_move(possible_moves)

        else:
            return self.get_winning_move(possible_moves)
