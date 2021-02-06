from collections import Callable


class Command:
    def __init__(self, name: str, func: Callable, description: str = ''):
        self.__name = name
        self.__func = func
        self.__description = description

    def __call__(self, *args, **kwargs):
        return self.__func(*args, **kwargs)

    @property
    def name(self):
        return self.__name

    @property
    def description(self):
        return self.__description
