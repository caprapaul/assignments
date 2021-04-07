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

        screen.blit(image(mapp), (0, 0))
        i += 1
        screen.blit(drona, (pos[1] * 20, pos[0] * 20))
        pygame.display.flip()
        time.sleep(0.5 * speed)

    run_pygame(update)


def image():
    img = pygame.Surface(WINDOW_SIZE)
    img.fill(WHITE)

    return img


def image_map(img, currentMap, wall=BLUE, background=WHITE):
    # creates the image of a map

    imagine = pygame.Surface((currentMap.n * 20, currentMap.m * 20))
    imagine.fill(background)

    brick = pygame.Surface((20, 20))
    brick.fill(wall)

    for i in range(currentMap.n):
        for j in range(currentMap.m):
            if (currentMap.surface[i][j] == WALL):
                imagine.blit(brick, (j * 20, i * 20))

    img.blit(imagine, (0, 0))

    return img


def image_drone(img, position):
    drone = pygame.image.load("drona.png")

    img.blit(drone, (position[1] * 20, position[0] * 20))

    return img


def image_path(img, path):
    path_tile = pygame.Surface((20, 20))
    path_tile.fill(GRAYBLUE)

    for x, y in path:
        img.blit(path_tile, (y * 20, x * 20))

    return img


def image_coverage(img, sensors):
    covered = pygame.Surface((20, 20))
    covered.fill(GREEN)

    for sensor in sensors.values():
        for covered_tile in sensor.covered[sensor.power]:
            img.blit(
                covered, (covered_tile[1] * 20, covered_tile[0] * 20))

    return img


def image_sensors(img, sensors):
    sensor_img = pygame.image.load("sensor.png")

    for sensor in sensors.values():
        x, y = sensor.position
        img.blit(sensor_img, (y * 20, x * 20))

    return img


def image_instructions(img):
    font = pygame.font.Font('freesansbold.ttf', 10)

    instructions = '1 - toggle path; 2 - toggle coverage; 3 - toggle sensors; 4 - toggle drone'
    text = font.render(instructions, True, WHITE, BLACK)
    textRect = text.get_rect()
    textRect.bottomleft = (0, WINDOW_SIZE[1])
    img.blit(text, textRect)

    return img


# movingDrone(m, path)
