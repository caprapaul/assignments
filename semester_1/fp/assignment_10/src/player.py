import abc

from board import Board


class Player(abc.ABC):
    def __init__(self, board: Board, is_human: bool, name: str = '', symbol: chr = '', order_id: int = -1):
        self._board = board
        self.__is_human = is_human
        self.__name = name
        self.__symbol = symbol
        self.__order_id = order_id

    @property
    def is_human(self):
        return self.__is_human

    @property
    def name(self):
        return self.__name

    @property
    def symbol(self):
        return self.__symbol

    @property
    def order_id(self):
        return self.__order_id

    @order_id.setter
    def order_id(self, value: int):
        self.__order_id = value

    @abc.abstractmethod
    def get_move(self) -> (int, int):
        pass
