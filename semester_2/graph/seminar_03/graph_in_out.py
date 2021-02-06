class GraphInOut:
    def __init__(self, vertex_count):
        self._out = {}
        self._in = {}

        for i in range(vertex_count):
            self._out[i] = []
            self._in[i] = []

    def parse_vertices(self):
        """Returns an iterable containing all the vertices"""
        return self._out.keys()

    def parse_out(self, vertex):
        """Returns an iterable containing the outbound neighbours of vertex"""
        return self._out[vertex]

    def parse_in(self, vertex):
        """Returns an iterable containing the inbound neighbours of vertex"""
        return self._in[vertex]

    def add_edge(self, from_vertex, to_vertex):
        """Returns True if there is an edge from from_vertex to to_vertex, False otherwise"""
        self._out[from_vertex].append(to_vertex)
        self._in[to_vertex].append(from_vertex)

    def has_edge(self, from_vertex, to_vertex):
        """Adds an edge from from_vertex to to_vertex"""
        return to_vertex in self._out[from_vertex]
