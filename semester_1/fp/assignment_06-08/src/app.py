import random

from repository import Repository
from person import Person
from activity import Activity
from services.person_service import PersonService
from services.activity_service import ActivityService, ActivityServiceError
from data.person_data import get_random_name, get_random_phone_number
from data.activity_data import get_random_date, get_random_time, get_random_description

from ui import UI

if __name__ == '__main__':
    person_repo = Repository()
    activity_repo = Repository()
    person_service = PersonService(person_repo, activity_repo)
    activity_service = ActivityService(activity_repo, person_repo)

    persons_len = 10
    persons = []

    for i in range(persons_len):
        persons.append(Person(person_repo.generate_uid(), get_random_name(), get_random_phone_number()))

    for person in persons:
        person_service.add_person(person)

    def get_random_persons_uids():
        person_uids = []
        length = random.randrange(1, len(persons))

        for i in range(length):
            person = persons[random.randrange(0, len(persons))]
            person_uids.append(person.uid)

        return person_uids

    activities_len = 10
    count = 0

    while count < activities_len:
        try:
            activity_service.add_activity(
                Activity(activity_repo.generate_uid(), get_random_persons_uids(),
                         get_random_date(), get_random_time(), get_random_description())
            )

            count += 1

        except ActivityServiceError:
            continue

    ui = UI(person_service, activity_service)
    ui.run()
