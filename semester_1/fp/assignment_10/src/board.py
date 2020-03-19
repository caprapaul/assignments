class OutOfBoundsError(Exception):
    def __init__(self):
        super().__init__()


class BoardError(Exception):
    def __init__(self, message):
        super().__init__(message)


class Board:
    def __init__(self, width: int, height: int, cells=None):
        if width <= 0 or height <= 0:
            raise BoardError('Invalid board properties.')

        self.__width = width
        self.__height = height

        if cells is None:
            self.__cells = [[0] * width for i in range(height)]

        else:
            self.__cells = cells

    @property
    def width(self):
        return self.__width

    @property
    def height(self):
        return self.__height

    @property
    def cells(self):
        return self.__cells

    def is_empty(self, x: int, y: int):
        """
        Checks if a cell is empty.
        :param x: x coordinate
        :param y: y coordinate
        :return: True if cell is empty False otherwise
        """
        if x < 0 or x >= self.__width or y < 0 or y >= self.__height:
            raise OutOfBoundsError()

        return self.__cells[y][x] == 0

    def set_cell(self, x: int, y: int, value: int):
        """
        Sets a cell's value.
        :param x: x coordinate
        :param y: y coordinate
        :param value: cell value
        :return: -
        """
        if x < 0 or x >= self.__width or y < 0 or y >= self.__height:
            raise OutOfBoundsError()

        self.__cells[y][x] = value
