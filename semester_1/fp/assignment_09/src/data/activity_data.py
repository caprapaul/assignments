import random
import datetime


__descriptions = [
    'Exam',
    'Movie',
    'Assignment',
    'Holiday'
]


def get_random_description():
    return __descriptions[random.randrange(0, len(__descriptions))]


MIN_YEAR = datetime.datetime.now().year
MAX_YEAR = datetime.datetime.now().year + 1


def get_random_date():
    start = datetime.datetime(MIN_YEAR, 1, 1, 0, 0, 0)
    years = MAX_YEAR - MIN_YEAR + 1
    end = start + datetime.timedelta(days=365 * years)
    return (start + (end - start) * random.random()).date()


def get_random_time():
    start = datetime.datetime(MIN_YEAR, 1, 1, 0, 0, 0)
    years = MAX_YEAR - MIN_YEAR + 1
    end = start + datetime.timedelta(days=365 * years)
    return (start + (end - start) * random.random()).time().replace(second=0, microsecond=0)
