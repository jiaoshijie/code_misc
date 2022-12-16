from scipy.io import loadmat
import numpy as np
import os
from torchvision import transforms
from torch.utils.data import DataLoader
from PIL import Image


def load_class_names(path='./devkit/cars_meta.mat'):
    mat_meta = loadmat(path)
    class_names = np.array([i[0] for i in mat_meta['class_names'][0]])
    return class_names


def load_annos(path='./devkit/cars_train_annos.mat'):
    mat_info = loadmat(path)
    annos = np.array(
            [{"x1": i[0][0][0], "y1": i[1][0][0], "x2": i[2][0][0],
                "y2": i[3][0][0], "class": i[4][0][0] - 1,
                "fname": i[5][0]} for i in mat_info['annotations'][0]])
    return annos


# DataSet loader
class LoadDataset:
    def __init__(self, imgdir, annos_path, transform, size):
        self.imgdir = imgdir
        self.annos = load_annos(annos_path)
        self.transform = transform
        self.resize = transforms.Resize(size)
        self.cache = {}

    def __len__(self):
        return len(self.annos)

    def __getitem__(self, idx):
        temp = self.annos[idx]
        target = temp['class']

        if idx not in self.cache:
            img = Image.open(os.path.join(self.imgdir, temp['fname']))
            img = img.convert('RGB')
            img = img.crop((temp['x1'], temp['y1'], temp['x2'], temp['y2']))
            img = self.resize(img)
            self.cache[idx] = img
        else:
            img = self.cache[idx]

        img = self.transform(img)  # to Tensor

        return img, target


def prepareTrainData(train_imgdir, train_annos_path, size):
    train_transform = transforms.Compose([
        transforms.RandomHorizontalFlip(),
        transforms.RandomRotation(15),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.4708, 0.4602, 0.4550],
                             std=[0.2926, 0.2916, 0.3001])
        # transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
        ])

    train_CarDataSet = LoadDataset(
            train_imgdir, train_annos_path, train_transform, size)

    train_loader = DataLoader(
            train_CarDataSet, batch_size=12, num_workers=4, shuffle=True,
            pin_memory=True
            )

    return train_loader


def prepareTestData(test_imgdir, test_annos_path, size):
    test_transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.4708, 0.4602, 0.4550],
                             std=[0.2926, 0.2916, 0.3001])
        # transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
        ])
    test_CarDataSet = LoadDataset(
            test_imgdir, test_annos_path, test_transform, size)

    test_loader = DataLoader(
            test_CarDataSet, batch_size=12, num_workers=4, shuffle=False,
            pin_memory=True
            )

    return test_loader


if __name__ == '__main__':
    pass
