from complex_number import *
from sequences import *


def display_numbers(numbers):
    """
    Displays all the numbers in the list.
    :param numbers: The list of complex numbers.
    :return:
    """
    for i, number in enumerate(numbers):
        print(f'{i + 1:2d}.\t[{get_real(number)}, {get_imaginary(number)}]')


def read_complex_number():
    """
    Reads a complex number.
    :return number: (float, float) - A complex number.
    """
    number = (0, 0)

    real = float(input('Input the real part: '))
    imaginary = float(input('Input the imaginary part: '))

    number = set_real(number, real)
    number = set_imaginary(number, imaginary)

    return number


def display_add_number(numbers):
    """
    Adds a new complex number to the list.
    :param numbers: The list of complex numbers.
    :return new_numbers: The modified list.
    """
    new_numbers = numbers

    number = read_complex_number()
    new_numbers.append(number)

    return new_numbers


def display_strictly_increasing_sequence(numbers):
    """
    Displays the longest sequence of numbers with a strictly increasing real part.
    :param numbers: The list of complex numbers.
    :return -:
    """
    sequence = get_strictly_increasing_sequence(numbers)
    print('The longest sequence of numbers with a strictly increasing real part:')
    display_numbers(sequence)


def display_mountain_sequence(numbers):
    """
    Displays the longest sequence of numbers with a real part in the form of a mountain.
    :param numbers: The list of complex numbers.
    :return -:
    """
    sequence = get_mountain_sequence(numbers)
    print('The longest sequence of numbers with a real part in the form of a mountain:')
    display_numbers(sequence)


def display_menu():
    """
    Prints the options menu.
    :return:
    """
    options = [
        'Display numbers.',
        'Add number.',
        'Get longest sequence of numbers with a strictly increasing real part.',
        'Get longest sequence of numbers with a real part in the form of a mountain.'
    ]

    print('OPTIONS:')

    for i, option in enumerate(options):
        print(f'{i + 1:2d}.\t{option}')

    print('\n-1.\tExit.\n')


def read_option():
    """
    Reads the option number.
    :return option:int - The option number.
    """
    option = int(input('Input option: '))

    return option


def init():
    """
    Initializes a list of complex numbers.
    :return new_numbers: - The initialized list of numbers.
    """
    new_numbers = [(10, 2), (3, 5), (4, 1), (2.5, 2), (3, 0.25), (13, 4), (1, 1), (14, 12.3), (1.2, 6.5), (2, 9)]

    return new_numbers


def run():
    numbers = init()

    option = 0

    while option != -1:
        display_menu()
        option = read_option()
        print()

        if option == 1:
            display_numbers(numbers)

        elif option == 2:
            numbers = display_add_number(numbers)

        elif option == 3:
            display_strictly_increasing_sequence(numbers)

        elif option == 4:
            display_mountain_sequence(numbers)

        else:
            print('Invalid option.')

        print('\n' * 2)


run()
