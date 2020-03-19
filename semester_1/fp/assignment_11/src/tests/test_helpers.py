import unittest

from helpers import sort_list, filter_list


class TestHelpers(unittest.TestCase):
    def test_sort(self):
        items = [2, 1, 3, 0]

        sorted_items = sort_list(items)
        self.assertEqual(sorted_items, [0, 1, 2, 3])

        sorted_items = sort_list(items, lambda x, y: x < y)
        self.assertEqual(sorted_items, [3, 2, 1, 0])

    def test_filter(self):
        items = [2, 1, 3, 0]

        filtered_items = filter_list(items, lambda x: x > 1)
        self.assertEqual(filtered_items, [2, 3])

        filtered_items = filter_list(items, lambda x: x > 3)
        self.assertEqual(filtered_items, [])
