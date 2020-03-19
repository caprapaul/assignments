from repositories.repository import Repository
from models.person import Person
from models.activity import Activity
from cmdsys.cmdsys import CommandSystem, Command


class PersonServiceError(Exception):
    def __init__(self, message):
        super().__init__(message)


class PersonService(CommandSystem):
    def __init__(self, person_repository: Repository, activity_repository: Repository):
        super().__init__()
        self._person_repository = person_repository
        self._activity_repository = activity_repository

    def generate_uid(self):
        return self._person_repository.generate_uid()

    class get_persons(Command):
        """
        Returns all persons.
        :return: 
        """
        def __init__(self, outer_instance: "PersonService"):
            super().__init__(outer_instance)

        def execute(self):
            return self.outer_instance._person_repository.get_items()

    class get_person(Command):
        """
        Returns the person with the given uid.
        :param uid: 
        :return: 
        """
        def __init__(self, uid: str, outer_instance: "PersonService"):
            super().__init__(outer_instance)

            self.uid = uid

        def execute(self):
            person = self.outer_instance._person_repository.get_item(uid=self.uid)

            if person is None:
                raise PersonServiceError(f"Cannot find person with uid: {self.uid}")

            return person

    class add_person(Command):
        """
        Adds an person to the repository.
        :param person:
        :return:
        """
        def __init__(self, person: Person, outer_instance: "PersonService"):
            super().__init__(outer_instance, undo_enabled=True, use_global_stacks=True)

            self.person = person

        def execute(self):
            self.outer_instance._person_repository.add_item(self.person, get_uid=lambda p: p.uid)

        def undo(self):
            self.outer_instance._person_repository.undo()

    class remove_person(Command):
        """
        Removes an person from the repository.
        :param uid: The uid of the person.
        :return:
        """

        def __init__(self, uid: str, outer_instance: "PersonService"):
            super().__init__(outer_instance, undo_enabled=True, use_global_stacks=True)

            self.uid = uid
            self.count = 0

        def execute(self):
            person: Person = self.outer_instance._person_repository.remove_item(uid=self.uid)
            activities = self.outer_instance._activity_repository.get_items(lambda a: person.uid in a.persons_uids)
            self.count = len(activities)

            for i, activity in enumerate(activities):
                new_uids = activity.persons_uids.copy()
                new_uids.remove(person.uid)

                new_activity = Activity(activity.uid, new_uids, activity.date, activity.time, activity.description)
                self.outer_instance._activity_repository.replace_item(new_activity, uid=activity.uid)


        def undo(self):
            self.outer_instance._person_repository.undo()

            for i in range(self.count):
                self.outer_instance._activity_repository.undo()

    class update_person(Command):
        """
        Updates an person from the repository.
        :param uid: The uid of the person.
        :param new_person: The new value.
        :return:
        """
        def __init__(self, uid: str, new_person: Person, outer_instance: "PersonService"):
            super().__init__(outer_instance, undo_enabled=True, use_global_stacks=True)

            self.uid = uid
            self.new_person = new_person

        def execute(self):
            self.outer_instance._person_repository.replace_item(self.new_person, uid=self.uid)

        def undo(self):
            self.outer_instance._person_repository.undo()

    class search_persons(Command):
        """
        Returns the persons with the given name and/or phone number.
        :param name:
        :param phone_number:
        :return:
        """
        def __init__(self, name: str, phone_number: str, outer_instance: "PersonService"):
            super().__init__(outer_instance)

            self.name = name
            self.phone_number = phone_number

        def execute(self):
            repo = self.outer_instance._person_repository

            match_name = lambda p: True if self.name == '' else self.name.lower() in p.name.lower()
            match_phone = lambda p: True if self.phone_number == '' else self.phone_number in p.phone_number

            persons = repo.get_items(lambda p: match_name(p) and match_phone(p))

            if not persons:
                raise PersonServiceError(f"Cannot find any person.")

            return persons
