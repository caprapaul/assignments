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

    def to_dict(self):
        return {
            'uid': self.__uid,
            'name': self.__name,
            'phone_number': self.__phone_number,
        }

    @staticmethod
    def from_dict(data):
        person = Person(data['uid'], data['name'], data['phone_number'])
        return person

    def __str__(self):
        return f'{self.__uid}\t\t{self.__phone_number}\t\t{self.__name}'

    def __repr__(self):
        return f'Person({self.__uid},{self.__name},{self.__phone_number})'

    def __eq__(self, other: "Person"):
        return self.__uid == other.__uid
