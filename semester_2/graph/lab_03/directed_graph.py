from edge import Edge
from vertex import Vertex


class DirectedGraph:
    def __init__(self):
        # Stores the inbound edges of each vertex
        self.__in = {}
        # Stores the outbound edges of each vertex
        self.__out = {}
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

    def parse_out(self, vertex):
        """Returns an iterator containing the outbound neighbours of vertex"""
        return iter(self.__out[vertex])

    def parse_in(self, vertex):
        """Returns an iterable containing the inbound neighbours of vertex"""
        return iter(self.__in[vertex])

    def add_vertex(self, identifier):
        """Adds a vertex to the graph."""
        self.__vertices[identifier] = identifier
        self.__out[identifier] = []
        self.__in[identifier] = []

    def add_edge(self, from_vertex, to_vertex, cost):
        """Adds an edge from from_vertex to to_vertex"""
        if self.get_vertex(from_vertex) is None:
            raise ValueError("Invalid source vertex.")

        if self.get_vertex(to_vertex) is None:
            raise ValueError("Invalid destination vertex.")

        edge = Edge(from_vertex, to_vertex, cost)

        self.__edges[(from_vertex, to_vertex)] = edge
        self.__out[from_vertex].append(edge)
        self.__in[to_vertex].append(edge)

    def get_vertex(self, identifier):
        """Returns the vertex if there is a vertex with id identifier, None otherwise"""
        if identifier in self.__vertices:
            return self.__vertices[identifier]

        else:
            return None

    def get_edge(self, from_vertex, to_vertex):
        """Returns the edge if there is an edge from from_vertex to to_vertex, None otherwise"""
        if (from_vertex, to_vertex) in self.__edges:
            return self.__edges[(from_vertex, to_vertex)]

        else:
            return None

    def remove_vertex(self, identifier):
        """Removes a vertex from the graph, removing all edges that contain it."""
        if self.get_vertex(identifier) is None:
            raise ValueError("Invalid identifier.")

        for edge in self.__out[identifier]:
            del self.__edges[(edge.start, edge.end)]

        for edge in self.__in[identifier]:
            if self.get_edge(edge.start, edge.end) is not None:
                del self.__edges[(edge.start, edge.end)]

        del self.__out[identifier]
        del self.__in[identifier]
        del self.__vertices[identifier]

    def remove_edge(self, from_vertex, to_vertex):
        """Removes an edge from the graph."""
        edge = self.get_edge(from_vertex, to_vertex)

        if edge is None:
            raise ValueError("Invalid edge.")

        self.__out[from_vertex].remove(edge)
        self.__in[to_vertex].remove(edge)
        del self.__edges[(from_vertex, to_vertex)]

    def in_degree(self, identifier):
        """Returns the in degree of a vertex."""
        return len(self.__in[identifier])

    def out_degree(self, identifier):
        """Returns the out degree of a vertex."""
        return len(self.__out[identifier])
