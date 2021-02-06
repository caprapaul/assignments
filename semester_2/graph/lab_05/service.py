from undirected_graph import UndirectedGraph
from priority_queue import PriorityQueue
import itertools
import math


def powerset(iterable):
    """powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"""
    s = list(iterable)
    return itertools.chain.from_iterable(itertools.combinations(s, r) for r in range(len(s) + 1))


class Service:
    def __init__(self, graph: UndirectedGraph):
        self.__graph = graph

    def vertex_cover_size(self, vertices):
        visited = set()

        for vertex in vertices:
            for edge in self.__graph.parse_vertex_edges(vertex):
                if edge not in visited:
                    visited.add(edge)

        if len(visited) == len(list(self.__graph.parse_edges())):
            return len(visited)

        else:
            return 0

    def get_minimum_vertex_cover(self):
        vertices = self.__graph.parse_vertices()
        subsets = powerset(vertices)

        min_cover = []

        for subset in subsets:
            cover_size = self.vertex_cover_size(subset)

            if cover_size != 0 and (not min_cover or cover_size < len(min_cover)):
                min_cover = subset

        return min_cover
