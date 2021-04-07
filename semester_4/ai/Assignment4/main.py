from controller import Controller
from repository import Repository
from ui import UI
from utils import *


def main():
    repository = Repository()
    repository.mapp.randomize()
    repository.random_sensors(SENSORS_COUNT, SENSORS_MAX_POWER)
    controller = Controller(repository)
    ui = UI(controller)

    ui.run()


if __name__ == '__main__':
    main()
