from collections.abc import Callable

from src.clisys.command import Command
from src.clisys.exception_handler import ExceptionHandler
from src.clisys.exceptions import *
from src.clisys.input_handler import InputHandler


def command(name: str, description: str = ''):
    """
    A decorator creator for commands.
    :param name: The name of the command.
    :param description: The description of the command.
    :return: A decorator
    """
    def decorator(func):
        """
        A decorator for commands. Transforms them into a callable object of type Command.
        :param func: The decorated function.
        :return: -
        """
        cmd = Command(name, func, description)
        cmd.__doc__ = func.__doc__
        return cmd

    return decorator


def exception_handler(func):
    """
    A decorator for the function that handles exceptions in commands.
    :param func: The decorated function.
    :return: -
    """
    return ExceptionHandler(func)


def input_handler(func):
    """
    A decorator for the function that handles input for commands.
    :param func: The decorated function.
    :return: -
    """
    return InputHandler(func)


class CLISys:
    """
    The base class for a CLI program.
    """
    def __init__(self):
        self.__exit = False
        self.__commands = {}
        self.__invalid_func: Callable = lambda name: None
        self.__input_func: Callable = lambda: None
        self.init_commands()

    def exit(self):
        self.__exit = True

    def init_commands(self):
        """
        Searches for all methods decorated by the command/handler decorator and saves them.
        :return:
        """
        for attr_name in dir(self):
            try:
                attr = getattr(self, attr_name)

                if isinstance(attr, Command):
                    self.__commands[attr.name] = attr

                elif isinstance(attr, ExceptionHandler):
                    self.__invalid_func = attr

                elif isinstance(attr, InputHandler):
                    self.__input_func = attr

            except:
                continue

    def get_commands(self):
        """
        Returns the dictionary of commands
        :return: The dictionary of commands.
        """
        return self.__commands

    def run(self):
        while not self.__exit:
            args = self.__input_func(self)
            cmd_name = args[0]

            try:
                if not (cmd_name in self.__commands.keys()):
                    raise InvalidCommand(cmd_name)

                cmd = self.__commands[cmd_name]
                cmd(self, args[1:])

            except Exception as e:
                self.__invalid_func(self, e)
