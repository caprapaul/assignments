from expense import Expense, ExpenseError
from src.clisys import clisys
from src.cmdsys import cmdsys
from src.repository import Repository


def read_expense():
    day, amount, type = input('Input expense: <day> <money_amount> <type>\n').split(' ')
    day = int(day)
    amount = int(amount)

    expense = Expense(day, amount, type)
    return expense


class UI(clisys.CLISys):
    def __init__(self):
        super().__init__()
        self.__repo = Repository()
        self.init_repo()

    @clisys.command('1', description='Add expense.')
    def add_expense(self, args):
        try:
            expense = read_expense()

        except ValueError:
            raise ExpenseError('Invalid expense.')

        self.__repo.add_item(expense)
        print('Expense added successfully!')

    @clisys.command('2', description='Show expenses.')
    def list_expenses(self, args):
        """
        Displays the list of expenses.
        :param args:
        :return:
        """
        expenses = self.__repo.get_items()

        print('Id\t|\tDay\t|\tAmount\t|\tType', end='\n\n')
        for i, expense in enumerate(expenses):
            print(f'{i + 1}.\t\t{expense.day}\t\t{expense.money_amount}\t\t\t{expense.type}')

    @clisys.command(name='3', description='Filter expenses.')
    def filter_expenses(self, args):
        """
        Filter the expenses list
        :param args:
        :return:
        """
        try:
            min_value = int(input('Input the minimum value: '))

        except ValueError:
            raise ValueError('Invalid minimum value.')

        self.__repo.remove_items(lambda e: e.money_amount <= min_value)

        print('Expenses filtered successfully!')

    @clisys.command(name='4', description='Undo.')
    def undo(self, args):
        """
        Undo the last command that changed the expenses list.
        :param args:
        :return:
        """
        self.__repo.undo()
        print('Undo executed successfully!')

    @clisys.command(name='5', description='Redo.')
    def redo(self, args):
        """
        Undo the last command that changed the expenses list.
        :param args:
        :return:
        """
        self.__repo.redo()
        print('Redo executed successfully!')

    @clisys.command(name='-1', description='Exit.')
    def exit_program(self, args):
        """
        Exits the program.
        """
        exit(0)

    @clisys.exception_handler
    def handle_exceptions(self, exception: Exception):
        """
        Handles exceptions raised in commands.
        :param exception: The exception.
        :return:
        """
        try:
            raise exception

        except clisys.InvalidCommand as e:
            print(f'Invalid option: "{str(e.command_name)}" .')

        except clisys.InvalidArgument as e:
            print(f'Invalid argument: "{str(e.argument_name)}" .')

        except clisys.InvalidArgumentCount:
            print('Invalid argument count.')

        except cmdsys.EmptyActionsStack:
            print('Nothing to undo.')

        except cmdsys.EmptyUndoStack:
            print('Nothing to redo.')

        except ExpenseError as e:
            print(e)

        except ValueError as e:
            print(e)

    def display_options(self):
        """
        Displays the list of options.
        :return:
        """
        print()
        options = list(self.get_commands().values())
        options.sort(key=lambda op: op.name)

        for option in options:
            print(f'{option.name}. {option.description}')

    @clisys.input_handler
    def get_option(self):
        """
        Gets the input and returns it as a list
        :return: A list of strings. (first element is the name of the command)
        """
        self.display_options()
        i = input('\nOption: ')

        return [i]

    def init_repo(self):
        self.__repo.add_item(Expense(1, 10, 'food'))
        self.__repo.add_item(Expense(1, 120, 'internet'))
        self.__repo.add_item(Expense(1, 112, 'food'))
        self.__repo.add_item(Expense(4, 20, 'food'))
        self.__repo.add_item(Expense(4, 100, 'electricity'))
        self.__repo.add_item(Expense(6, 980, 'phone'))
        self.__repo.add_item(Expense(8, 1, 'food'))
        self.__repo.add_item(Expense(8, 16, 'food'))
        self.__repo.add_item(Expense(23, 100, 'food'))
        self.__repo.add_item(Expense(30, 233, 'gas'))


if __name__ == '__main__':
    ui = UI()
    ui.run()
