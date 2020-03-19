import random

from repositories.repository import Repository
from repositories.repository_text import RepositoryText
from repositories.repository_binary import RepositoryBinary
from repositories.repository_json import RepositoryJSON
from models.person import Person
from models.activity import Activity
from services.person_service import PersonService
from services.activity_service import ActivityService, ActivityServiceError
from data.person_data import get_random_name, get_random_phone_number
from data.activity_data import get_random_date, get_random_time, get_random_description
from settings import Settings

from ui import UI

if __name__ == '__main__':
    settings = Settings()

    if settings.repository == 'inmemory':
        person_repo = Repository()
        activity_repo = Repository()

    elif settings.repository == 'text':
        person_repo = RepositoryText()
        activity_repo = RepositoryText()

    elif settings.repository == 'binary':
        person_repo = RepositoryBinary()
        activity_repo = RepositoryBinary()

    elif settings.repository == 'json':
        person_repo = RepositoryJSON()
        activity_repo = RepositoryJSON()

    else:
        person_repo = Repository()
        activity_repo = Repository()

    person_repo.load_data(file=settings.persons, type=Person)
    activity_repo.load_data(file=settings.activities, type=Activity)

    person_service = PersonService(person_repo, activity_repo)
    activity_service = ActivityService(activity_repo, person_repo)

    # Generate data
    if settings.repository == 'inmemory':
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

    person_repo.save_data(file=settings.persons)
    activity_repo.save_data(file=settings.activities)
