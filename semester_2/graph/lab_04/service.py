from directed_graph import DirectedGraph
from priority_queue import PriorityQueue
import math


class Service:
    def __init__(self, graph: DirectedGraph):
        self.__graph = graph

    def predecessor_count_sorting(self):
        sorted = []
        queue = []
        count = {}

        for vertex in self.__graph.parse_vertices():
            count[vertex] = self.__graph.in_degree(vertex)

            if count[vertex] == 0:
                queue.append(vertex)

        while queue:
            vertex = queue.pop(0)
            sorted.append(vertex)

            for out_edge in self.__graph.parse_out(vertex):
                out_vertex = out_edge.end
                count[out_vertex] = count[out_vertex] - 1

                if count[out_vertex] == 0:
                    queue.append(out_vertex)

        if len(sorted) < self.__graph.vertices_count:
            sorted = []

        return sorted

    def get_schedule_earliest(self):
        sorted = self.predecessor_count_sorting()
        start_time = {0: 0}
        end_time = {0: 0}

        for start_point in sorted:
            current_time = end_time[start_point]
            for activity_edge in self.__graph.parse_out(start_point):
                start_time[activity_edge.end] = current_time
                end_time[activity_edge.end] = current_time + activity_edge.cost

        return sorted, start_time, end_time

    def get_schedule_latest(self):
        (sorted, start_time_earliest, end_time_earliest) = self.get_schedule_earliest()
        start_time = {sorted[-1]: start_time_earliest[sorted[-1]]}
        end_time = {sorted[-1]: end_time_earliest[sorted[-1]]}

        for end_point in sorted[::-1]:
            current_end_time = end_time_earliest[end_point]
            for activity_edge in self.__graph.parse_in(end_point):
                end_time[activity_edge.start] = current_end_time
                start_time[activity_edge.start] = current_end_time - activity_edge.cost

        return sorted, start_time, end_time


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
