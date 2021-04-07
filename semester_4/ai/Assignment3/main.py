from controller import Controller
from repository import Repository
from ui import UI


def main():
    repository = Repository()
    repository.mapp.randomize()
    controller = Controller(repository)
    ui = UI(controller)

    ui.run()


if __name__ == '__main__':
    main()
