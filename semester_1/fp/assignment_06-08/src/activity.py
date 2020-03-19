import datetime


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

    def __str__(self):
        return f'{self.__uid}\t\t{self.__date}\t\t{self.__time}\t\t{self.__description}\t\t{self.__persons_uids}'

    def __eq__(self, other: "Activity"):
        return self.__uid == other.__uid
