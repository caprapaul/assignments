
class Table:
    def __init__(self, items=None):
        if items is None:
            items = {}

        self.__items = items

    def __getitem__(self, key):
        return self.__items[key]

    def __setitem__(self, key, value):
        self.__items[key] = value
        self.__last = len(self.__items.values())

    def __delitem__(self, key):
        del self.__items[key]

    def __iter__(self):
        """
        Returns a generator for the keys and values.
        :return:
        """

        for key in self.__items.keys():
            value = self.__items[key]
            yield (key, value)

        return

    def pop(self, key):
        return self.__items.pop(key)

    def keys(self):
        """
        Returns a generator for the keys.
        :return:
        """
        for key in self.__items.keys():
            yield key

        return None

    def values(self):
        """
        Returns a generator for the values.
        :return:
        """
        for key in self.__items.keys():
            value = self.__items[key]
            yield value

        return None

    def copy(self):
        return Table(self.__items.copy())
