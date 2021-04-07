# -*- coding: utf-8 -*-

import pickle
from domain import *


class Repository:
    def __init__(self):
        self.mapp = Map()
        self.sensors = {}

    def random_sensors(self, count, power):
        positions = self.mapp.get_empty_positions(count)

        for pos in positions:
            sensor = Sensor(pos, power)
            self.sensors[pos] = sensor

    def save_map(self, file_name):
        with open(file_name, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def load_map(self, file_name):
        with open(file_name, 'rb') as f:
            dummy = pickle.load(f)
            self.mapp = dummy.mapp
            self.sensors = dummy.sensors
            f.close()
