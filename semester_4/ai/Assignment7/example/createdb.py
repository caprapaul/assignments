import torch
import numpy as np

max_ = 10
min_ = -10
size = 1000

x = (max_ - min_) * torch.rand((size, 2)) + min_
x_0 = torch.tensor([x_[0] for x_ in x])
x_1 = torch.tensor([x_[1] for x_ in x])
y = torch.sin(x_0 + x_1 / np.pi)
pairs = torch.column_stack((x, y))

print(x)
print(y)
print(pairs)

torch.save(pairs, 'mydataset.dat')
