from collections.abc import Callable


class ExceptionHandler:
    def __init__(self, func: Callable):
        self .__func = func

    def __call__(self, *args, **kwargs):
        return self.__func(*args, **kwargs)
