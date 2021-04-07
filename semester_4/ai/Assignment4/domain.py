# -*- coding: utf-8 -*-

from random import *
from utils import *
import numpy as np
import copy


class Sensor:
    def __init__(self, position, max_power):
        self.position = position
        self.coverages = [0 for i in range(max_power + 1)]
        self.covered = [[] for i in range(max_power + 1)]
        self.power = 0

    def calculate_coverage(self, mapp):
        directions = [(0, 1), (1, 0), (-1, 0), (0, -1)]

        for power in range(1, len(self.coverages)):
            for direction in directions:
                current_range = 0
                x, y = self.position

                while current_range < power and mapp.check_position((x + direction[0], y + direction[1])):
                    x = x + direction[0]
                    y = y + direction[1]
                    self.coverages[power] += 1
                    self.covered[power].append((x, y))
                    current_range += 1


class Ant:
    def __init__(self, vertex, energy):
        self.vertex = vertex
        self.energy = energy
        self.path = [vertex]
        self.finished = False

    def check_visited_position(self, vertex):
        for visited_vertex in self.path:
            if visited_vertex.position == vertex.position:
                return True

        return False

    def move(self, graph, q0, cost_power, pheromone_power):
        edges = graph.parse_vertex_edges(self.vertex)
        next_vertices = []

        desirabilities = {}

        # get the edges with unvisited vertex positions that can be reached (cost <= energy)
        for edge in edges:
            if edge.cost > self.energy:
                continue

            if self.check_visited_position(edge.start) and self.check_visited_position(edge.end):
                continue

            next_vertex = None

            if self.vertex != edge.start:
                next_vertex = edge.start

            elif self.vertex != edge.end:
                next_vertex = edge.end

            next_vertices.append(next_vertex)
            pheromone_strength = edge.pheromone
            desirabilities[next_vertex] = (
                (1 / edge.cost) ** cost_power) * (pheromone_strength ** pheromone_power)

        if not next_vertices:
            self.finished = True
            return

        next_vertex = None

        if random() < q0:
            # choose the best vertex destination
            best_vertex = max(next_vertices, key=lambda v: desirabilities[v])
            next_vertex = best_vertex

        else:
            # choose a random vertex destination based on the desirabilities of the vertices
            weights = []

            for vertex in next_vertices:
                desirability = desirabilities[vertex]
                weights.append(desirability)

            next_vertex = choices(next_vertices, weights=weights, k=1)[0]

        next_edge = graph.get_edge(self.vertex, next_vertex)

        self.path.append(next_vertex)
        self.vertex = next_vertex
        self.energy -= next_edge.cost

    def cost(self, graph):
        cost = 0

        for i in range(len(self.path) - 1):
            v1 = self.path[i]
            v2 = self.path[i + 1]
            edge = graph.get_edge(v1, v2)
            cost += edge.cost - v2.reward

        return cost


class Map:
    def __init__(self, n=20, m=20):
        self.n = n
        self.m = m
        self.surface = np.zeros((self.n, self.m))

    def check_position(self, position):
        return 0 <= position[0] < self.n and 0 <= position[1] < self.m and self.surface[position[0]][position[1]] != 1

    def randomize(self, fill=0.2):
        self.surface = np.zeros((self.n, self.m))
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

    def get_empty_positions(self, n):
        positions = []

        while len(positions) < n:
            x = randint(0, self.n - 1)
            y = randint(0, self.m - 1)
            pos = (x, y)

            if pos not in positions and self.check_position(pos):
                positions.append(pos)

        return positions

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string = string + str(int(self.surface[i][j]))
            string = string + "\n"
        return string


class Statistics:
    def __init__(self):
        self.iterations_fitness_average = []
        self.runs_fitness_average = []
        self.execution_time = []
        self.fitness_average = 0
        self.fitness_std = 0
