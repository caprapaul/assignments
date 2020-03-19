from complex_number import *


def __get_longest_sequence__with_property(numbers, prop):
    """
    Returns the longest sequence with a certain property.
    :param numbers: A list of numbers.
    :param prop: The property to check against.
    :return longest_sequence: A list representing the longest sequence with the property.
    """
    longest_sequence = []

    for i in range(0, len(numbers)):
        sequence = []

        for j in range(i, len(numbers)):
            sequence.append(numbers[j])

            if prop(sequence) and len(sequence) > len(longest_sequence):
                longest_sequence = sequence.copy()

    return longest_sequence


def get_strictly_increasing_sequence(numbers):
    """
    Returns the longest sequence of numbers with a strictly increasing real part.
    :param numbers: A list of numbers.
    :return longest_sequence: The longest sequence with the property.
    """
    def is_strictly_increasing(sequence):
        if len(sequence) == 1:
            return True

        for i in range(0, len(sequence) - 1):
            real1 = get_real(sequence[i])
            real2 = get_real(sequence[i + 1])

            if real1 >= real2:
                return False

        return True

    longest_sequence = __get_longest_sequence__with_property(numbers, is_strictly_increasing)

    return longest_sequence


def get_mountain_sequence(numbers):
    """
    Returns the longest sequence of numbers with a real part in the form of a mountain.
    :param numbers: A list of numbers.
    :return longest_sequence: The longest sequence with the property.
    """
    def is_mountain(sequence):
        direction = 0

        if len(sequence) == 1:
            return True

        if len(sequence) == 2:
            return False

        for i in range(0, len(sequence) - 1):
            real1 = get_real(sequence[i])
            real2 = get_real(sequence[i + 1])

            if direction == 0:
                if real1 > real2:
                    return False
                else:
                    direction = 1

            elif direction == 1:
                if real1 > real2:
                    direction = -1

            elif direction == -1:
                if real1 <= real2:
                    return False

        return direction == -1

    longest_sequence = __get_longest_sequence__with_property(numbers, is_mountain)

    return longest_sequence

