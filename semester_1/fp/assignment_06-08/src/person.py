class Person:
    def __init__(self, uid: str, name: str, phone_number: str):
        self.__uid = uid
        self.__name = name
        self.__phone_number = phone_number

    @property
    def uid(self):
        return self.__uid

    @property
    def name(self):
        return self.__name

    @property
    def phone_number(self):
        return self.__phone_number

    def __str__(self):
        return f'{self.__uid}\t\t{self.__phone_number}\t\t{self.__name}'

    def __eq__(self, other: "Person"):
        return self.__uid == other.__uid
