from vertex import Vertex


class Edge:
    def __init__(self, start: Vertex, end: Vertex, cost: int):
        self.__start = start
        self.__end = end
        self.__cost = cost
