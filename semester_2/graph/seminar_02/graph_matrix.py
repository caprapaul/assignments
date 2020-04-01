class GraphMatrix:
    def __init__(self, vertex_count):
        self._matrix = []

        for i in range(vertex_count):
            self._matrix.append([])
            for j in range(vertex_count):
                self._matrix[i].append(False)

    def parse_vertices(self):
        """Returns an iterable containing all the vertices"""
        return range(len(self._matrix))

    def parse_out(self, vertex):
        """Returns an iterable containing the outbound neighbours of vertex"""
        outbound = []

        for i in range(len(self._matrix[vertex])):
            if self._matrix[vertex][i]:
                outbound.append(i)

        return outbound

    def parse_in(self, vertex):
        """Returns an iterable containing the inbound neighbours of vertex"""
        inbound = []

        for i in range(len(self._matrix)):
            if self._matrix[i][vertex]:
                inbound.append(i)

        return inbound

    def add_edge(self, from_vertex, to_vertex):
        """Returns True if there is an edge from from_vertex to to_vertex, False otherwise"""
        self._matrix[from_vertex][to_vertex] = True

    def has_edge(self, from_vertex, to_vertex):
        """Adds an edge from from_vertex to to_vertex"""
        return self._matrix[from_vertex][to_vertex]
