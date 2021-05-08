# -*- coding: utf-8 -*-

import torch
import torch.nn.functional as F


class Net(torch.nn.Module):
    # the class for the network

    def __init__(self, n_feature, n_hidden, n_output, device):
        # we have two layers: a hidden one and an output one
        super(Net, self).__init__()
        self.hidden = torch.nn.Linear(n_feature, n_hidden).to(device)
        self.output = torch.nn.Sequential(
            torch.nn.Linear(n_feature, n_hidden).to(device),
            torch.nn.ReLU().to(device),
            torch.nn.Linear(n_hidden, n_hidden).to(device),
            torch.nn.ReLU().to(device),
            torch.nn.Linear(n_hidden, n_output).to(device)
        )

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the refu function applied on the output of the hidden layer
        #x = F.relu(self.hidden(x))
        x = self.output(x)
        return x