import random
from directed_graph import DirectedGraph
from ui import UI
from service import Service


def random_graph(graph, vertex_count, edge_count):
    current_edge_count = 0

    for i in range(vertex_count):
        graph.add_vertex(i)

    while current_edge_count < edge_count:
        from_vertex = random.randrange(0, vertex_count)
        to_vertex = random.randrange(0, vertex_count)
        cost = random.randrange(-10, 10)

        if graph.get_edge(from_vertex, to_vertex) is None:
            graph.add_edge(from_vertex, to_vertex, cost)
            current_edge_count += 1


def load_from_file(graph, file_name: str):
    with open(file_name, 'r') as data_file:
        first_line = data_file.readline()
        (vertex_count, edge_count) = first_line.split(' ')
        vertex_count = int(vertex_count)
        edge_count = int(edge_count)

        for i in range(vertex_count):
            graph.add_vertex(i)

        for line in data_file:
            (edge_start, edge_end, edge_cost) = line.split(' ')
            edge_start = int(edge_start)
            edge_end = int(edge_end)
            edge_cost = int(edge_cost)

            graph.add_edge(edge_start, edge_end, edge_cost)


def load_activities(graph: DirectedGraph, file_name: str):
    with open(file_name, 'r') as data_file:
        first_line = data_file.readline()
        activity_count = first_line
        activity_count = int(activity_count)

        for i in range(activity_count + 1):
            graph.add_vertex(i)

        for i, line in enumerate(data_file):
            (prerequisites_str, duration) = line.split(' ')

            prerequisites_str = prerequisites_str.split(',')
            prerequisites = []

            for prerequisite_str in prerequisites_str:
                prerequisites.append(int(prerequisite_str))

            duration = int(duration)

            for prerequisite in prerequisites:
                graph.add_edge(prerequisite, i + 1, duration)


def save_to_file(graph: DirectedGraph, file_name: str):
    with open(file_name, 'w') as data_file:
        output = f"{graph.vertices_count} {graph.edges_count}\n"

        for edge in graph.parse_edges():
            output += f"{edge.start} {edge.end} {edge.cost}\n"

        data_file.write(output)


def run():
    graph = DirectedGraph()
    #random_graph(graph, 100, 10)
    #load_from_file(graph, "graph5.txt")
    load_activities(graph, "activities.txt")
    service = Service(graph)
    ui = UI(graph, service)
    ui.run()
    save_to_file(graph, "graph_out.txt")


run()
