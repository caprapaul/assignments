from repositories.repository import Repository
import ast


class RepositoryText(Repository):
    def load_data(self, **kwargs):
        """
        Load repository from txt file.
        :param kwargs:
        file - file to load the data from
        type - the type of the objects
        :return:
        """
        type = kwargs['type']
        file = kwargs['file']
        with open(file, 'r') as data_file:
            for line in data_file:
                line = line[:-1]
                items_dict = ast.literal_eval(line)

                item = type.from_dict(items_dict)

                self.add_item(item, lambda i: i.uid)

    def save_data(self, **kwargs):
        """
        Save repository to txt file.
        :param kwargs:
        file - file to load the data from
        :return:
        """

        file = kwargs['file']
        with open(file, 'w') as data_file:
            for item in self._items.values():
                data_string = '{'
                item_dict = item.to_dict()

                for key, value in item_dict.items():
                    data_string += f'"{key}":"{value}",'

                data_string = data_string[:-1]
                data_string += '}\n'
                data_file.write(data_string)

