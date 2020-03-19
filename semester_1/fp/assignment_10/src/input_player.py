from board import OutOfBoundsError, Board
from player import Player


class InputPlayer(Player):
    """
    Human player that gets its move from the console input.
    """
    def __init__(self, board: Board, name: str = '', symbol: chr = '', order_id: int = -1):
        super().__init__(board, True, name, symbol, order_id)

    def get_move(self) -> (int, int):
        raw_input = input(f'Input move for player {self.name} (Format: "x, y"): ')

        invalid_input = False
        try:
            x_str, y_str = raw_input.strip().split(',')
            x, y = int(x_str), int(y_str)

            if not self._board.is_empty(x, y):
                invalid_input = True

        except ValueError:
            invalid_input = True

        while invalid_input:
            invalid_input = False
            print('Invalid input.')
            print('\n' * 2)
            raw_input = input(f'Input move for player {self.name} (Format: "x, y"): ')

            try:
                x_str, y_str = raw_input.strip().split(',')
                x, y = int(x_str), int(y_str)

                if not self._board.is_empty(x, y):
                    invalid_input = True

            except ValueError:
                invalid_input = True

            except OutOfBoundsError:
                invalid_input = True

        return x, y
