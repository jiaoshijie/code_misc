import matplotlib.pyplot as plt
import csv
# import numpy as np


def plot_trend(epochs, train_acc, loss, test_acc):
    eps = [i + 1 for i in range(epochs)]
    plt.figure(1)
    ax1 = plt.subplot(1, 2, 1)
    ax2 = plt.subplot(1, 2, 2)
    # draw loss
    plt.sca(ax1)
    plt.plot(eps, loss, marker='v', label="loss")
    plt.xlabel('epochs')
    plt.legend()
    # draw train acc and test acc
    plt.sca(ax2)
    plt.plot(eps, train_acc, marker='o', label="train acc")
    plt.plot(eps, test_acc, marker='v', label="vaild acc")
    plt.xlabel('epochs')
    plt.legend()

    plt.show()


def writeToCSV(filename, res, epochs):
    header = ['epoch', 'train acc', 'loss', 'test acc']
    data = [[i + 1, res['train_acc'][i], res['loss'][i],
            res['test_acc'][i]] for i in range(epochs)]
    with open(filename, 'w') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        for i in data:
            writer.writerow(i)


def plot_trendfromcsv(filename):
    count = 0
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        res = {'train_acc': [], 'loss': [], 'test_acc': []}
        for count, row in enumerate(reader):
            if count != 0:
                res['train_acc'].append(float(row[1]))
                res['loss'].append(float(row[2]))
                res['test_acc'].append(float(row[3]))

    plot_trend(count, **res)


def get_parameter_number(net):
    total_num = sum(p.numel() for p in net.parameters())
    trainable_num = sum(p.numel() for p in net.parameters() if p.requires_grad)
    return {'Total': total_num, 'Trainable': trainable_num}


if __name__ == '__main__':
    plot_trendfromcsv('./18_400res.csv')
