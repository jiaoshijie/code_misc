import matplotlib.pyplot as plt
# from scipy.fftpack import fft, ifft
# import math
# import random as r


def draw(x=[1, 2, 3], y1=[1, 2, 3], y2=[1, 2, 3]):
    plt.figure(1)
    ax1 = plt.subplot(1, 2, 1)
    ax2 = plt.subplot(1, 2, 2)
    plt.sca(ax1)
    plt.plot(x, y1)
    plt.sca(ax2)
    plt.plot(x, y2)
    plt.show()


# def example1():
#     x1 = [1, 1, 1, 1, 1]
#     x2 = [1, 1, 1, 1]

#     xx1 = ifft(x1, 8)
#     xx2 = ifft(x2, 8)

#     xx3 = xx1 * xx2

#     y3 = fft(xx3, 8) * 8
#     print(y3)


# def example2():
#     x1 = [i * 2 * math.pi / 1000 for i in range(1000)]
#     y1 = [2 * math.cos(2 * i) + 3 * math.sin(4 * i) +
#           r.random() * 0.3 for i in x1]

#     # draw(x1, y1)

#     xx1 = fft(y1, 1024)
#     xx1[5:1000 - 30] = 0
#     yy1 = ifft(xx1, 1024)

#     # draw(x1, yy1[0:1000])

#     plt.figure(1)
#     ax1 = plt.subplot(1, 2, 1)
#     ax2 = plt.subplot(1, 2, 2)
#     plt.sca(ax1)
#     plt.plot(x1, y1)
#     plt.sca(ax2)
#     plt.plot(x1, yy1[0:1000])
#     plt.show()
