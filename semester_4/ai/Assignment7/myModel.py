# -*- coding: utf-8 -*-

import torch
import torch.nn.functional as F


class Net(torch.nn.Module):
    # the class for the network

    def __init__(self, n_input, n_hidden, n_output, hidden_layers=1):
        super(Net, self).__init__()
        modules = []
        modules.append(torch.nn.Linear(n_input, n_hidden))

        for _ in range(hidden_layers - 1):
            modules.append(torch.nn.ReLU())
            modules.append(torch.nn.Linear(n_hidden, n_hidden))

        modules.append(torch.nn.ReLU())
        modules.append(torch.nn.Linear(n_hidden, n_output))

        self.output = torch.nn.Sequential(*modules)

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the refu function applied on the output of the hidden layer
        x = self.output(x)
        return x
