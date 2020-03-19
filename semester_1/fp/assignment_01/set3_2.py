# PROBLEM [14]


import math


def is_prime(n: int):
    """
    Checks if a number is prime.
    :param n: A natural number.
    :return: True if n is prime False otherwise
    """
    if n <= 1:
        return False

    if n <= 3:
        return True

    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False

    return True


def get_next_prime_divisor(n: int, d: int):
    """
    Returns the next prime divisor of n after d.
    :param n: A natural number.
    :param d: A natural number
    :return: prime_divisor: int - Next prime divisor. (0 if there is none)
    """
    if d == 0:
        d = 1

    for i in range(d + 1, n + 1):
        if n % i == 0 and is_prime(i):
            return i

    return 0


def nth_element(n: int):
    """
    Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,... obtained from the
    sequence of natural numbers by replacing composed numbers with their prime divisors, each
    divisor d being written d times.
    :param n: A natural number.
    :return: nth: int - The n-th element.
    """
    if n <= 3:
        return n

    nth = 3     # Current element of the sequence
    x = 4       # Current number, composed or not
    i = 4       # Element counter
    j = 0       # Repeating element counter
    d = 0       # Current prime divisor
    while i <= n:
        if is_prime(x):
            nth = x

            x += 1
            i += 1
        else:
            if j == 0:
                d = get_next_prime_divisor(x, d)
                j = d

                if d == 0:      # If there is no prime divisor left
                    x += 1      # Continue to the next number
                    continue

                nth = d

                j -= 1
                i += 1
            else:
                j -= 1
                i += 1

    return nth


def read_number():
    n = int(input('Please input a natural number: '))
    print('\n')
    return n


def show_result(n: int, result: int):
    print(f'The {n}-th element of the sequence is: {result}')


def run():
    n = read_number()
    result = nth_element(n)
    show_result(n, result)


run()
