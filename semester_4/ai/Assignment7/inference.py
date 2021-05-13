# -*- coding: utf-8 -*-
"""
Created on Tue Apr 27 14:20:51 2021

@author: tudor
"""

import torch
import torch.nn.functional as F
import numpy as np

from myModel import Net
from constants import *

device = 'cuda' if torch.cuda.is_available() else 'cpu'
print('Using {} device'.format(device))

# we load the model

ann = Net(N_INPUT, N_HIDDEN, N_OUTPUT, HIDDEN_LAYERS).to(device)

ann.load_state_dict(torch.load(CURRENT_NETWORK_PATH))
ann.eval()


# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print (name, param.data)

input_ = input("x1, x2 = ")

while input_.upper() != 'EXIT':
    x1, x2 = input_.split(',')
    x1 = float(x1)
    x2 = float(x2)
    x = torch.tensor([x1, x2]).to(device)
    predicted = ann(x).item()
    correct = np.sin(x1 + x2 / np.pi)
    print(f'predicted: {predicted}')
    print(f'correct: {correct}')
    print(f'difference: {correct - predicted}')
    print()
    input_ = input("x1, x2 = ")
