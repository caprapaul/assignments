# PROBLEM [3]


def find_max_digit(n: int):
    """
    Returns the max digit of a number.
    :param n: The number to find the max in.
    :return: max_digit: int - The max digit.
    """
    max_digit = n % 10
    n //= 10
    while n > 0:
        digit = n % 10

        if digit > max_digit:
            max_digit = digit

        n //= 10

    return max_digit


def remove_digit(n: int, d: int):
    """
    Removes a given digit from a number.
    :param n: The number to remove from.
    :param d: The digit to remove.
    :return: new_n - The modified number.
    """
    new_n = 0
    i = 1
    found = False
    while n > 0:
        digit = n % 10

        if digit != d or found:
            new_n += i * digit
            i *= 10

        if digit == d:
            found = True

        n //= 10

    return new_n


def count_digits(n: int):
    """
    Returns the number of digits of n.
    :param n: A natural number.
    :return:
    """
    count = 0
    while n > 0:
        count += 1
        n //= 10

    return count


def largest_same_digits(n: int):
    """
    Returns the largest number with the same digits as n.
    :param n: The number to work on.
    :return: largest - The largest number with the same digits as n.
    """
    largest = 0
    digits_count = count_digits(n)

    while digits_count > 0:
        largest *= 10
        max_digit = find_max_digit(n)
        largest += max_digit
        n = remove_digit(n, max_digit)
        digits_count -= 1

    return largest


def read_number():
    n = int(input('Please input a natural number: '))
    print('\n')
    return n


def show_result(n: int, result: int):
    print(f'The largest natural number written with the same digits as {n} is: {result}')


def run():
    n = read_number()
    result = largest_same_digits(n)
    show_result(n, result)


run()
