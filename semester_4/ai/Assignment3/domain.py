# -*- coding: utf-8 -*-

from random import *
from utils import *
import numpy as np
import copy

# the glass gene can be replaced with int or float, or other types
# depending on your problem's representation


class Gene:
    def __init__(self):
        self.value = (randint(-1, 1), randint(-1, 1))


class Individual:
    def __init__(self, size=0):
        self.__size = size
        self.__genes = [Gene() for i in range(self.__size)]
        self.__f = None

    @property
    def f(self):
        return self.__f

    def compute_path(self, mapp, position):
        path = [(position[0], position[1])]

        for gene in self.__genes:
            new_pos = (position[0] + gene.value[0],
                       position[1] + gene.value[1])

            if mapp.check_position(new_pos):
                path.append(new_pos)
                position = new_pos

        return path

    def fitness(self, mapp, position):
        visited = []
        path = self.compute_path(mapp, position)
        self.__f = 0

        directions = [(0, 1), (1, 0), (-1, 0), (0, -1)]

        for pos in path:
            for direction in directions:
                x, y = pos

                while mapp.check_position((x + direction[0], y + direction[1])):
                    x = x + direction[0]
                    y = y + direction[1]

                    if (x, y) not in visited:
                        self.__f += 1
                        visited.append((x, y))

    def mutate(self, max_mutations=1, mutate_probability=0.04):
        if random() < mutate_probability:
            mutations = randint(0, max_mutations)

            while mutations > 0:
                self.__genes[randint(0, self.__size - 1)] = Gene()
                mutations -= 1

    def crossover(self, other_parent, crossover_probability=0.8):
        offspring1 = Individual(self.__size)
        offspring2 = Individual(self.__size)

        if random() < crossover_probability:
            point = randint(0, self.__size - 1)

            offspring1.__genes = other_parent.__genes[:point] + \
                self.__genes[point:]
            offspring2.__genes = self.__genes[:point] + \
                other_parent.__genes[point:]

        return offspring1, offspring2


class Population():
    def __init__(self, mapp, position, population_size=0, individual_size=0):
        self.__population_size = population_size
        self.__individuals = [Individual(individual_size)
                              for x in range(population_size)]
        self.__map = mapp
        self.__position = position

    @property
    def map(self):
        return self.__map

    @property
    def position(self):
        return self.__position

    @property
    def population_size(self):
        return self.__population_size

    def add_individual(self, individual):
        self.__individuals.append(individual)

    def replace_individuals(self, individuals):
        self.__individuals = individuals

    def evaluate(self):
        # evaluates the population
        for individual in self.__individuals:
            individual.fitness(self.__map, self.__position)

    def selection(self, k=0):
        # perform a selection of k individuals from the population
        # and returns that selection
        individuals = copy.deepcopy(self.__individuals)

        for i in individuals:
            if i.f is None:
                a = 10

        individuals.sort(reverse=True, key=lambda i: i.f)
        selected = []

        for i in range(0, k):
            selected.append(individuals[i])

        return selected


class Map():
    def __init__(self, n=20, m=20):
        self.n = n
        self.m = m
        self.surface = np.zeros((self.n, self.m))

    def check_position(self, position):
        return 0 <= position[0] < self.n and 0 <= position[1] < self.m and self.surface[position[0]][position[1]] != 1

    def detect(self, x, y):
        self.surface[x][y] = 2

    def randomize(self, fill=0.2):
        self.surface = np.zeros((self.n, self.m))
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

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
