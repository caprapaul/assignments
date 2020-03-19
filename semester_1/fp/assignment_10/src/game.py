from board import Board, OutOfBoundsError
from player import Player

from typing import List
import random
from enum import Enum


class Cell(Enum):
    """
    Cell can be:
        0   - EMPTY
        -1  - DESTROYED
        >0  - Hit by player
    """
    EMPTY = 0
    DESTROYED = -1


class GameError(Exception):
    def __init__(self, message):
        super().__init__(message)


class Game:
    def __init__(self, board: Board = None, players: List[Player] = None):
        if players is None:
            players = []

        self.__board = board
        self.__players = players
        self.__moves = []
        self.__current_player = None

    @property
    def current_player(self):
        return self.__current_player

    @property
    def is_finished(self):
        for row in self.__board.cells:
            for cell in row:
                if cell == 0:
                    return False

        return True

    @property
    def board(self):
        return self.__board.cells

    def start(self):
        """
        Start a game.
        :return:
        """
        if len(self.__players) == 0:
            raise GameError('Cannot play the game with no players.')

        self.init_players_order()
        self.__current_player = self.__players[0]
        self.run_computer_players()

    def init_players_order(self):
        """
        Shuffle the players list for a random order.
        :return:
        """
        random.shuffle(self.__players)
        for i, player in enumerate(self.__players):
            player.order_id = i + 1

    def get_player_symbol(self, index: int):
        """
        Get the symbol of a player.
        :param index: player index
        :return:
        """
        return self.__players[index - 1].symbol

    def next_player(self):
        """
        Set the next player as the current player.
        :return:
        """
        self.__current_player = self.__players[self.__current_player.order_id % len(self.__players)]

    def run_computer_players(self):
        """
        Run the computer players' turns.
        :return:
        """
        while not self.__current_player.is_human and not self.is_finished:
            x, y = self.__current_player.get_move()

            self.execute_move(x, y, self.__current_player)

            if self.is_finished:
                return

            self.next_player()

    def run(self):
        """
        Run the game until a human player's turn.
        :return:
        """
        x, y = self.__current_player.get_move()

        self.execute_move(x, y, self.__current_player)

        if self.is_finished:
            return

        self.next_player()
        self.run_computer_players()

    def execute_move(self, x: int, y: int, author: Player):
        """
        Execute a given move.
        :param x: x coordinate
        :param y: y coordinate
        :param author: author of the move
        :return:
        """
        for x_n in range(x - 1, x + 2):
            for y_n in range(y - 1, y + 2):
                try:
                    self.__board.set_cell(x_n, y_n, Cell.DESTROYED.value)

                except OutOfBoundsError:
                    continue

        self.__board.set_cell(x, y, author.order_id)
