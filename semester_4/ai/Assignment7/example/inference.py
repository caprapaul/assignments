# -*- coding: utf-8 -*-
"""
Created on Tue Apr 27 14:20:51 2021

@author: tudor
"""

import torch
import torch.nn.functional as F
import numpy as np

from myModel import Net

device = 'cuda' if torch.cuda.is_available() else 'cpu'
print('Using {} device'.format(device))

# we load the model

filepath = "myNetwork.pt"
ann = Net(2, 10, 1, device).to(device)

ann.load_state_dict(torch.load(filepath))
ann.eval()

# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print (name, param.data)


x1, x2 = input("x1, x2 = ").split(',')
x1 = float(x1)
x2 = float(x2)
x = torch.tensor([x1, x2]).to(device)
print(ann(x).tolist())
print(f'correct: {np.sin(x1 + x2 / np.pi)}')
