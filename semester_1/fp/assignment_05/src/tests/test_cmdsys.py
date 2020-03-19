from src.cmdsys.cmdsys import CommandSystem
from src.cmdsys.exceptions import *
from src.cmdsys.command import Command
from src.tests.testing import test_function


@test_function
def test_command_system():
    class TestSystem(CommandSystem):
        def __init__(self, message):
            super().__init__()
            self.message = message

        class test_command(Command):
            def __init__(self, message):
                self.__message = message
                self.__old_message = ''

            @property
            def undo_enabled(self):
                return True

            def execute(self, outer_instance: "TestSystem"):
                self.__old_message = outer_instance.message
                outer_instance.message = self.__message

            def undo(self, outer_instance: "TestSystem"):
                outer_instance.message = self.__old_message

    t = TestSystem('initial')
    assert t.message == 'initial'
    t.test_command('test')
    assert t.message == 'test'

    t.test_command('test2')
    assert t.message == 'test2'

    t.undo()
    assert t.message == 'test'

    t.undo()
    assert t.message == 'initial'

    try:
        t.undo()
        assert False

    except EmptyActionsStack:
        assert True


if __name__ == '__main__':
    test_command_system()
