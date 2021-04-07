import pygame
from constants import *
from pygame.locals import *


class Drone():
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.visited = set()
        self.visited.add((x, y))
        self.back = [(x, y)]

    def is_finished(self):
        return (self.x, self.y) == (None, None)

    def move(self, detected_map):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detected_map.surface[self.x-1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detected_map.surface[self.x+1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detected_map.surface[self.x][self.y-1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detected_map.surface[self.x][self.y+1] == 0:
                self.y = self.y + 1

    def get_neighbors(self, detected_map):
        neighbors = []

        if self.x > 0:
            if detected_map.surface[self.x - 1][self.y] == 0:
                neighbors.append((self.x - 1, self.y))

        if self.y > 0:
            if detected_map.surface[self.x][self.y - 1] == 0:
                neighbors.append((self.x, self.y - 1))

        if self.x < 19:
            if detected_map.surface[self.x + 1][self.y] == 0:
                neighbors.append((self.x + 1, self.y))

        if self.y < 19:
            if detected_map.surface[self.x][self.y + 1] == 0:
                neighbors.append((self.x, self.y + 1))

        return neighbors

    def move_dfs(self, detected_map):
        unvisited_neighbors = list(
            filter(lambda x: x not in self.visited,
                   self.get_neighbors(detected_map))
        )

        if not unvisited_neighbors:
            if not self.back:
                (self.x, self.y) = (None, None)
                return

            (self.x, self.y) = self.back.pop()
            return

        self.back.append((self.x, self.y))
        new_pos = unvisited_neighbors.pop()
        (self.x, self.y) = new_pos
        self.visited.add(new_pos)
