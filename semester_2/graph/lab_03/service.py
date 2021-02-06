from directed_graph import DirectedGraph
from priority_queue import PriorityQueue
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

    def get_min_cost_path(self, start, end):
        queue = PriorityQueue()
        previous = {vertex: None for vertex in self.__graph.parse_vertices()}
        distances = {vertex: math.inf for vertex in self.__graph.parse_vertices()}
        visited = set()

        queue.add(end, 0)
        visited.add(end)
        distances[end] = 0

        while not queue.is_empty():
            current_vertex = queue.pop()

            if current_vertex == start:
                # Build path
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

            for edge in self.__graph.parse_in(current_vertex):
                next_vertex = edge.start
                current_distance = distances[current_vertex] + edge.cost

                if next_vertex not in visited:
                    queue.add(next_vertex, current_distance)
                    visited.add(next_vertex)

                if current_distance < distances[next_vertex]:
                    distances[next_vertex] = current_distance
                    previous[next_vertex] = current_vertex

        return []
