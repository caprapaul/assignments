class InvalidCommand(Exception):
    def __init__(self, command_name):
        self.command_name = command_name


class InvalidArgumentCount(Exception):
    pass


class InvalidArgument(Exception):
    def __init__(self, argument_name):
        self.argument_name = argument_name
