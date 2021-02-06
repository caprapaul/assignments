from directed_graph import DirectedGraph
import math


class Service:
    def __init__(self, graph: DirectedGraph):
        self.__graph = graph

    def get_path(self, start, end):
        queue = []
        previous = {vertex: None for vertex in self.__graph.parse_vertices()}
        distances = {vertex: math.inf for vertex in self.__graph.parse_vertices()}
        visited = set()

        queue.append(end)
        visited.add(end)
        distances[end] = 0

        while len(queue) > 0:
            current_vertex = queue.pop(0)

            if current_vertex == start:
                path = []
                while current_vertex is not None:
                    path.append(current_vertex)
                    next_vertex = None
                    try:
                        next_vertex = previous[current_vertex]
                    except KeyError:
                        pass

                    current_vertex = next_vertex

                return path

            current_distance = distances[current_vertex] + 1
            for edge in self.__graph.parse_in(current_vertex):
                next_vertex = edge.start

                if next_vertex not in visited:
                    queue.append(next_vertex)
                    visited.add(next_vertex)

                if current_distance < distances[next_vertex]:
                    distances[next_vertex] = current_distance
                    previous[next_vertex] = current_vertex

        return []
