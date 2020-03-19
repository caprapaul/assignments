# PROBLEM [15]


import math


def find_divisors(n: int):
    """
    Returns a list with the divisors of n.
    :param n: A natural number.
    :return: divisors - A list with the divisors of n.
    """
    divisors = []

    for i in range(1, int(math.sqrt(n)) + 1):
        if n % i == 0:
            divisors.append(i)
            divisors.append(n // i)

    return divisors


def list_sum(l):
    """
    Returns the sum of a list of numbers.
    :param l: A list of natural numbers;
    :return: l_sum: int - The product.
    """
    l_sum = 0

    for x in l:
        l_sum += x

    return l_sum


def is_perfect(n: int):
    """
    Checks if n is perfect.
    :param n: A natural number
    :return: True if n is perfect, False otherwise
    """
    divisors = find_divisors(n)
    divisors_sum = list_sum(divisors)

    if divisors_sum - n == n:
        return True

    return False


def largest_perfect(n: int):
    """
    Returns the largest perfect number smaller than n.
    :param n: A natural number.
    :return: largest: int - The largest perfect number smaller than n.
    """
    largest = n - 1

    while largest > 0:
        if is_perfect(largest):
            return largest

        largest -= 1

    return 0


def read_number():
    n = int(input('Please input a natural number: '))
    print('\n')
    return n


def show_result(n: int, result: int):
    print(f'The largest perfect number smaller than {n} is: {result}')


def run():
    n = read_number()
    result = largest_perfect(n)
    show_result(n, result)


run()
