import unittest

from models.person import Person


class TestPerson(unittest.TestCase):
    def test_person(self):
        person = Person('1', 'test', '0123456789')

        self.assertEqual(person.uid, '1')
        self.assertEqual(person.name, 'test')
        self.assertEqual(person.phone_number, '0123456789')


if __name__ == '__main__':
    unittest.main()
