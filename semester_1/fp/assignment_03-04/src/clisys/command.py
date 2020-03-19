from collections import Callable


class Command:
    def __init__(self, name: str, func: Callable):
        self.__name = name
        self .__func = func

    def __call__(self, *args, **kwargs):
        return self.__func(*args, **kwargs)

    def get_name(self):
        return self.__name
