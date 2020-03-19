from repositories.repository import Repository
from models.activity import Activity
from cmdsys.cmdsys import CommandSystem, Command
import datetime


class ActivityServiceError(Exception):
    def __init__(self, message):
        super().__init__(message)


class ActivityService(CommandSystem):
    def __init__(self, activity_repository: Repository, person_repository: Repository):
        super().__init__()
        self._activity_repository = activity_repository
        self._person_repository = person_repository

    def generate_uid(self):
        return self._activity_repository.generate_uid()

    class get_activities(Command):
        """
        Returns all persons.
        :return:
        """

        def __init__(self, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

        def execute(self):
            return self.outer_instance._activity_repository.get_items()

    class get_activity(Command):
        """
        Returns the activity with the given uid.
        :param uid: 
        :return: 
        """

        def __init__(self, uid: str, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

            self.uid = uid

        def execute(self):
            activity = self.outer_instance._activity_repository.get_item(uid=self.uid)

            if activity is None:
                raise ActivityServiceError(f'Cannot find activity with uid: {self.uid}')

            return activity

    class add_activity(Command):
        """
        Adds an activity to the repository.
        :param activity:
        :return:
        """

        def __init__(self, activity: Activity, outer_instance: "ActivityService"):
            super().__init__(outer_instance, undo_enabled=True, use_global_stacks=True)

            self.activity = activity

        def execute(self):
            overlapping_activity = None

            for person_uid in self.activity.persons_uids:
                if self.outer_instance._person_repository.get_item(uid=person_uid) is None:
                    raise ActivityServiceError(f'Cannot find person with uid: {person_uid}')

                overlapping_activity = self.outer_instance._activity_repository.get_item(
                    condition=lambda a: a.date == self.activity.date and
                                        a.time == self.activity.time and
                                        person_uid in a.activitys_uids)

            if overlapping_activity is not None:
                raise ActivityServiceError('Activity overlaps with another!')

            self.outer_instance._activity_repository.add_item(self.activity, get_uid=lambda a: a.uid)

        def undo(self):
            self.outer_instance._activity_repository.undo()

    class remove_activity(Command):
        """
        Removes an activity from the repository.
        :param uid: The uid of the activity.
        :return:
        """

        def __init__(self, uid: str, outer_instance: "ActivityService"):
            super().__init__(outer_instance, undo_enabled=True, use_global_stacks=True)

            self.uid = uid

        def execute(self):
            self.outer_instance._activity_repository.remove_item(uid=self.uid)

        def undo(self):
            self.outer_instance._activity_repository.undo()

    class update_activity(Command):
        """
        Updates an activity from the repository.
        :param uid: The uid of the activity.
        :param new_activity: The new value.
        :return:
        """

        def __init__(self, uid: str, new_activity: Activity, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

            self.uid = uid
            self.new_activity = new_activity

        def execute(self):
            self.outer_instance._activity_repository.replace_item(self.new_activity, uid=self.uid)

        def undo(self):
            self.outer_instance._activity_repository.undo()

    class get_date_activities(Command):
        def __init__(self, date: datetime.date, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

            self.date = date

        def execute(self):
            activities = self.outer_instance._activity_repository.get_items(condition=lambda a: a.date == self.date)
            activities.sort(key=lambda a: a.time)
            return activities

    class get_busiest_days(Command):
        def __init__(self, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

        def execute(self):
            activities = self.outer_instance._activity_repository.get_items()
            days = {}

            for activity in activities:
                if activity.date in days.keys():
                    days[activity.date] = days[activity.date] + 1

                else:
                    days[activity.date] = 1

            days = [(k, v) for k, v in days.items()]
            days.sort(key=lambda d: d[1], reverse=True)

            return days

    class get_person_activities(Command):
        def __init__(self, uid: str, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

            self.uid = uid

        def execute(self):
            return self.outer_instance._activity_repository.get_items(lambda a: self.uid in a.persons_uids)

    class search_activities(Command):
        """
        Returns the person with the given uid.
        :param uid:
        :return:
        """

        def __init__(self, date: datetime.date, time: datetime.date, description: str, outer_instance: "ActivityService"):
            super().__init__(outer_instance)

            self.date = date
            self.time = time
            self.description = description

        def execute(self):
            repo = self.outer_instance._activity_repository

            match_date = lambda p: True if self.date is None else p.date == self.date
            match_time = lambda p: True if self.time is None else p.date == self.time
            match_description = lambda p: True if self.description == '' else  self.description.lower() in p.description.lower()

            activities = repo.get_items(lambda p: match_date(p) and match_time(p) and match_description(p))

            if not activities:
                raise ActivityServiceError(f"Cannot find any activity.")

            return activities
