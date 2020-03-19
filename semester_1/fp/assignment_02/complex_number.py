def get_real(x: (float, float)):
    """
    Returns the real part of a complex number.
    :param x: A complex number represented as a tuple (float, float).
    :return: x[0]: float - The real part of x.
    """
    return x[0]


def set_real(x: (float, float), value: float):
    """
    Modifies the real part of a complex number.
    :param x: A complex number represented as a tuple (float, float).
    :param value: A real number.
    :return: new_x: (float, float) - The modified complex number.
    """
    new_x = (value, x[1])
    return new_x


def get_imaginary(x: (float, float)):
    """
    Returns the imaginary part of a complex number.
    :param x: A complex number represented as a tuple (float, float).
    :return: x[1]: float - The imaginary part of x.
    """
    return x[1]


def set_imaginary(x: (float, float), value: float):
    """
    Modifies the imaginary part of a complex number.
    :param x: A complex number represented as a tuple (float, float).
    :param value: A real number.
    :return: new_x: (float, float) - The modified complex number.
    """
    new_x = (x[0], value)
    return new_x
