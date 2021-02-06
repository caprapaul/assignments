class Vertex:
    def __init__(self, identifier):
        self.__id = identifier

    def __hash__(self):
        return hash(self.__id)

    def __eq__(self, other):
        return self.__id == other.__id

    def __ne__(self, other):
        return not(self == other)
