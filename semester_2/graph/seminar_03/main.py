from graph_in_out import GraphInOut

import random


def random_graph(graph, vertex_count, edge_count):
    current_edge_count = 0

    while current_edge_count < edge_count:
        from_vertex = random.randrange(0, vertex_count)
        to_vertex = random.randrange(0, vertex_count)

        if not graph.has_edge(from_vertex, to_vertex):
            graph.add_edge(from_vertex, to_vertex)
            current_edge_count += 1


def my_graph(graph):
    graph.add_edge(0, 2)
    graph.add_edge(0, 4)
    graph.add_edge(0, 7)
    graph.add_edge(2, 3)
    graph.add_edge(4, 5)
    graph.add_edge(4, 6)
    graph.add_edge(6, 8)


def build_tree_internal(graph, tree, root, visited):
    tree[root] = []

    for child in graph.parse_out(root):
        if child not in visited:
            visited.append(child)
            tree[root].append(child)
            build_tree_internal(graph, tree, child, visited)


def build_tree(graph, root):
    visited = [root]
    tree = {}

    for vertex in graph.parse_vertices():
        tree[vertex] = []

    build_tree_internal(graph, tree, root, visited)

    return tree


def print_tree(tree, root, depth):
    indent = depth * '\t'
    print(f"{indent}{root}")

    for child in tree[root]:
        print_tree(tree, child, depth + 1)


def get_root(graph):
    for vertex in graph.parse_vertices():
        if len(graph.parse_in(vertex)) == 0:
            return vertex


def build_path_internal(tree, root, end):
    if root == end:
        return [root]

    path = []
    for child in tree[root]:
        subpath = build_path_internal(tree, child, end)
        if end in subpath:
            path.append(root)
            path += subpath

    return path


def build_path(tree, start, end):
    path = build_path_internal(tree, start, end)

    return path


def run():
    vertex_count = 9
    edge_count = 10
    graph = GraphInOut(vertex_count)
    #random_graph(graph, vertex_count, edge_count)
    my_graph(graph)

    root = get_root(graph)
    tree = build_tree(graph, root)
    print_tree(tree, root, 0)

    start = 4
    end = 8
    path = build_path(tree, start, end)

    if len(path) > 0:
        print(f"The path from {start} to {end} is: {path}")
    else:
        print(f"There is no path from {start} to {end}.")


run()
