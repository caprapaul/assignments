from vertex import Vertex


class Edge:
    def __init__(self, start: int, end: int, cost: int):
        self.__start = start
        self.__end = end
        self.__cost = cost

    @property
    def start(self):
        return self.__start

    @property
    def end(self):
        return self.__end

    @property
    def cost(self):
        return self.__cost

    @cost.setter
    def cost(self, value):
        self.__cost = value
