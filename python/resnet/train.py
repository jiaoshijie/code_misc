from data_loader import prepareTrainData, prepareTestData, load_class_names
import torch
from model import get_model
import torch.optim as optimizer
from torch.nn import functional as F
from utils import writeToCSV
# from tqdm import tqdm
# import time


def main():
    device = torch.device('cuda')

    classes = load_class_names('./devkit/cars_meta.mat')

    model = get_model(len(classes))  # TODO: choose an arch(resnet18, resnet34)
    model = model.to(device)

    train_data = prepareTrainData(
            './cars_train', './devkit/cars_train_annos.mat', (400, 400))
    test_data = prepareTestData(
            './cars_test', './devkit/cars_test_annos.mat', (400, 400))
    best_acc = 0
    optim = optimizer.SGD(model.parameters(), lr=0.01, momentum=0.9)
    lr_scheduler = optimizer.lr_scheduler.MultiStepLR(optim, [5, 10])
    res = {'train_acc': [], 'loss': [], 'test_acc': []}
    for epoch in range(21):
        # train
        train_sum = 0
        train_total_num = 0
        model.train()
        for input, target in train_data:
            input = input.to(device)
            target = target.to(device)
            # 1.
            optim.zero_grad()
            # 2.
            pred = model(input)
            train_sum += pred.max(1)[1].eq(target).float().sum()
            train_total_num += len(target)
            # 3.
            loss = F.cross_entropy(pred, target)
            loss.backward()
            optim.step()

        lr_scheduler.step()

        res['train_acc'].append((train_sum / train_total_num).type(
            torch.float32).cpu().detach().numpy())
        res['loss'].append(loss.type(torch.float32).cpu().detach().numpy())

        # vaild
        test_sum = 0
        test_total_num = 0
        for input, target in test_data:
            input = input.to(device)
            target = target.to(device)
            pred = model(input)
            test_sum += pred.max(1)[1].eq(target).float().sum()
            test_total_num += len(target)
        acc = test_sum / test_total_num
        res['test_acc'].append(acc.type(torch.float32).cpu().detach().numpy())
        if best_acc < acc:
            best_acc = acc
            torch.save(model.state_dict(), './best.pt')
        print(f"[{epoch + 1}] train acc: {res['train_acc'][-1]: .3f}"
              f", loss: {res['loss'][-1]: .3f}"
              f", current test acc: {res['test_acc'][-1]: .3f}"
              f", best test acc: {best_acc: .4f}.")
    writeToCSV('18_400res.csv', res, 21)


if __name__ == '__main__':
    main()
