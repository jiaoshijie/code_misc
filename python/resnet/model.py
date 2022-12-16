import torch.nn as nn
import torchvision


class NetWork(nn.Module):
    def __init__(self, base, num_classes):
        super().__init__()
        self.base = base
        in_features = self.base.fc.in_features
        self.base.fc = nn.Linear(in_features, num_classes)

    def forward(self, x):
        fc = self.base(x)
        return fc


def get_model(num_classes, arch='resnet34'):
    if arch == 'resnet34':
        base = torchvision.models.resnet34(pretrained=True)
    else:
        base = torchvision.models.resnet18(pretrained=True)
    model = NetWork(base, num_classes)

    return model
