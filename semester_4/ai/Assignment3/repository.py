# -*- coding: utf-8 -*-

import pickle
from domain import *


class Repository():
    def __init__(self):
        self.__populations = []
        self.mapp = Map()

    @property
    def populations(self):
        return self.__populations

    def add_population(self, population):
        self.__populations.append(population)

    def save_map(self, file_name):
        with open(file_name, 'wb') as f:
            pickle.dump(self.mapp, f)
            f.close()

    def load_map(self, file_name):
        with open(file_name, 'rb') as f:
            dummy = pickle.load(f)
            self.mapp = dummy
            f.close()
