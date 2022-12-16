from PIL import Image
import numpy as np


# imgPath: ./cars_test/00001.jpg  width=276 height=182
def loadimg(path, mothed: str = 'L'):
    img = Image.open(path)
    img = img.convert(mothed)  # RGB or L(for grey img)
    return img


def convertImgToNumpy(img):
    np_img = np.array(img)
    return np_img


def displayNumpyImage(img):
    Image.fromarray(np.uint8(img)).show()


def convolution2D(img, K, step=1):
    res = np.zeros(
            ((img.shape[0] - K.shape[0]) // step + 1,
             (img.shape[1] - K.shape[1]) // step + 1))
    for i in range(res.shape[0]):
        for j in range(res.shape[1]):
            res[i][j] = (img[i:i+3, j:j+3] * K).sum()

    return res


def convolution3D(img, K, step=1):
    img = img.T
    res = np.zeros(
            (3, (img.shape[1] - K.shape[0]) // step + 1,
             (img.shape[2] - K.shape[0]) // step + 1))
    for c in range(res.shape[0]):
        for i in range(res.shape[1]):
            for j in range(res.shape[2]):
                res[c][i][j] = (img[c][i:i+3, j:j+3] * K).sum()
    # print(res.shape)
    return res.T


def grey_convolution_run():
    img = loadimg('./cars_test/00005.jpg')
    np_img = convertImgToNumpy(img)
    kernel = np.array(
            [[-1, -1, -1],
             [-1, 2, -1],
             [-1, -1, -1]])
    res = convolution2D(np_img, kernel, 1)
    displayNumpyImage(res)


def ture_color_convolution_run():
    img = loadimg('./cars_test/00002.jpg', 'RGB')
    img.show()
    np_img = convertImgToNumpy(img)
    kernel = np.array(
            [[0, -1, 0],
             [-1, 0, -1],
             [0, -1, 0]])
    # kernel = (1 / 16) * np.array(
    #         [[1, 2, 1],
    #          [2, 0, 2],
    #          [1, 2, 1]])
    res = convolution3D(np_img, kernel, 1)
    displayNumpyImage(res)


def split():
    img = loadimg('./cars_test/00001.jpg')
    img = img.crop((100, 120, 30, 50))
    img.show()


if __name__ == '__main__':
    ture_color_convolution_run()
