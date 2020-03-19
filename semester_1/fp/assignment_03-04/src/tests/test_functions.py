from src.functions import *
from src.repository import Repository
from src.transaction import Transaction
from src.tests.testing import test_function


@test_function
def test_get_balance():
    repo = Repository()

    repo.add_item(Transaction(2, 1909, 'in', 'freelancing'))
    repo.add_item(Transaction(24, 178, 'out', 'food'))
    repo.add_item(Transaction(1, 1200, 'out', 'rent'))
    repo.add_item(Transaction(14, 54, 'out', 'food'))
    repo.add_item(Transaction(14, 55023, 'in', 'salary'))
    repo.add_item(Transaction(16, 550, 'in', 'freelancing'))
    repo.add_item(Transaction(23, 1200, 'out', 'project'))
    repo.add_item(Transaction(2, 230, 'out', 'food'))
    repo.add_item(Transaction(16, 176, 'out', 'food'))
    repo.add_item(Transaction(5, 188, 'out', 'food'))

    assert get_balance(repo, 2) == 479
    assert get_balance(repo, 5) == 291


@test_function
def test_get_sum():
    repo = Repository()

    repo.add_item(Transaction(2, 1909, 'in', 'freelancing'))
    repo.add_item(Transaction(24, 178, 'out', 'food'))
    repo.add_item(Transaction(1, 1200, 'out', 'rent'))
    repo.add_item(Transaction(14, 54, 'out', 'food'))
    repo.add_item(Transaction(14, 55023, 'in', 'salary'))
    repo.add_item(Transaction(16, 550, 'in', 'freelancing'))
    repo.add_item(Transaction(23, 1200, 'out', 'project'))
    repo.add_item(Transaction(2, 230, 'out', 'food'))
    repo.add_item(Transaction(16, 176, 'out', 'food'))
    repo.add_item(Transaction(5, 188, 'out', 'food'))

    assert get_sum(repo, 'in') == 57482
    assert get_sum(repo, 'out') == 3226


@test_function
def test_get_max():
    repo = Repository()

    repo.add_item(Transaction(2, 1909, 'in', 'freelancing'))
    repo.add_item(Transaction(2, 178, 'out', 'food'))
    repo.add_item(Transaction(1, 1200, 'out', 'rent'))
    repo.add_item(Transaction(14, 54, 'out', 'food'))
    repo.add_item(Transaction(14, 55023, 'in', 'salary'))
    repo.add_item(Transaction(14, 550, 'in', 'freelancing'))
    repo.add_item(Transaction(23, 1200, 'out', 'project'))
    repo.add_item(Transaction(2, 230, 'out', 'food'))
    repo.add_item(Transaction(16, 176, 'out', 'food'))
    repo.add_item(Transaction(5, 188, 'out', 'food'))

    assert get_max(repo, 'in', 14).get_money_amount() == 55023
    assert get_max(repo, 'out', 2).get_money_amount() == 230


if __name__ == '__main__':
    test_get_balance()
    test_get_sum()
    test_get_max()