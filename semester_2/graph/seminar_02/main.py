from graph_matrix import GraphMatrix
from graph_out import GraphOut
from graph_in_out import GraphInOut

import random
import time


def random_graph(graph, vertex_count):
    edge_count = 0

    while edge_count < 10 * vertex_count:
        from_vertex = random.randrange(0, vertex_count)
        to_vertex = random.randrange(0, vertex_count)

        if not graph.has_edge(from_vertex, to_vertex):
            graph.add_edge(from_vertex, to_vertex)
            edge_count += 1


def matrix(vertex_count):
    print("Matrix:")
    graph = GraphMatrix(vertex_count)
    random_graph(graph, vertex_count)

    start = time.perf_counter()

    for vertex in graph.parse_vertices():
        for inbound in graph.parse_in(vertex):
            pass

        for outbound in graph.parse_out(vertex):
            pass

    stop = time.perf_counter()
    print(f"Elapsed time: {stop - start} s")


def out(vertex_count):
    print("Out dictionary:")
    graph = GraphOut(vertex_count)
    random_graph(graph, vertex_count)

    start = time.perf_counter()

    for vertex in graph.parse_vertices():
        for inbound in graph.parse_in(vertex):
            pass

        for outbound in graph.parse_out(vertex):
            pass

    stop = time.perf_counter()
    print(f"Elapsed time: {stop - start} s")


def in_out(vertex_count):
    print("In and Out dictionaries:")
    graph = GraphInOut(vertex_count)
    random_graph(graph, vertex_count)

    start = time.perf_counter()

    for vertex in graph.parse_vertices():
        for inbound in graph.parse_in(vertex):
            pass

        for outbound in graph.parse_out(vertex):
            pass

    stop = time.perf_counter()
    print(f"Elapsed time: {stop - start} s")


def run():
    vertex_counts = [1000, 10000, 100000, 1000000]

    for (i, vertex_count) in enumerate(vertex_counts):
        print(f"{i + 1}) {vertex_count} vertices: ")
        matrix(vertex_count)
        print()
        out(vertex_count)
        print()
        in_out(vertex_count)
        print()


run()
