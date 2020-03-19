class Vertex:
    __counter = 0

    def __init__(self):
        self.__id = Vertex.__counter
        Vertex.__counter += 1
