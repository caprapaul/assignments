from repository import *
from undirected_graph import UndirectedGraph
from vertex import Vertex
from edge import Edge
import utils

import random
import numpy as np
import time


class Controller:
    def __init__(self, repository):
        self.__repository = repository
        self.__graph = None

    def search_a_star(self, initial_x, initial_y, final_x, final_y):
        openn = []
        closed = []
        parents = {}

        start = (initial_x, initial_y)
        goal = (final_x, final_y)

        start_distances = {}
        goal_distances = {}

        openn.append(start)
        parents[start] = None
        start_distances[start] = 0

        while openn:
            current = min(openn, key=lambda o: start_distances.get(
                o, 0) + goal_distances.get(o, 0))

            if current == goal:
                path = []
                path.append(current)

                while parents[current]:
                    current = parents[current]
                    path.append(current)

                return path[::-1]

            openn.remove(current)
            closed.append(current)

            neigbhors = utils.get_neighbors(
                self.__repository.mapp, current[0], current[1])

            for node in neigbhors:
                if node in closed:
                    continue

                new_distance = start_distances[current] + 1

                if node in openn:
                    if start_distances[node] > new_distance:
                        start_distances[node] = new_distance
                        parents[node] = current

                else:
                    start_distances[node] = new_distance
                    goal_distances[node] = utils.manhattan(
                        node[0], node[1], goal[0], goal[1])
                    parents[node] = current

                    openn.append(node)

        return []

    def create_graph(self, start_position, initial_pheromone):
        # calculate the cooverages of each sensor at each power level
        for sensor in self.__repository.sensors.values():
            sensor.calculate_coverage(self.__repository.mapp)

        self.__graph = UndirectedGraph()

        # transform the starting point and each sensor's different states into vertices
        start_vertex = Vertex(start_position, 0, 0)
        self.__graph.add_vertex(start_vertex)

        for sensor in self.__repository.sensors.values():
            for i, coverage in enumerate(sensor.coverages):
                vertex = Vertex(sensor.position, i, coverage)
                self.__graph.add_vertex(vertex)

        vertices = list(self.__graph.parse_vertices())

        for i in range(len(vertices) - 1):
            start = vertices[i]

            for j in range(i + 1, len(vertices)):
                end = vertices[j]

                if start.position[0] != end.position[0] and start.position[1] != end.position[1]:
                    path = self.search_a_star(
                        start.position[0], start.position[1], end.position[0], end.position[1])

                    cost = len(path)
                    edge = Edge(start, end, cost, path, initial_pheromone)
                    self.__graph.add_edge(edge)

    def epoch(self, ant_energy, ants_count, q0, cost_power, pheromone_power, evaporation_rate):
        ants = []
        vertices = list(self.__graph.parse_vertices())

        # create ants
        for i in range(ants_count):
            vertex = vertices[0]
            ant = Ant(vertex, ant_energy)
            ants.append(ant)

        running = True

        while running:
            running = False

            for ant in ants:
                if ant.finished:
                    continue

                ant.move(self.__graph, q0, cost_power, pheromone_power)
                running = True

        costs = [ant.cost(self.__graph) for ant in ants]
        min_cost = min(costs)
        f = [1 / (cost - min_cost + 1) for cost in costs]

        for edge in self.__graph.parse_edges():
            edge.pheromone *= 1 - evaporation_rate

        for i, ant in enumerate(ants):
            for j in range(len(ant.path) - 1):
                v1 = ant.path[j]
                v2 = ant.path[j + 1]
                edge = self.__graph.get_edge(v1, v2)
                edge.pheromone += f[i]

        best_i = max(range(len(ants)), key=lambda i: f[i])
        best_ant = ants[i]
        return (best_ant.path, f[i])

    def solve(self, ant_energy, ants_count, q0, cost_power, pheromone_power, evaporation_rate, epoch_count):
        sol = ([], -1)
        best_sol = ([], -1)

        for i in range(epoch_count):
            sol = self.epoch(ant_energy, ants_count, q0,
                             cost_power, pheromone_power, evaporation_rate)

            if sol[1] > best_sol[1]:
                best_sol = sol

        return best_sol

    def update_sensors(self, vertices):
        for sensor in self.__repository.sensors.values():
            sensor.power = 0

        for vertex in vertices:
            if vertex.position in self.__repository.sensors:
                sensor = self.__repository.sensors[vertex.position]
                sensor.power = vertex.power

    def get_path(self, vertices):
        path = []

        for i in range(len(vertices) - 1):
            v1 = vertices[i]
            v2 = vertices[i + 1]
            edge = self.__graph.get_edge(v1, v2)
            edge_path = edge.path

            if edge.path[0] != v1.position:
                edge_path = edge_path[::-1]

            path += edge_path

        return path

    @ property
    def map(self):
        return self.__repository.mapp

    @ property
    def sensors(self):
        return self.__repository.sensors

    def save_map(self, file_name='test.map'):
        self.__repository.save_map(file_name)

    def load_map(self, file_name='test.map'):
        self.__repository.load_map(file_name)
