def test_function(func):
    """
    A decorator for testing functions.
    :param func: The decorated function.
    :return wrapper: A wrapper function.
    """
    from collections import Callable

    def wrapper(on_test_end: Callable = lambda: None):
        """
        A wrapper for the decorated function.
        :param on_test_end: A function to be called when the test ends.
        :return: -
        """
        name = func.__name__
        print(f'Testing {name} ...', end='\t' * (4 - (len(name) // 8)))
        func()
        on_test_end()
        print('\x1b[6;32m' + 'Success! \x1b[0m')

    return wrapper
