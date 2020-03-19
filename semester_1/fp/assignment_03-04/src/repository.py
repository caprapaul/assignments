from src.cmdsys.cmdsys import CommandSystem
from src.cmdsys.command import Command


class Repository(CommandSystem):
    def __init__(self):
        super().__init__()
        self.items = []

    class get_item(Command):
        """
        Gets an item from the list.
        :param condition: A condition function.
        :return item: The first item that meets the condition.
        """
        def __init__(self, condition):
            self.condition = condition

        @property
        def undo_enabled(self):
            return False

        def execute(self, outer_instance: "Repository"):
            for item in outer_instance.items:
                if self.condition(item):
                    return item

    class get_items(Command):
        """
        Gets an item from the list.
        :param condition: A condition function.
        :return items: A list of items that meet the condition.
        """
        def __init__(self, condition=lambda item: True):
            self.condition = condition

        @property
        def undo_enabled(self):
            return False

        def execute(self, outer_instance: "Repository"):
            found_items = []
            for item in outer_instance.items:
                if self.condition(item):
                    found_items.append(item)

            return found_items

    class add_item(Command):
        """
        Adds an item to the list.
        :param item: The item to add.
        :return:
        """
        def __init__(self, item):
            self.item = item

        def undo_enabled(self):
            return True

        def execute(self, outer_instance: "Repository"):
            outer_instance.items.append(self.item)

        def undo(self, outer_instance: "Repository"):
            outer_instance.items.remove(self.item)

    class remove_item(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self, condition):
            self.condition = condition
            self.removed_item = (0, None)

        def undo_enabled(self):
            return True

        def execute(self, outer_instance: "Repository"):
            items_copy = outer_instance.items.copy()

            for i, item in enumerate(items_copy):
                if self.condition(item):
                    self.removed_item = (i, item)
                    outer_instance.items.remove(item)
                    break

        def undo(self, outer_instance: "Repository"):
            outer_instance.items.insert(self.removed_item[0], self.removed_item[1])

    class remove_items(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self, condition):
            self.condition = condition
            self.removed_items = {}

        def undo_enabled(self):
            return True

        def execute(self, outer_instance: "Repository"):
            items_copy = outer_instance.items.copy()

            for i, item in enumerate(items_copy):
                if self.condition(item):
                    self.removed_items[i] = item
                    outer_instance.items.remove(item)

        def undo(self, outer_instance: "Repository"):
            for i, item in self.removed_items.items():
                outer_instance.items.insert(i, item)

    class clear_items(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self):
            self.removed_items = []

        def undo_enabled(self):
            return True

        def execute(self, outer_instance: "Repository"):
            items_copy = outer_instance.items.copy()

            for item in items_copy:
                self.removed_items.append(item)
                outer_instance.items.remove(item)

        def undo(self, outer_instance: "Repository"):
            outer_instance.items += self.removed_items

    class replace_item(Command):
        """
        Removes an item from the list.
        :param condition: A condition function.
        :return:
        """
        def __init__(self, condition, new_item):
            self.condition = condition
            self.new_item = new_item
            self.old_item = None
            self.replaced_id = 0

        def undo_enabled(self):
            return True

        def execute(self, outer_instance: "Repository"):
            for i, item in enumerate(outer_instance.items):
                if self.condition(item):
                    self.replaced_id = i
                    self.old_item = outer_instance.items[i]
                    outer_instance.items[i] = self.new_item
                    break

        def undo(self, outer_instance: "Repository"):
            outer_instance.items[self.replaced_id] = self.old_item
