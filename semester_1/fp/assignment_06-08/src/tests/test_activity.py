import unittest
import datetime

from activity import Activity


class TestActivity(unittest.TestCase):
    def test_activity(self):
        date = datetime.datetime(2019, 12, 10, 12, 10)
        activity = Activity('1', ['1234', '5678'], date.date(), date.time(), 'test')

        self.assertEqual(activity.uid, '1')
        self.assertEqual(activity.persons_uids, ['1234', '5678'])
        self.assertEqual(activity.date, date.date())
        self.assertEqual(activity.time, date.time())
        self.assertEqual(activity.description, 'test')


if __name__ == '__main__':
    unittest.main()
