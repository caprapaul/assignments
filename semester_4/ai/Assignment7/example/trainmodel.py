
import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np

import myModel

device = 'cpu' if torch.cuda.is_available() else 'cpu'
print('Using {} device'.format(device))

pairs = torch.load('mydataset.dat')

x = torch.empty(2).to(device)
y = torch.empty(1).to(device)

for pair in pairs:
    x_ = torch.tensor([pair[0], pair[1]]).to(device)
    x = torch.vstack((x, x_))
    y = torch.vstack((y, pair[2].to(device)))


print(x.size())

# we set up the lossFunction as the mean square error
loss_fn = torch.nn.MSELoss()

# we create the ANN
ann = myModel.Net(n_feature=2, n_hidden=10,
                  n_output=1, device=device).to(device)

print(ann)
# we use an optimizer that implements stochastic gradient descent
optimizer = torch.optim.SGD(ann.parameters(), lr=1e-4)

# we memorize the losses forsome graphics
loss_list = []
avg_loss_list = []

# we set up the environment for training in batches
epochs = 2000
batch_size = 256
n_batches = int(len(x) / batch_size)
print(n_batches)

for epoch in range(epochs):
    for batch in range(n_batches):
        # we prepare the current batch  -- please observe the slicing for tensors
        batch_X, batch_y = x[batch * batch_size:(
            batch + 1) * batch_size, ], y[batch*batch_size:(batch+1)*batch_size, ]

        # we compute the output for this batch
        prediction = ann(batch_X)

        # we compute the loss for this batch
        loss = loss_fn(prediction, batch_y)

        # we save it for graphics
        loss_list.append(loss)

        # we set up the gradients for the weights to zero (important in pytorch)
        optimizer.zero_grad()

        # we compute automatically the variation for each weight (and bias) of the network
        loss.backward()

        # we compute the new values for the weights
        optimizer.step()

    # we print the loss for all the dataset for each 10th epoch
    if epoch % 100 == 99:
        y_pred = ann(x)
        loss = loss_fn(y_pred, y)
        print('\repoch: {}\tLoss =  {:.5f}'.format(epoch, loss.item()))

# Specify a path
filepath = "myNetwork.pt"

# save the model to file
torch.save(ann.state_dict(), filepath)

# visualise the parameters for the ann (aka weights and biases)
for name, param in ann.named_parameters():
    if param.requires_grad:
        print(name, param.data)

loss_list = [l.item() for l in loss_list]

plt.plot(loss_list)
plt.title('Loss VS Epoch')
plt.xlabel('#Epoch')
plt.ylabel('Loss')
plt.show()
