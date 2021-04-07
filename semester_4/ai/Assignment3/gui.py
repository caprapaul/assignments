# -*- coding: utf-8 -*-

from pygame.locals import *
import pygame
import time
from utils import *
from domain import *
import threading


def init_pygame(dimension):
    # init the pygame
    pygame.init()
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration with AE")

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode(dimension)
    screen.fill(WHITE)
    return screen


def run_pygame(update=lambda events: None):
    # closes the pygame
    running = True
    # loop for events
    while running:
        # event handling, gets all event from the event queue
        events = pygame.event.get()
        for event in events:
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False

        update(events)

    pygame.quit()


def moving_drone(mapp, path, speed=1,  mark_seen=True):
    # animation of a drone on a path

    screen = init_pygame((mapp.n * 20, mapp.m * 20))
    drona = pygame.image.load("drona.png")
    running = True
    i = 0

    def update(events):
        nonlocal i

        if i >= len(path):
            return

        pos = path[i]

        if mark_seen:
            brick = pygame.Surface((20, 20))
            brick.fill(GREEN)
            directions = [(0, 1), (1, 0), (-1, 0), (0, -1)]

            for direction in directions:
                x, y = pos
                mapp.detect(x, y)

                while mapp.check_position((x + direction[0], y + direction[1])):
                    x = x + direction[0]
                    y = y + direction[1]

                    mapp.detect(x, y)

        screen.blit(image(mapp), (0, 0))
        i += 1
        screen.blit(drona, (pos[1] * 20, pos[0] * 20))
        pygame.display.flip()
        time.sleep(0.5 * speed)

    run_pygame(update)


def image(currentMap, colour=BLUE, background=WHITE):
    # creates the image of a map

    imagine = pygame.Surface((currentMap.n * 20, currentMap.m * 20))
    brick = pygame.Surface((20, 20))
    brick.fill(colour)
    detected = pygame.Surface((20, 20))
    detected.fill(GREEN)
    imagine.fill(background)
    for i in range(currentMap.n):
        for j in range(currentMap.m):
            if (currentMap.surface[i][j] == 1):
                imagine.blit(brick, (j * 20, i * 20))
            if (currentMap.surface[i][j] == 2):
                imagine.blit(detected, (j * 20, i * 20))

    return imagine


#movingDrone(m, path)
