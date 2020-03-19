import datetime
import ast


class Activity:
    def __init__(self, uid: str, persons_uids, date: datetime.date, time: datetime.time, description: str):
        self.__uid = uid
        self.__persons_uids = list(dict.fromkeys(persons_uids))  # keep only unique persons
        self.__date = date
        self.__time = time
        self.__description = description

    @property
    def uid(self):
        return self.__uid

    @property
    def persons_uids(self):
        return self.__persons_uids

    @property
    def date(self):
        return self.__date

    @property
    def time(self):
        return self.__time

    @property
    def description(self):
        return self.__description

    def to_dict(self):
        date = datetime.date.strftime(self.__date, '%Y-%m-%d')
        time = datetime.time.strftime(self.__time, '%H:%M:%S')
        return {
            'uid': self.__uid,
            'person_uids': self.__persons_uids,
            'date': date,
            'time': time,
            'description': self.__description
        }

    @staticmethod
    def from_dict(data):
        if isinstance(data['person_uids'], str):
            person_uids = ast.literal_eval(data['person_uids'])

        else:
            person_uids = data['person_uids']

        date = datetime.datetime.strptime(data['date'], '%Y-%m-%d').date()
        time = datetime.datetime.strptime(data['time'], '%H:%M:%S').time()
        activity = Activity(data['uid'], person_uids, date, time, data['description'])
        return activity

    def __str__(self):
        return f'{self.__uid}\t\t{self.__date}\t\t{self.__time}\t\t{self.__description}\t\t{self.__persons_uids}'

    def __repr__(self):
        return f'Activity({self.__uid},{self.__persons_uids},{self.__date},{self.__time},{self.__description})'

    def __eq__(self, other: "Activity"):
        return self.__uid == other.__uid
