from datetime import datetime
import re
from src.clisys import clisys
from src.cmdsys import cmdsys
from src.functions import *
from src.transaction import Transaction
from src.repository import Repository


def display_transactions(transactions):
    header = 'Id\t|\tDay\t|\tAmount\t|\tType\t|\tDescription'
    print(header)
    print('-' * len(header) * 2)
    
    for i, transaction in enumerate(transactions):
        day = transaction.get_day()
        amount = transaction.get_money_amount()
        type = transaction.get_type()
        description = transaction.get_description()

        print(
            f'{i + 1}.\t\t{day}\t\t{amount}\t\t\t{type}\t\t\t\t{description}')


class TransactionCommands(clisys.CLISys):
    def __init__(self):
        super().__init__()
        self.__repo = Repository()
        self.init_repo()

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
                raise clisys.InvalidArgument(args[0])

            cmd = commands[cmd_name]

            print(f'{cmd_name}: {cmd.__doc__}')

    @clisys.command(name='test')
    def test(self, args):
        """
        Test command.
        """
        print('TEST')

    @clisys.command(name='exit')
    def exit_command(self, args):
        """
        Exits the program.
        """
        exit(0)

    @clisys.command(name='add')
    def add_transaction(self, args):
        """
        Add a transaction to the list.
            add <value> <type> <description>
        """
        try:
            value = int(args[0])

        except ValueError:
            raise clisys.InvalidArgument(args[0])

        type = args[1]
        description = args[2]

        transaction = Transaction(int(datetime.today().strftime('%d')), value, type, description)
        self.__repo.add_item(transaction)

    @clisys.command(name='insert')
    def insert_transaction(self, args):
        """
        Insert a transaction in the list.
            insert <day> <value> <type> <description>
        """
        try:
            day = int(args[0])

        except ValueError:
            raise clisys.InvalidArgument(args[0])

        try:
            value = int(args[1])

        except ValueError:
            raise clisys.InvalidArgument(args[1])

        type = args[2]
        description = args[3]

        transaction = Transaction(day, value, type, description)
        self.__repo.add_item(transaction)

    @clisys.command(name='remove')
    def remove_transaction(self, args):
        """
        Remove transactions from the list.
            remove <day>
            remove <start day> to <end day>
            remove <type>
        """
        count = len(args)
        if count == 1:
            try:
                day = int(args[0])
                self.__repo.remove_items(lambda t: t.get_day() == day)

            except ValueError:
                type = args[0]
                self.__repo.remove_items(lambda t: t.get_type() == type)

        elif count == 3:
            if args[1] != 'to':
                raise clisys.InvalidArgument(args[1])

            start_day = int(args[0])
            end_day = int(args[2])
            self.__repo.remove_items(lambda t: start_day <= t.get_day() <= end_day)

        else:
            raise clisys.InvalidArgumentCount

    @clisys.command(name='replace')
    def replace_transaction(self, args):
        """
        Replace the amount of a transaction with a given value.
            replace <day> <type> <description> with <value>
        """
        if len(args) != 5:
            raise clisys.InvalidArgumentCount

        if args[3] != 'with':
            raise clisys.InvalidArgument(args[3])

        try:
            day = int(args[0])

        except ValueError:
            raise clisys.InvalidArgument(args[0])

        type = args[1]
        description = args[2]
        try:
            value = int(args[4])
        except ValueError:
            raise clisys.InvalidArgument(args[4])

        self.__repo.replace_item(lambda t: t.get_day() == day and
                                           t.get_type() == type and
                                           t.get_description() == description,
                                 Transaction(day, value, type, description))

    @clisys.command(name='list')
    def list_transactions(self, args):
        """
        Display the list of transactions.
            list
            list <type>
            list [ < | = | > ] <value>
            list balance <day>
        """
        count = len(args)
        if count == 0:
            display_transactions(self.__repo.get_items())

        elif count == 1:
            type = args[0]
            display_transactions(self.__repo.get_items(lambda t: t.get_type() == type))

        elif count == 2:
            option = args[0]
            if option == 'balance':
                try:
                    day = int(args[1])

                except ValueError:
                    raise clisys.InvalidArgument(args[1])

                balance = get_balance(self.__repo, day)

                print(f"Balance on day {day}: {balance}")

            elif option in ['<', '=', '>']:
                try:
                    amount = int(args[1])

                except ValueError:
                    raise clisys.InvalidArgument(args[1])

                if option == '<':
                    display_transactions(self.__repo.get_items(lambda t: t.get_money_amount() < amount))

                elif option == '=':
                    display_transactions(self.__repo.get_items(lambda t: t.get_money_amount() == amount))

                elif option == '>':
                    display_transactions(self.__repo.get_items(lambda t: t.get_money_amount() > amount))

            else:
                raise clisys.InvalidArgument(args[0])

        else:
            raise clisys.InvalidArgumentCount

    @clisys.command(name='sum')
    def sum_transactions(self, args):
        """
        Displays the total amount from a transaction type.
            sum <type>
        """
        if len(args) > 1:
            raise clisys.InvalidArgumentCount

        type = args[0]
        result = get_sum(self.__repo, type)

        print(f'Total amount from "{type}" transactions: {result}')

    @clisys.command(name='max')
    def max_transaction(self, args):
        if len(args) != 2:
            raise clisys.InvalidArgumentCount

        type = args[0]
        try:
            day = int(args[1])

        except ValueError:
            raise clisys.InvalidArgument(args[1])

        result = get_max(self.__repo, type, day)

        if result is None:
            print(f'No transaction of type "{type}" on day {day}.')

        else:
            print(f'The maximum "{type}" transaction on  day {day}: "{result.get_description()}: {result.get_money_amount()}"')

    @clisys.command(name='filter')
    def filter_transactions(self, args):
        """
        Filters the transactions.
            filter <type>
            filter <type> <value>
        """
        count = len(args)

        if count == 1:
            type = args[0]

            self.__repo.remove_items(lambda t: t.get_type() != type)

        elif count == 2:
            type = args[0]

            try:
                value = int(args[1])

            except ValueError:
                raise clisys.InvalidArgument([args[1]])

            self.__repo.remove_items(lambda t: t.get_type() != type or t.get_money_amount() >= value)

        print('Transactions filtered successfully!')

    @clisys.command(name='undo')
    def undo(self, args):
        """
        Undo the last command that changed the transactions list.
            undo
        """
        try:
            self.__repo.undo()
            print('Undo executed successfully!')

        except cmdsys.EmptyActionsStack:
            print('Nothing to undo.')

    @clisys.command(name='redo')
    def redo(self, args):
        """
        Redo the last undo-ed command.
            redo
        """
        try:
            self.__repo.redo()
            print('Redo executed successfully!')

        except cmdsys.EmptyUndoStack:
            print('Nothing to redo.')

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
            print(f'Invalid command: "{str(e.command_name)}" .')

        except clisys.InvalidArgument as e:
            print(f'Invalid argument: "{str(e.argument_name)}" .')

        except clisys.InvalidArgumentCount:
            print(f'Invalid argument count.')

    @clisys.input_handler
    def get_input(self):
        """
        Gets the input and returns it as a list
        :return: A list of strings.
        """
        i = input('\n> ')
        i = re.split(r' +', i)

        return i

    def init_repo(self):
        self.__repo.add_item(Transaction(2, 1909, 'in', 'freelancing'))
        self.__repo.add_item(Transaction(24, 178, 'out', 'food'))
        self.__repo.add_item(Transaction(1, 1200, 'out', 'rent'))
        self.__repo.add_item(Transaction(14, 54, 'out', 'food'))
        self.__repo.add_item(Transaction(14, 55023, 'in', 'salary'))
        self.__repo.add_item(Transaction(16, 550, 'in', 'freelancing'))
        self.__repo.add_item(Transaction(23, 1200, 'out', 'project'))
        self.__repo.add_item(Transaction(2, 230, 'out', 'food'))
        self.__repo.add_item(Transaction(16, 176, 'out', 'food'))
        self.__repo.add_item(Transaction(5, 188, 'out', 'food'))


if __name__ == '__main__':
    t = TransactionCommands()
    t.run()
