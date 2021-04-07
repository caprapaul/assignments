# -*- coding: utf-8 -*-

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

# define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]

# define mapsize
POSITION = (10, 10)
MAP_SIZE = 20
WINDOW_SIZE = (400, 400)
POPULATION_SIZE = 30
INDIVIDUAL_SIZE = 30
MAX_MUTATIONS = 2
ITERATIONS = 50
RUNS = 3
PARENTS_COUNT = 3
MUTATE_PROBABILITY = 0.04
CROSSOVER_PROBABILITY = 0.5
