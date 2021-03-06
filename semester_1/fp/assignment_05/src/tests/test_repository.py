from src.repository import Repository
from src.tests.testing import test_function


@test_function
def test_add_item():
    repo = Repository()

    repo.add_item(1)
    assert repo.get_items() == [1]
    repo.undo()
    assert repo.get_items() == []


@test_function
def test_get_items():
    repo = Repository()

    repo.add_item(0)
    repo.add_item(1)
    assert repo.get_item(lambda item: item == 1) == 1

    repo.add_item(1)
    assert repo.get_items() == [0, 1, 1]
    assert repo.get_items(lambda item: item == 1) == [1, 1]
    assert not repo.get_items(lambda item: item > 1)

    repo.add_item(2)
    assert repo.get_items(lambda item: item > 1) == [2]


@test_function
def test_remove_items():
    repo = Repository()

    repo.add_item(0)
    repo.add_item(1)
    repo.add_item(1)
    repo.add_item(1)

    repo.remove_item(lambda item: item == 1)
    assert repo.get_items() == [0, 1, 1]
    repo.undo()
    assert repo.get_items() == [0, 1, 1, 1]

    repo.remove_items(lambda item: item == 1)
    assert repo.get_items() == [0]
    repo.undo()
    assert repo.get_items() == [0, 1, 1, 1]


@test_function
def test_replace_item():
    repo = Repository()

    repo.add_item(0)
    repo.add_item(1)
    repo.add_item(1)
    repo.add_item(1)

    repo.replace_item(lambda item: item == 1, 0)
    assert repo.get_items() == [0, 0, 1, 1]
    repo.undo()
    assert repo.get_items() == [0, 1, 1, 1]


if __name__ == '__main__':
    test_add_item()
    test_get_items()
    test_remove_items()
    test_replace_item()
