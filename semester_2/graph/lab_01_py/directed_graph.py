from edge import Edge
from vertex import Vertex


class DirectedGraph:
    def __init__(self):
        # Stores the in and out edge indices of each vertex
        self.__inout = []
        # Stores the vertices
        self.__vertices = []
        # Stores the edges
        self.__edges = []

    def load_from_file(self, file_name: str):
        with open(file_name, 'r') as data_file:
            first_line = data_file.readline()
            (vertex_count, edge_count) = first_line.split(' ')
            vertex_count = int(vertex_count)
            edge_count = int(edge_count)
            self.__vertices = [Vertex() for i in range(vertex_count)]

            for line in data_file:
                (edge_start, edge_end, edge_cost) = line.split(' ')
                edge_start: int = int(edge_start)
                edge_end: int = int(edge_end)
                edge_cost = int(edge_cost)

                edge_start = self.__vertices[edge_start]
                edge_end = self.__vertices[edge_end]

                self.__edges.append(Edge(edge_start, edge_end, edge_cost))


    def print(self):
        for row in self.__cost_matrix:
            for element in row:
                print(f"{element} ")
            print()

    def vertices_count(self):
        return len(self.__vertices)

    def edges_count(self):
        return len(self.__edges)
