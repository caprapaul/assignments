from datetime import datetime
from src.clisys.clisys import CLISys
from src.clisys import clisys
from src import repository as repo, transaction as tr
from src.functions import *

cli = CLISys()
_transactions = []


def display_transactions(transactions):
    header = 'Id\t|\tDay\t|\tAmount\t|\tType\t|\tDescription'
    print(header)
    print('-' * len(header) * 2)
    for i, transaction in enumerate(transactions):
        day = tr.get_day(transaction)
        amount = tr.get_money_amount(transaction)
        type = tr.get_type(transaction)
        description = tr.get_description(transaction)

        print(
            f'{i + 1}.\t\t{day}\t\t{amount}\t\t\t{type}\t\t\t\t{description}')


@cli.command(name='help')
def __help(args):
    """
    Displays help for all commands or a single command.
        help
        help <command>
    """
    count = len(args)
    commands = cli.get_commands()

    if count == 0:
        for cmd_name, cmd in commands.items():
            print(f'{cmd_name}: {cmd.__doc__}')

    elif count == 1:
        cmd_name = args[0]

        if not (cmd_name in commands.keys()):
            raise clisys.InvalidArgument(args[0])

        cmd = commands[cmd_name]

        print(f'{cmd_name}: {cmd.__doc__}')


@cli.command(name='test')
def test(args):
    """
    Test command.
    """
    print('TEST')


@cli.command(name='exit')
def exit_command(args):
    """
    Exits the program.
    """
    exit(0)


@cli.command(name='add')
def add_transaction(args):
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

    transaction = tr.create(int(datetime.today().strftime('%d')), value, type, description)
    repo.add_item(_transactions, transaction)


@cli.command(name='insert')
def insert_transaction(args):
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

    transaction = tr.create(day, value, type, description)
    repo.add_item(_transactions, transaction)


@cli.command(name='remove')
def remove_transaction(args):
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
            repo.remove_items(_transactions, lambda t: tr.get_day(t) == day)

        except ValueError:
            type = args[0]
            repo.remove_items(_transactions, lambda t: tr.get_type(t) == type)

    elif count == 3:
        if args[1] != 'to':
            raise clisys.InvalidArgument(args[1])

        start_day = int(args[0])
        end_day = int(args[2])
        repo.remove_items(_transactions, lambda t: start_day <= tr.get_day(t) <= end_day)

    else:
        raise clisys.InvalidArgumentCount


@cli.command(name='replace')
def replace_transaction(args):
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

    repo.replace_item(_transactions,
                      lambda t: tr.get_day(t) == day and
                                tr.get_type(t) == type and
                                tr.get_description(t) == description,
                      tr.create(day, value, type, description))


@cli.command(name='list')
def list_transactions(args):
    """
    Display the list of transactions.
        list
        list <type>
        list [ < | = | > ] <value>
        list balance <day>
    """
    count = len(args)
    if count == 0:
        display_transactions(repo.get_items(_transactions))

    elif count == 1:
        type = args[0]
        display_transactions(repo.get_items(_transactions, lambda t: tr.get_type(t) == type))

    elif count == 2:
        option = args[0]
        if option == 'balance':
            try:
                day = int(args[1])

            except ValueError:
                raise clisys.InvalidArgument(args[1])

            balance = get_balance(_transactions, day)

            print(f"Balance on day {day}: {balance}")

        elif option in ['<', '=', '>']:
            try:
                amount = int(args[1])

            except ValueError:
                raise clisys.InvalidArgument(args[1])

            if option == '<':
                display_transactions(repo.get_items(_transactions, lambda t: tr.get_money_amount(t) < amount))

            elif option == '=':
                display_transactions(repo.get_items(_transactions, lambda t: tr.get_money_amount(t) == amount))

            elif option == '>':
                display_transactions(repo.get_items(_transactions, lambda t: tr.get_money_amount(t) > amount))

        else:
            raise clisys.InvalidArgument(args[1])

    else:
        raise clisys.InvalidArgumentCount


@cli.exception_handler
def handle_exceptions(exception: Exception):
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


@cli.input_handler
def get_input():
    """
    Gets the input and returns it as a list
    :return: A list of strings.
    """
    return input('\n> ').split(' ')


def init_repo():
    repo.add_item(_transactions, tr.create(2, 1909, 'in', 'freelancing'))
    repo.add_item(_transactions, tr.create(24, 178, 'out', 'food'))
    repo.add_item(_transactions, tr.create(1, 1200, 'out', 'rent'))
    repo.add_item(_transactions, tr.create(14, 54, 'out', 'food'))
    repo.add_item(_transactions, tr.create(14, 55023, 'in', 'salary'))
    repo.add_item(_transactions, tr.create(16, 550, 'in', 'freelancing'))
    repo.add_item(_transactions, tr.create(23, 1200, 'out', 'project'))
    repo.add_item(_transactions, tr.create(2, 230, 'out', 'food'))
    repo.add_item(_transactions, tr.create(16, 176, 'out', 'food'))
    repo.add_item(_transactions, tr.create(5, 188, 'out', 'food'))


if __name__ == '__main__':
    init_repo()
    cli.run()
