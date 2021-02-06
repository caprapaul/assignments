class PriorityQueue:
    def __init__(self):
        self.__values = {}

    def is_empty(self):
        return len(self.__values) == 0

    def pop(self):
        min_priority = None
        min_object = None

        for obj in self.__values:
            obj_priority = self.__values[obj]

            if min_priority is None or obj_priority < min_priority:
                min_priority = obj_priority
                min_object = obj

        del self.__values[min_object]
        return min_object

    def add(self, obj, priority):
        self.__values[obj] = priority

    def contains(self, val):
        return val in self.__values
