import unittest

from repositories.repository import Repository
from services.activity_service import ActivityService, Activity
from services.person_service import PersonService, Person
from data.activity_data import *
from data.person_data import *
from cmdsys.cmdsys import CommandSystem


class TestServices(unittest.TestCase):
    def test_activity_service(self):
        a_repo = Repository()
        p_repo = Repository()
        p_repo.add_item(Person('1', get_random_name(), get_random_phone_number()), get_uid=lambda p: p.uid)
        p_repo.add_item(Person('2', get_random_name(), get_random_phone_number()), get_uid=lambda p: p.uid)
        p_repo.add_item(Person('3', get_random_name(), get_random_phone_number()), get_uid=lambda p: p.uid)

        service = ActivityService(a_repo, p_repo)
        activity1 = Activity('1234', ['1', '2'], get_random_date(), get_random_time(), 'test1')
        activity2 = Activity('4321', ['1', '3'], get_random_date(), get_random_time(), 'test2')

        service.add_activity(activity1)
        self.assertEqual(service.get_activities(), [activity1])
        service.add_activity(activity2)
        self.assertEqual(service.get_activities(), [activity1, activity2])

        self.assertEqual(service.get_activity(activity1.uid), activity1)

        service.remove_activity(activity2.uid)
        self.assertEqual(service.get_activities(), [activity1])

        CommandSystem.global_undo()
        self.assertEqual(service.get_activities(), [activity1, activity2])
        CommandSystem.global_redo()
        self.assertEqual(service.get_activities(), [activity1])
        CommandSystem.global_undo()

        new_activity = Activity(activity2.uid, ['1'], activity2.date, activity2.time, activity2.description)
        service.update_activity(activity2.uid, new_activity)
        self.assertEqual(service.get_activities(), [activity1, new_activity])

        self.assertEqual(service.get_date_activities(activity1.date), [activity1])

        self.assertEqual(service.get_busiest_days(), [(activity1.date, 1), (new_activity.date, 1)])

        self.assertEqual(service.get_person_activities('2'), [activity1])
        self.assertEqual(service.search_activities(None, None, 'test1'), [activity1])

    def test_person_service(self):
        a_repo = Repository()
        p_repo = Repository()
        service = PersonService(p_repo, a_repo)

        person1 = Person('1', get_random_name(), get_random_phone_number())
        person2 = Person('2', get_random_name(), get_random_phone_number())

        service.add_person(person1)
        self.assertEqual(service.get_persons(), [person1])
        service.add_person(person2)
        self.assertEqual(service.get_persons(), [person1, person2])

        self.assertEqual(service.get_person(person1.uid), person1)

        service.remove_person(person2.uid)
        self.assertEqual(service.get_persons(), [person1])

        CommandSystem.global_undo()
        self.assertEqual(service.get_persons(), [person1, person2])
        CommandSystem.global_redo()
        self.assertEqual(service.get_persons(), [person1])
        CommandSystem.global_undo()


if __name__ == '__main__':
    unittest.main()
