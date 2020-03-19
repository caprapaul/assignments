from repositories.repository import Repository
import json


class RepositoryJSON(Repository):
    def load_data(self, **kwargs):
        """
        Load repository from json file.
        :param kwargs:
        file - file to load the data from
        type - the type of the objects
        :return:
        """
        file = kwargs['file']
        type = kwargs['type']
        with open(file, 'r') as data_file:
            first_char = data_file.read(1)

            if not first_char:
                return

            data_file.seek(0)

            data_dict = json.load(data_file)

            for key, item in data_dict.items():
                self._items[key] = type.from_dict(item)

    def save_data(self, **kwargs):
        """
        Save repository to json file.
        :param kwargs:
        file - file to load the data from
        :return:
        """

        file = kwargs['file']
        with open(file, 'w') as data_file:
            data_dict = {}

            for key, item in self._items.items():
                data_dict[key] = item.to_dict()

            json.dump(data_dict, data_file)
