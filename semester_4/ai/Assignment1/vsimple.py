

# import the pygame module, so you can use it
import pygame
from pygame.locals import *
from random import randint

from environment import Environment
from dmap import DMap
from drone import Drone

from constants import *


def main():
    # we create the environment
    e = Environment()
    # e.load_environment("test2.map")
    e.random_map(0.3)
    # print(str(e))

    # we create the map
    m = DMap()

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)

    # cream drona
    d = Drone(x, y)

    # create a surface on screen that has the size of 800 x 480
    width = 800
    height = 400
    screen = pygame.display.set_mode((width, height))
    screen.fill(WHITE)
    screen.blit(e.image(), (0, 0))

    font = pygame.font.SysFont('Arial', 24)
    img = font.render('Finished', True, BLACK, WHITE)
    rect = img.get_rect()
    rect.center = (width // 2, height)

    # define a variable to control the main loop
    running = True
    auto = True
    delay = 500

    message_shown = False

    # main loop
    while running:
        m.mark_detected_walls(e, d.x, d.y)

        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == QUIT:
                # change the value to False, to exit the main loop
                running = False

            if event.type == KEYDOWN:
                # change auto movement speed
                pressed_keys = pygame.key.get_pressed()

                if pressed_keys[K_UP]:
                    delay //= 2

                if pressed_keys[K_DOWN]:
                    delay *= 2

                delay = max(10, delay)

                if (not auto) and not d.is_finished():
                    d.move_dfs(m)

        if auto and not d.is_finished():
            d.move_dfs(m)
            pygame.time.delay(delay)

        screen.blit(m.image(d.x, d.y), (400, 0))

        pygame.display.flip()

    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()
