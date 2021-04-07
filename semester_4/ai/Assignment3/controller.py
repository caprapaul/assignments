from repository import *
import random
import numpy as np
import time


class Controller():
    def __init__(self, repository):
        # args - list of parameters needed in order to create the controller
        self.__repository = repository

    def iteration(self, run, stats, population, parents_count, max_mutations, mutate_probability, crossover_probability):
        # args - list of parameters needed to run one iteration
        # a iteration:
        # selection of the parrents
        # create offsprings by crossover of the parents
        # apply some mutations
        # selection of the survivors
        f = []

        parents = population.selection(parents_count)

        for i in range(len(parents) - 1):
            for j in range(i, len(parents)):
                offspring1, offspring2 = parents[i].crossover(
                    parents[j], crossover_probability)

                offspring1.mutate(max_mutations, mutate_probability)
                offspring2.mutate(max_mutations, mutate_probability)
                offspring1.fitness(population.map, population.position)
                offspring2.fitness(population.map, population.position)

                population.add_individual(offspring1)
                population.add_individual(offspring2)

        new_individuals = population.selection(population.population_size)
        population.replace_individuals(new_individuals)

        for individual in new_individuals:
            f.append(individual.f)

        stats.iterations_fitness_average[run].append(np.average(f))

    def run(self, run, stats, population, parents_count, max_mutations, mutate_probability, crossover_probability, iterations):
        # args - list of parameters needed in order to run the algorithm

        # until stop condition
        #    perform an iteration
        #    save the information need it for the satistics

        # return the results and the info for statistics
        print(f'Run #{run}')

        stats.iterations_fitness_average.append([])
        start = time.perf_counter()
        population.evaluate()

        for i in range(iterations):
            self.iteration(run, stats, population, parents_count, max_mutations,
                           mutate_probability, crossover_probability)
            # print(f'Iteration #{i}')

        stop = time.perf_counter()

        stats.runs_fitness_average.append(
            np.average(stats.iterations_fitness_average[run]))
        stats.execution_time.append(stop - start)

        return population.selection(1)[0]

    def solver(self, position, parents_count, max_mutations, mutate_probability, crossover_probability, iterations, runs, population_size, individual_size):
        # args - list of parameters needed in order to run the solver

        # create the population,
        # run the algorithm
        # return the results and the statistics
        stats = Statistics()
        best = []

        for i in range(runs):
            random.seed(i)
            population = Population(
                self.__repository.mapp, position, population_size, individual_size)

            self.__repository.add_population(population)
            run_best = self.run(i, stats, population, parents_count, max_mutations,
                                mutate_probability, crossover_probability, iterations)

            best.append(run_best)

        stats.fitness_average = np.average(stats.runs_fitness_average)
        stats.fitness_std = np.std(stats.runs_fitness_average)

        return best, stats

    @ property
    def map(self):
        return self.__repository.mapp

    def save_map(self, file_name='test.map'):
        self.__repository.save_map(file_name)

    def load_map(self, file_name='test.map'):
        self.__repository.load_map(file_name)
