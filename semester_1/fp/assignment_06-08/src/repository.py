from src.cmdsys.cmdsys import CommandSystem, Command
import random


class RepositoryError(Exception):
    def __init__(self, outer_instance: "Repository", message):
        super().__init__(outer_instance, message)


class Repository(CommandSystem):
    UID_LEN: int = 4
    UID_CHARS: str = '1234567890abcdefghijklmnopqrstuvwxyz'

    def __init__(self):
        super().__init__()
        self._items = {}

    def generate_uid(self):
        """
        Generates a unique id of length UID_LEN from the characters in UID_CHARS.
        :return uid: str - A unique id.
        """
        uid = ''
        chars_list = list(Repository.UID_CHARS)

        while uid in self._items.keys() or uid == '':
            uid_list = []

            for i in range(Repository.UID_LEN):
                rand_i = random.randrange(0, len(chars_list))
                uid_list.append(chars_list[rand_i])

            uid = ''.join(uid_list)

        return uid

    class get_item(Command):
        """
        Gets an item from the list.
        :param condition: A condition function.
        :return item: The first item that meets the condition.
        """
        def __init__(self, uid: str = '', condition=None, outer_instance: "Repository" = None):
            super().__init__(outer_instance)

            if condition is None and uid == '' or condition is not None and uid != '':
                raise RepositoryError('Exactly one parameter needed.')

            self.uid = uid
            self.condition = condition

        def execute(self):
            if self.uid != '':
                if self.uid not in self.outer_instance._items:
                    return None

                return self.outer_instance._items[self.uid]

            for item in self.outer_instance._items.values():
                if self.condition(item):
                    return item

            return None

    class get_items(Command):
        """
        Gets an item from the list.
        :param condition: A condition function.
        :return items: A list of items that meet the condition.
        """
        def __init__(self, condition=lambda item: True, outer_instance: "Repository" = None):
            super().__init__(outer_instance)

            self.condition = condition

        def execute(self):
            found_items = []
            for item in self.outer_instance._items.values():
                if self.condition(item):
                    found_items.append(item)

            return found_items

    class add_item(Command):
        """
        Adds an item to the list.
        :param item: The item to add.
        :return uid: The uid of the added item.
        """
        def __init__(self, item, get_uid=None, outer_instance: "Repository" = None):
            super().__init__(outer_instance, undo_enabled=True)

            self.item = item
            self.uid = 0
            self.get_uid = get_uid

        def execute(self):
            if self.get_uid is None:
                self.uid = self.outer_instance.generate_uid()

            else:
                self.uid = self.get_uid(self.item)

            if self.uid in self.outer_instance._items:
                raise RepositoryError('UID is already in the repository!')

            self.outer_instance._items[self.uid] = self.item
            return self.uid

        def undo(self):
            self.outer_instance._items.pop(self.uid)

    class remove_item(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """

        def __init__(self, uid: str = '', condition=None, outer_instance: "Repository" = None):
            super().__init__(outer_instance, undo_enabled=True)

            if condition is None and uid == '' or condition is not None and uid != '':
                raise RepositoryError('Exactly one parameter needed.')

            self.uid = uid
            self.condition = condition
            self.removed_item = (0, None)

        def execute(self):
            if self.uid != '':
                if self.uid not in self.outer_instance._items:
                    raise RepositoryError('UID is not in the repository!')

                item = self.outer_instance._items.pop(self.uid)
                self.removed_item = (self.uid, item)

                return item

            items_copy = self.outer_instance._items.copy()

            for i, item in items_copy.items():
                if self.condition(item):
                    self.removed_item = (i, item)
                    return self.outer_instance._items.pop(i)

        def undo(self):
            self.outer_instance._items[self.removed_item[0]] = self.removed_item[1]

    class remove_items(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self, condition, outer_instance: "Repository"):
            super().__init__(outer_instance, undo_enabled=True)

            self.condition = condition
            self.removed_items = {}

        def execute(self):
            items_copy = self.outer_instance._items.copy()

            for i, item in items_copy.items():
                if self.condition(item):
                    self.removed_items[i] = item
                    self.outer_instance._items.pop(i)

        def undo(self):
            for i, item in self.removed_items.items():
                self.outer_instance._items[i] = item

    class clear_items(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self, outer_instance: "Repository"):
            super().__init__(outer_instance, undo_enabled=True)

            self.removed_items = {}

        def execute(self):
            items_copy = self.outer_instance._items.copy()

            for i, item in items_copy.items():
                self.removed_items[i] = item
                self.outer_instance._items.pop(i)

        def undo(self):
            for i, item in self.removed_items.items():
                self.outer_instance._items[i] = item

    class replace_item(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """

        def __init__(self, new_item, uid: str = '', condition=None, outer_instance: "Repository" = None):
            super().__init__(outer_instance, undo_enabled=True)

            if condition is None and uid == '' or condition is not None and uid != '':
                raise RepositoryError('Exactly one parameter needed.')

            self.uid = uid
            self.condition = condition
            self.new_item = new_item
            self.replaced_item = (0, None)

        def execute(self):
            if self.uid != '':
                if self.uid not in self.outer_instance._items:
                    raise RepositoryError('UID is not in the repository!')

                self.replaced_item = (self.uid, self.outer_instance._items[self.uid])
                self.outer_instance._items[self.uid] = self.new_item
                return

            for i, item in self.outer_instance._items.items():
                if self.condition(item):
                    self.replaced_item = (i, self.outer_instance._items[i])
                    self.outer_instance._items[i] = self.new_item
                    break

        def undo(self):
            self.outer_instance._items[self.replaced_item[0]] = self.replaced_item[1]
