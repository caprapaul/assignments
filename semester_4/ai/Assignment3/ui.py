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
import re
import matplotlib
import matplotlib.pyplot as plt


class UI(clisys.CLISys):
    def __init__(self, controller: Controller):
        super().__init__()
        self.__controller = controller
        self.__best_individuals = []
        self.__stats = Statistics()

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
                screen.blit(image(self.__controller.map), (0, 0))
                pygame.display.flip()

            run_pygame(update)

    @clisys.command(name='solve')
    def solve(self, args):
        """
        Run the solver.
        """
        self.__best_individuals, self.__stats = self.__controller.solver(utils.POSITION, utils.PARENTS_COUNT, utils.MAX_MUTATIONS, utils.MUTATE_PROBABILITY,
                                                                         utils.CROSSOVER_PROBABILITY, utils.ITERATIONS, utils.RUNS, utils.POPULATION_SIZE, utils.INDIVIDUAL_SIZE)

    @clisys.command(name='stats')
    def stats(self, args):
        """
        Visualize the statistics for a run.
            stats - view stats of all runs
            stats <run> - view stats of a run
        """
        if len(args) == 1:
            x = []
            averages = []
            run = int(args[0])

            for i, iteration in enumerate(self.__stats.iterations_fitness_average[run]):
                x.append(i)
                averages.append(iteration)

            plt.plot(x, averages)
            plt.show()
            print(f'Execution Time: {self.__stats.execution_time[run]}')

        elif len(args) == 0:
            print(f'Fitness Std: {self.__stats.fitness_std}')
            print(f'Fitness Average: {self.__stats.fitness_average}')

    @clisys.command(name='view')
    def view(self, args):
        """
        View the drone moving on a path.
        """
        if len(args) == 1:
            run = int(args[0])
            path = self.__best_individuals[run]

        elif len(args) == 0:
            path = self.__best_individuals[0].compute_path(
                self.__controller.map, utils.POSITION)
            moving_drone(self.__controller.map, path)

    @clisys.command(name='exit')
    def exit_command(self, args):
        """
        Exits the program.
        """
        exit(0)

    @clisys.command(name='reload')
    def reload(self, args):
        """
        Reload the parameters.
        """
        importlib.reload(utils)

    @clisys.exception_handler
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

    @clisys.input_handler
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
