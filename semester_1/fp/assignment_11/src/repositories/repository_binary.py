from repositories.repository import Repository
import pickle


class RepositoryBinary(Repository):
    def load_data(self, **kwargs):
        """
        Load repository from pickle file.
        :param kwargs:
        file - file to load the data from
        :return:
        """
        file = kwargs['file']
        with open(file, 'rb') as data_file:
            first_char = data_file.read(1)

            if not first_char:
                return

            data_file.seek(0)

            self._items = pickle.load(data_file)

    def save_data(self, **kwargs):
        """
        Save repository to pickle file.
        :param kwargs:
        file - file to load the data from
        :return:
        """
        file = kwargs['file']
        with open(file, 'wb') as data_file:
            pickle.dump(self._items, data_file)
