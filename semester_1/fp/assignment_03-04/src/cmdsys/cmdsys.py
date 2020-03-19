from src.cmdsys.command import Command
from src.cmdsys.exceptions import *


class CommandSystem:
    """
    A base class to facilitate the creation of a command pattern system.
    """
    def __init__(self):
        self.__actions_stack = []
        self.__undo_stack = []
        self.init_commands()

    def init_commands(self):
        """
        Searches for all the inner classes that inherit from Command and decorates them with the command decorator.
        :return:
        """
        for attr_name in dir(self):
            attr = getattr(self, attr_name)

            if isinstance(attr, type):
                if Command in attr.__bases__:
                    setattr(self, attr_name, self.command(attr))

    def undo(self):
        """
        Undo the last undo-able command.
        :return:
        """
        if len(self.__actions_stack) == 0:
            raise EmptyActionsStack

        action = self.__actions_stack.pop()
        action.undo(self)
        self.__undo_stack.append(action)

    def redo(self):
        """
        Redo the last undo-ed command.
        :return:
        """
        if len(self.__undo_stack) == 0:
            raise EmptyUndoStack

        action = self.__undo_stack.pop()
        action.execute(self)
        self.__actions_stack.append(action)

    def command(self, cls):
        """
        A decorator for command classes. As a result these classes can be used as functions.
        :param cls: The command class.
        :return: A wrapper.
        """
        def wrapper(*args, **kwargs):
            """
            A wrapper for command classes that calls their constructor and execute() method.
            If the command has an undo function
            :param args: Arguments list.
            :param kwargs: Keyed arguments list.
            :return: An instance of the class.
            """
            obj = cls(*args, **kwargs)
            result = obj.execute(self)

            if obj.undo_enabled:
                self.__actions_stack.append(obj)

            return result

        return wrapper


