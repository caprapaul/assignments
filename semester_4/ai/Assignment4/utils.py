# -*- coding: utf-8 -*-

def get_neighbors(mapp, x, y):
    neighbors = [(d[0], d[1])
                 for d in [(x, y + 1), (x + 1, y), (x, y - 1), (x - 1, y)]]

    return [valid_neighbor for valid_neighbor in neighbors if mapp.check_position(valid_neighbor)]


def manhattan(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


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

# define cell types
AIR = 0
WALL = 1


# define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]

# define mapsize
POSITION = (10, 10)
MAP_SIZE = 20
WINDOW_SIZE = (400, 440)

SENSORS_COUNT = 5
SENSORS_MAX_POWER = 5

INITIAL_PHEROMONE = 1

ANT_ENERGY = 40
ANTS_COUNT = 5
Q0 = 0.5
COST_POWER = 1.9
PHEROMONE_POWER = 0.9
EVAPORATION_RATE = 0.05

EPOCH_COUNT = 100
