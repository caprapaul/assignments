from abc import ABC, abstractmethod


class Command:
    """
    The base class for commands.
    Set self.undo_enabled to True to enable the undo functionality.
    """
    def __init__(self, outer_instance, undo_enabled: bool = False, use_global_stacks: bool = False):
        self.outer_instance = outer_instance
        self.undo_enabled = undo_enabled
        self.use_global_stacks = use_global_stacks

    @abstractmethod
    def execute(self):
        """
        The instructions the command executes.
        :param outer_instance: The instance of the outer class. (the class the command is defined in)
        :return:
        """
        raise NotImplementedError

    def undo(self):
        """
        The instructions the command's undo executes.
        :param outer_instance: The instance of the outer class. (the class the command is defined in)
        :return:
        """
        pass
