import unittest

from repositories.repository import Repository


class TestRepository(unittest.TestCase):
    def test_generate_id(self):
        repo = Repository()
        uids = []

        for i in range(1000):
            uid = repo.add_item(1)
            self.assertNotIn(uid, uids)
            uids.append(uid)

    def test_add_item(self):
        repo = Repository()
    
        repo.add_item(1)
        self.assertEqual(repo.get_items(), [1])

    def test_get_items(self):
        repo = Repository()
    
        repo.add_item(0)
        repo.add_item(1)
        self.assertEqual(repo.get_item(condition=lambda item: item == 1), 1)

        uid = repo.add_item(2)
        self.assertEqual(repo.get_item(uid=uid), 2)
    
        repo.add_item(1)
        self.assertEqual(repo.get_items(), [0, 1, 2, 1])
        self.assertEqual(repo.get_items(lambda item: item == 1), [1, 1])
        self.assertEqual(repo.get_items(lambda item: item > 2), [])
    
        repo.add_item(3)
        self.assertEqual(repo.get_items(lambda item: item > 2), [3])
    
    def test_remove_items(self):
        repo = Repository()
    
        repo.add_item(0)
        repo.add_item(1)
        repo.add_item(1)
        repo.add_item(1)
    
        repo.remove_item(condition=lambda item: item == 1)
        self.assertEqual(repo.get_items(), [0, 1, 1])

        uid = repo.add_item(2)
        repo.remove_item(uid=uid)
        self.assertEqual(repo.get_items(), [0, 1, 1])
    
        repo.remove_items(lambda item: item == 1)
        self.assertEqual(repo.get_items(), [0])

    def test_replace_item(self):
        repo = Repository()
    
        repo.add_item(0)
        repo.add_item(1)
        repo.add_item(1)
        uid = repo.add_item(1)
    
        repo.replace_item(0, condition=lambda item: item == 1)
        self.assertEqual(repo.get_items(), [0, 0, 1, 1])

        repo.replace_item(2, uid=uid)
        self.assertEqual(repo.get_items(), [0, 0, 1, 2])


if __name__ == '__main__':
    unittest.main()
