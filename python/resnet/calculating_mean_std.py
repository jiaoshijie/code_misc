from data_loader import load_annos
import os
from PIL import Image
from torchvision.transforms import transforms
from tqdm import tqdm


def calculating_mean(imgdir, img_annos_path, resize, transform):
    annos = load_annos(img_annos_path)
    mean_sum = {0: 0, 1: 0, 2: 0}  # R: 0, G: 1, B: 2
    for i in tqdm(annos):
        img = Image.open(os.path.join(imgdir, i['fname']))
        img = img.convert('RGB')
        img = resize(img)
        img = transform(img)
        for j in range(len(img)):
            mean_sum[j] += img[j].mean()

    for i in range(3):
        mean_sum[i] = mean_sum[i] / len(annos)

    print(mean_sum)


# train: {0: tensor(0.4708), 1: tensor(0.4602), 2: tensor(0.4550)}
def calculating_std(imgdir, img_annos_path, resize, transform, mean):
    annos = load_annos(img_annos_path)
    std = {0: 0, 1: 0, 2: 0}  # R: 0, G: 1, B: 2
    pixels = 0
    for i in tqdm(annos):
        img = Image.open(os.path.join(imgdir, i['fname']))
        img = img.convert('RGB')
        img = resize(img)
        img = transform(img)
        pixels += img.shape[1] * img.shape[2]
        for j in range(len(img)):
            std[j] += ((img[j] - mean[j]) ** 2).sum()

    for i in range(3):
        std[i] = (std[i] / pixels) ** 0.5

    print(std)
# {0: tensor(0.2926), 1: tensor(0.2916), 2: tensor(0.3001)}


if __name__ == '__main__':
    # calculating_mean(
    #                 './cars_train', './devkit/cars_train_annos.mat',
    #                 transforms.Resize(400), transforms.ToTensor())

    calculating_std(
            './cars_train', './devkit/cars_train_annos.mat',
            transforms.Resize(400), transforms.ToTensor(),
            {0: 0.4708, 1: 0.4602, 2: 0.4550})
