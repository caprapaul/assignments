# -*- coding: utf-8 -*-


# imports
from gui import *
from controller import *
from repository import *
from domain import *
import utils
import importlib

from clisys import clisys
from clisys import exceptions
import pygame
from pygame.locals import *
import re
import matplotlib
import matplotlib.pyplot as plt


class UI(clisys.CLISys):
    def __init__(self, controller: Controller):
        super().__init__()
        self.__controller = controller
        self.__solution = None

    @clisys.command(name='help')
    def help(self, args):
        """
        Displays help for all commands or a single command.
            help
            help <command>
        """
        count = len(args)
        commands = self.get_commands()

        if count == 0:
            for cmd_name, cmd in commands.items():
                print(f'{cmd_name}: {cmd.__doc__}')

        elif count == 1:
            cmd_name = args[0]

            if not (cmd_name in commands.keys()):
                raise exceptions.InvalidArgument(args[0])

            cmd = commands[cmd_name]

            print(f'{cmd_name}: {cmd.__doc__}')

    @clisys.command(name='map')
    def map_command(self, args):
        """
        Map operations.
            map random [fill=0.2] - randomize map
            map save - save map to file
            map load - load map from file
            map view - visualize map
        """
        option = args[0]

        if option == 'random':
            if len(args) == 2:
                fill = float(args[1])
                self.__controller.map.randomize(fill)

            else:
                self.__controller.map.randomize()

        elif option == 'load':
            self.__controller.load_map()

        elif option == 'save':
            self.__controller.save_map()

        elif option == 'view':
            screen = init_pygame(utils.WINDOW_SIZE)

            def update(events):
                img = image()
                img = image_map(img, self.__controller.map)
                img = image_sensors(img, self.__controller.sensors)
                screen.blit(img, (0, 0))
                pygame.display.flip()

            run_pygame(update)

    @ clisys.command(name='solve')
    def solve(self, args):
        """
        Run the solver.
        """
        self.__controller.create_graph(utils.POSITION, utils.INITIAL_PHEROMONE)
        self.__solution = self.__controller.solve(utils.ANT_ENERGY, utils.ANTS_COUNT, utils.Q0,
                                                  utils.COST_POWER, utils.PHEROMONE_POWER, utils.EVAPORATION_RATE, utils.EPOCH_COUNT)

        self.__controller.update_sensors(self.__solution[0])
        print(self.__solution)

    @ clisys.command(name='graph')
    def graph(self, args):
        """
        Create a graph from the starting position and sensor positions.
        """
        self.__controller.create_graph(utils.POSITION, utils.INITIAL_PHEROMONE)

    @ clisys.command(name='path')
    def path(self, args):
        """
        View the path.
        """
        path = self.__controller.get_path(self.__solution[0])
        print(path)

        screen = init_pygame(utils.WINDOW_SIZE)

        show_path = True
        show_coverage = True
        show_sensors = True
        show_drone = True

        def update(events):
            nonlocal show_path
            nonlocal show_coverage
            nonlocal show_sensors
            nonlocal show_drone

            for event in events:
                if event.type == pygame.KEYDOWN:
                    pressed_keys = pygame.key.get_pressed()

                    if pressed_keys[pygame.K_1]:
                        show_path = not show_path

                    if pressed_keys[pygame.K_2]:
                        show_coverage = not show_coverage

                    if pressed_keys[pygame.K_3]:
                        show_sensors = not show_sensors

                    if pressed_keys[pygame.K_4]:
                        show_drone = not show_drone

            img = image()
            img = image_map(img, self.__controller.map)

            if show_path:
                img = image_path(img, path)

            if show_coverage:
                img = image_coverage(img, self.__controller.sensors)

            if show_sensors:
                img = image_sensors(img, self.__controller.sensors)

            if show_drone:
                img = image_drone(img, utils.POSITION)

            img = image_instructions(img)
            screen.blit(img, (0, 0))
            pygame.display.flip()

        run_pygame(update)

    @ clisys.command(name='exit')
    def exit_command(self, args):
        """
        Exits the program.
        """
        exit(0)

    @ clisys.command(name='reload')
    def reload(self, args):
        """
        Reload the parameters.
        """
        importlib.reload(utils)

    @ clisys.exception_handler
    def handle_exceptions(self, exception: Exception):
        """
        Handles exceptions raised in commands.
        :param exception: The exception.
        :return:
        """
        try:
            raise exception

        except exceptions.InvalidCommand as e:
            print(f'Invalid command: "{str(e.command_name)}".')

        except exceptions.InvalidArgument as e:
            print(f'Invalid argument: "{str(e.argument_name)}".')

        except exceptions.InvalidArgumentCount:
            print(f'Invalid argument count.')

    @ clisys.input_handler
    def get_input(self):
        """
        Gets the input and returns it as a list
        :return: A list of strings.
        """
        i = input('\n> ')
        i = re.split(r' +', i)
        i[0] = i[0].lower()

        return i

# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.movingDrone(currentMap, path, speed, markseen)
#              ATENTION! the function doesn't check if the path passes trough walls
