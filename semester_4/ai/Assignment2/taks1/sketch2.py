

# import the pygame module, so you can use it
import pickle
import pygame
import time
from pygame.locals import *
from random import random, randint
import numpy as np
from constants import *
from map import Map
from drone import Drone
from service import Service
import time


def displayWithPath(image, path, color=GREEN):
    mark = pygame.Surface((20, 20))
    mark.fill(color)
    for move in path:
        image.blit(mark, (move[1] * 20, move[0] * 20))

    return image


def displayText(image, width, height, greedy_time, a_star_time):
    font = pygame.font.Font('freesansbold.ttf', 16)

    text = font.render(
        f'Greedy: {greedy_time * 1000:0.2f}ms', True, RED, BLACK)
    textRect = text.get_rect()
    textRect.midleft = (0, height - 40)
    image.blit(text, textRect)

    text = font.render(
        f'A-Star: {a_star_time * 1000:0.2f}ms', True, YELLOW, BLACK)
    textRect = text.get_rect()
    textRect.midleft = (0, height - 20)
    image.blit(text, textRect)

    return image


# define a main function
def main():

    # we create the map
    m = Map()
    # m.randomMap()
    # m.saveMap("test2.map")
    m.loadMap("test1.map")

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Path in simple environment")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)

    # create drona
    d1 = Drone(x, y)
    d2 = Drone(x, y + 1)
    s = Service()

    # create a surface on screen that has the size of 400 x 480
    screen_width = 400
    screen_height = 480
    screen = pygame.display.set_mode((screen_width, screen_height))
    screen.fill(WHITE)

    # define a variable to control the main loop
    running = True
    show_a_star = True
    show_greedy = True

    path_a_star = []
    path_greedy = []
    a_star_time = 0.0
    greedy_time = 0.0

    # main loop
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False

            if event.type == KEYDOWN:
                pressed_keys = pygame.key.get_pressed()

                if pressed_keys[K_1]:
                    show_greedy = not show_greedy

                if pressed_keys[K_2]:
                    show_a_star = not show_a_star

                dir_x = 0
                dir_y = 0

                if pressed_keys[K_UP]:
                    dir_y += 1

                if pressed_keys[K_DOWN]:
                    dir_y -= 1

                if pressed_keys[K_RIGHT]:
                    dir_x += 1

                if pressed_keys[K_LEFT]:
                    dir_x -= 1

                d1.moveTowards(m, dir_x, dir_y)  # this call will be erased
                dir_x = 0
                dir_y = 0

                if pressed_keys[K_w]:
                    dir_y += 1

                if pressed_keys[K_s]:
                    dir_y -= 1

                if pressed_keys[K_d]:
                    dir_x += 1

                if pressed_keys[K_a]:
                    dir_x -= 1

                d2.moveTowards(m, dir_x, dir_y)

                start = time.perf_counter()
                path_a_star = s.searchAStar(m, d1, d1.x, d1.y, d2.x, d2.y)
                end = time.perf_counter()
                a_star_time = end - start

                start = time.perf_counter()
                path_greedy = s.searchGreedy(m, d1, d1.x, d1.y, d2.x, d2.y)
                end = time.perf_counter()
                greedy_time = end - start

        img = m.image()

        if show_greedy and path_greedy:
            img.blit(displayWithPath(img, path_greedy, RED), (0, 0))

        if show_a_star and path_a_star:
            img.blit(displayWithPath(img, path_a_star, YELLOW), (0, 0))

        img.blit(d1.mapWithDrone(img), (0, 0))
        img.blit(d2.mapWithDrone(img), (0, 0))
        screen.blit(img, (0, 0))
        displayText(screen, screen_width, screen_height,
                    greedy_time, a_star_time)
        pygame.display.flip()

    pygame.display.flip()
    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()
