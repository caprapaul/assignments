from src.repository import Repository
from src.transaction import Transaction


def get_balance(repo: Repository, day: int):
    """
    Returns the account balance on a day.
    :param repo: The transactions repository.
    :param day: A day.
    :return balance: The balance on the given day.
    """
    in_transactions = repo.get_items(lambda t: t.get_type() == 'in' and t.get_day() <= day)
    out_transactions = repo.get_items(lambda t: t.get_type() == 'out' and t.get_day() <= day)

    balance = 0

    for in_transaction in in_transactions:
        balance += in_transaction.get_money_amount()

    for out_transaction in out_transactions:
        balance -= out_transaction.get_money_amount()

    return balance


def get_sum(repo: Repository, type: str):
    """
    Returns the total amount from a transaction type.
    :param repo: The transactions repository.
    :param type: The transaction type.
    :return type_amount: The total amount from a transaction type.
    """
    transactions = repo.get_items(lambda t: t.get_type() == type)

    type_amount = 0

    for transaction in transactions:
        type_amount += transaction.get_money_amount()

    return type_amount


def get_max(repo: Repository, type: str, day: int):
    """
    Returns the transaction with the maximum amount from a day, of a type.
    :param repo: The transactions repository.
    :param type: The transaction type.
    :param day: The transaction day.
    :return max_transaction: The transaction with the maximum amount from a day, of a type.
    """
    transactions = repo.get_items(lambda t: t.get_day() == day and t.get_type() == type)

    if len(transactions) == 0:
        return None

    max_transaction: Transaction = transactions[0]

    for transaction in transactions:
        if transaction.get_money_amount() > max_transaction.get_money_amount():
            max_transaction = transaction

    return max_transaction
