# PROBLEM [9]


import math


def find_proper_factors(n: int):
    """
    Returns the proper factors of a natural number n.
    :param n: A natural number.
    :return: factors - A list with the proper factors of n.
    """
    factors = []

    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            factors.append(i)
            factors.append(n // i)

    return factors


def list_product(l):
    """
    Returns the product of a list of numbers.
    :param l: A list of natural numbers;
    :return: product: int - The product.
    """
    product = 1

    for x in l:
        product *= x

    return product


def proper_factors_product(n: int):
    """
    Returns the product of all proper factors of a natural number n.
    :param n: A natural number.
    :return: product: int - The product.
    """
    factors = find_proper_factors(n)
    product = list_product(factors)
    return product


def read_number():
    n = int(input('Please input a natural number: '))
    print('\n')
    return n


def show_result(n: int, result: int):
    print(f'The product of the proper factors of {n} is: {result}')


def run():
    n = read_number()
    result = proper_factors_product(n)
    show_result(n, result)


run()
