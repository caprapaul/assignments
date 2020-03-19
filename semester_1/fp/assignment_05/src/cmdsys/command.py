from abc import ABC, abstractmethod


class Command:
    """
    The base class for commands.
    Set self.undo_enabled to True to enable the undo functionality.
    """
    @property
    def undo_enabled(self):
        raise NotImplementedError

    @abstractmethod
    def execute(self, outer_instance):
        """
        The instructions the command executes.
        :param outer_instance: The instance of the outer class. (the class the command is defined in)
        :return:
        """
        raise NotImplementedError

    def undo(self, outer_instance):
        """
        The instructions the command's undo executes.
        :param outer_instance: The instance of the outer class. (the class the command is defined in)
        :return:
        """
        pass
