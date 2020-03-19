import unittest

from table import Table


class TestTable(unittest.TestCase):
    def test_iterator(self):
        table = Table()
        table[0] = 0
        table[1] = 1
        table[2] = 2

        i = 0
        for key, val in table:
            self.assertEqual(key, i)
            self.assertEqual(val, i)
            i += 1
