import unittest

from backtracking import get_payments, get_payments_iter


class TestHelpers(unittest.TestCase):
    def assertCountEqualNested(self, item1, item2):
        """
        Asserts that the list elements of 2 lists have the same elements.
        :param item1: first list
        :param item2: second list
        :return:
        """
        for li1 in item1:
            for el1 in li1:
                found = False
                for li2 in item2:
                    if el1 in li2:
                        found = True

                if not found:
                    raise AssertionError(f'Cannot find {el1} in {item2}')

    def test_count_equal_nested(self):
        self.assertCountEqualNested([[1, 1, 2, 2], [6], [3, 1, 2]], [[2, 2, 1, 1], [1, 2, 3], [6]])

        with self.assertRaises(AssertionError):
            self.assertCountEqualNested([[1, 1, 2, 2], [3, 1, 2], [6]], [[2, 2, 1, 1], [1, 2, 3]])

    def test_get_payments(self):
        coins = [2, 2, 1, 3, 1, 6]
        s = 6
        payments = get_payments(coins, s)

        self.assertCountEqualNested(payments, [[2, 2, 1, 1], [1, 2, 3], [6]])

    def test_get_payments_iter(self):
        coins = [2, 2, 1, 3, 1, 6]
        s = 6
        payments = get_payments_iter(coins, s)
        self.assertCountEqualNested(payments, [[2, 2, 1, 1], [1, 2, 3], [6]])
