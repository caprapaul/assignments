import random


__first_names = [
    'Ioana',
    'George',
    'Andrei',
    'Dimitrie',
    'Horatiu',
    'Laura',
    'Miruna',
    'Gheorghe',
    'Viorel',
    'Ciprian',
    'Denisa',
    'Marinela',
    'Alex',
    'Viorica',
    'Mihai',
    'Ionela',
    'Livia',
    'Andreea',
    'Maria'
]

__last_names = [
    'Nastase',
    'Puscas',
    'Istrati',
    'Babes',
    'Costache',
    'Ilica',
    'Iordache',
    'Voiculescu',
    'Bucsa',
    'Diaconu',
    'Urzica',
    'Manea',
    'Florea',
    'Vlaicu',
    'Nemes'
]

__phone_numbers = [
    '0793381507',
    '0738093235',
    '0772714075',
    '0778196321',
    '0735076465',
    '0349047805',
    '0336939506',
    '0730224095',
    '0722402765',
    '0241224265',
    '0354210345',
    '0346379828',
    '0798042471',
    '0766927641',
    '0700357323',
    '0775945651',
    '0266969139',
    '0773667214',
    '0779851214',
    '0794675930',
]


def get_random_name():
    first_name = __first_names[random.randrange(0, len(__first_names))]
    last_name = __last_names[random.randrange(0, len(__last_names))]
    return f'{first_name} {last_name}'


def get_random_phone_number():
    return __phone_numbers[random.randrange(0, len(__phone_numbers))]
