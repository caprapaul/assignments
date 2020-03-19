from clisys import clisys
from game import Game, GameError
from board import Board, BoardError
from input_player import InputPlayer
from random_computer import RandomComputer

from texttable import Texttable


class MenuUI(clisys.CLISys):
    def __init__(self):
        super().__init__()
        self.__game: Game = None

    def replace_cell(self, x):
        if x == 0:
            return ''

        elif x == -1:
            return u'\u2588'

        elif x > 0:
            return self.__game.get_player_symbol(x)

    def display_board(self):
        cells = self.__game.board
        table = Texttable()
        width = len(cells[0])
        table.set_cols_align(["c"] * (width + 2))
        table.set_cols_valign(["m"] * (width + 2))
        table.add_row(['', 'X'] + [str(x) for x in range(0, width)])
        table.add_row(['Y', u'\u2554'] + [u'\u2550'] * (width))

        for y, row in enumerate(cells):
            row_new = [self.replace_cell(x) for x in row]
            table.add_row([str(y), u'\u2551'] + row_new)

        print(table.draw())

    def run_game(self):
        while not self.__game.is_finished:
            self.display_board()
            self.__game.run()
            print('\n' * 2)

        self.display_board()
        winner = self.__game.current_player

        if winner.is_human:
            print('YOU WON!')

        else:
            print('YOU LOST!')

        print(f'The winner is: {winner.name}')

    @clisys.command(name='1', description='New Game.')
    def new_game(self, args):
        board_width = int(input('Input board width: '))
        board_height = int(input('Input board height: '))

        board = Board(board_width, board_height)

        humans_count = int(input('Input the number of human players: '))

        if humans_count < 0:
            raise ValueError('Invalid number of human players.')

        computers_count = int(input('Input the number of computer players: '))

        if computers_count < 0:
            raise ValueError("Invalid number of computer players.")

        players = []

        for i in range(0, humans_count):
            name = input(f'Input player {i} name: ')
            symbol = input(f'Input player {i} symbol: ')
            players.append(InputPlayer(board, name=name, symbol=symbol))

        for i in range(0, computers_count):
            difficulty = int(input(f'Input CPU {i} difficulty: \n'
                                   f'(0 - Random; 1 - Easy)'))
            symbol = input(f'Input CPU {i} symbol: ')

            if difficulty == 0:
                players.append(RandomComputer(board, name=f'CPU {i}', symbol=symbol, difficulty=0))

            if difficulty == 1:
                players.append(RandomComputer(board, name=f'CPU {i}', symbol=symbol, difficulty=1))

        print('\n' * 2)
        self.__game = Game(board, players)
        self.__game.start()
        self.run_game()

    @clisys.command(name='-1', description='Exit.')
    def exit_program(self, args):
        """
        Exits the program.
        """
        self.exit()

    @clisys.exception_handler
    def handle_exceptions(self, exception: Exception):
        """
        Handles exceptions raised in commands.
        :param exception: The exception.
        :return:
        """
        try:
            raise exception

        except clisys.InvalidCommand as e:
            print(f'Invalid option: "{str(e.command_name)}" .')

        except clisys.InvalidArgument as e:
            print(f'Invalid argument: "{str(e.argument_name)}" .')

        except clisys.InvalidArgumentCount:
            print('Invalid argument count.')

        except BoardError as e:
            print(e)

        except GameError as e:
            print(e)

        except ValueError as e:
            print(e)

    def display_options(self):
        """
        Displays the list of options.
        :return:
        """
        print()
        options = list(self.get_commands().values())
        options.sort(key=lambda op: int(op.name))

        for option in options:
            print(f'{"%3d" % int(option.name)}. {option.description}')

    @clisys.input_handler
    def get_option(self):
        """
        Gets the input and returns it as a list
        :return: A list of strings. (first element is the name of the command)
        """
        self.display_options()
        i = input('\nOption: ')

        return [i]
