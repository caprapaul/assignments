from edge import Edge
from vertex import Vertex


class UndirectedGraph:
    def __init__(self):
        # Stores the edges of each vertex
        self.__vertex_edges = {}
        # Stores the vertices
        self.__vertices = {}
        # Stores the edges
        self.__edges = {}

    @property
    def vertices_count(self):
        return len(self.__vertices)

    @property
    def edges_count(self):
        return len(self.__edges)

    def parse_vertices(self):
        """Returns an iterable containing all the vertices"""
        return iter(self.__vertices.values())

    def parse_edges(self):
        return iter(self.__edges.values())

    def parse_vertex_edges(self, vertex):
        """Returns an iterable containing the neighbours of vertex"""
        return iter(self.__vertex_edges[vertex])

    def add_vertex(self, identifier):
        """Adds a vertex to the graph."""
        self.__vertices[identifier] = identifier
        self.__vertex_edges[identifier] = []

    def add_edge(self, from_vertex, to_vertex, cost):
        """Adds an edge between from_vertex and to_vertex"""
        if self.get_vertex(from_vertex) is None:
            raise ValueError("Invalid source vertex.")

        if self.get_vertex(to_vertex) is None:
            raise ValueError("Invalid destination vertex.")

        edge = Edge(from_vertex, to_vertex, cost)

        self.__edges[(from_vertex, to_vertex)] = edge
        self.__vertex_edges[from_vertex].append(edge)
        self.__vertex_edges[to_vertex].append(edge)

    def get_vertex(self, identifier):
        """Returns the vertex if there is a vertex with id identifier, None otherwise"""
        if identifier in self.__vertices:
            return self.__vertices[identifier]

        else:
            return None

    def get_edge(self, from_vertex, to_vertex):
        """Returns the edge if there is an edge between from_vertex and to_vertex, None otherwise"""
        if (from_vertex, to_vertex) in self.__edges:
            return self.__edges[(from_vertex, to_vertex)]

        elif (to_vertex, from_vertex) in self.__edges:
            return self.__edges[(to_vertex, from_vertex)]

        else:
            return None

    def remove_vertex(self, identifier):
        """Removes a vertex from the graph, removing all edges that contain it."""
        if self.get_vertex(identifier) is None:
            raise ValueError("Invalid identifier.")

        for edge in self.__vertex_edges[identifier]:
            self.__vertex_edges[edge.start].remove(edge)
            self.__vertex_edges[edge.end].remove(edge)

            if (edge.start, edge.end) in self.__edges.keys():
                del self.__edges[(edge.start, edge.end)]

            if (edge.end, edge.start) in self.__edges.keys():
                del self.__edges[(edge.end, edge.start)]

        del self.__vertex_edges[identifier]

    def remove_edge(self, from_vertex, to_vertex):
        """Removes an edge from the graph."""
        edge = self.get_edge(from_vertex, to_vertex)

        if edge is None:
            raise ValueError("Invalid edge.")

        self.__vertex_edges[to_vertex].remove(edge)
        self.__vertex_edges[from_vertex].remove(edge)

        if (edge.start, edge.end) in self.__edges.keys():
            del self.__edges[(edge.start, edge.end)]

        if (edge.end, edge.start) in self.__edges.keys():
            del self.__edges[(edge.end, edge.start)]

    def degree(self, identifier):
        """Returns the in degree of a vertex."""
        return len(self.__vertex_edges[identifier])
