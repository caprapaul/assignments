import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np
import math

import myModel
from constants import *


def main():
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    print('Using {} device'.format(device))

    pairs = torch.load('mydataset1.dat')
    # print(pairs)

    x = torch.empty(0, 2).to(device)
    y = torch.empty(0, 1).to(device)

    for pair in pairs:
        x_ = torch.tensor([pair[0], pair[1]]).to(device)
        x = torch.vstack((x, x_))
        y = torch.vstack((y, pair[2].to(device)))

    # print(y)
    # return

    # we set up the lossFunction as the mean square error
    loss_fn = torch.nn.MSELoss()

    # we create the ANN
    ann = myModel.Net(N_INPUT, N_HIDDEN, N_OUTPUT, HIDDEN_LAYERS).to(device)

    # print(ann)
    # we use an optimizer that implements stochastic gradient descent
    optimizer = torch.optim.SGD(ann.parameters(), lr=LEARNING_RATE)

    # we memorize the losses forsome graphics
    loss_list = []
    avg_loss_list = []

    # we set up the environment for training in batches
    batch_size = BATCH_SIZE
    n_batches = int(math.ceil(len(x) / batch_size))
    print(n_batches)

    for epoch in range(EPOCHS):
        for batch in range(n_batches):
            # we prepare the current batch  -- please observe the slicing for tensors
            batch_X, batch_y = x[batch * batch_size:(
                batch + 1) * batch_size, ], y[batch * batch_size:(batch + 1) * batch_size, ]

            # we compute the output for this batch
            prediction = ann(batch_X)

            # we compute the loss for this batch
            loss = loss_fn(prediction, batch_y)

            # we save it for graphics
            loss_list.append(loss.item())

            # we set up the gradients for the weights to zero (important in pytorch)
            optimizer.zero_grad()

            # we compute automatically the variation for each weight (and bias) of the network
            loss.backward()

            # we compute the new values for the weights
            optimizer.step()

        # we print the loss for all the dataset for each 10th epoch
        if (epoch + 1) % 500 == 0:
            y_pred = ann(x)
            loss = loss_fn(y_pred, y)
            print('\repoch: {}\tLoss =  {:.5f}'.format(epoch, loss.item()))

        avg_loss_list.append(sum(loss_list) / len(loss_list))
        loss_list.clear()

    # save the model to file
    torch.save(ann.state_dict(), CURRENT_NETWORK_PATH)

    # visualise the parameters for the ann (aka weights and biases)
    # for name, param in ann.named_parameters():
    #     if param.requires_grad:
    #         print(name, param.data)

    # loss_list = [l.item() for l in loss_list]

    plt.plot(avg_loss_list)
    plt.title('Loss VS Epoch')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.show()


main()
