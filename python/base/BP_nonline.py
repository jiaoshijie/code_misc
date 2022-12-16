import numpy as np
import matplotlib.pyplot as plt

x_data = np.mat(np.linspace(-0.4, 0.4, 200).tolist())
noise = np.mat(np.random.normal(0, 0.01, x_data.shape))
y_data = np.square(x_data) + noise
# y_data = 2 * x_data + noises
# y_data = np.power(x_data, 3) + noise
# print(x_data.shape)

# 归一化
# ......


# 定义激励函数
def logsig(x):
    # @x 矩阵
    # return 1 / (1 + np.exp(-x))  # [0, 1]
    return (np.exp(x) - np.exp(-x)) / (np.exp(x) + np.exp(-x))  # [-1, 1]


# 数据初始化
errhistory = []  # 记录误差
learnrate = 0.1  # 学习速率
errorfinal = 0.35 * 10**(-3)  # 最终迭代误差

# 生成网络权值和baises
Weight_L1 = np.random.rand(3, 1)  # 3x1
baises_L1 = np.random.rand(3, 1)  # 3x1
Weight_L2 = np.random.rand(1, 3)  # 1x1
baises_L2 = np.random.rand(1, 1)  # 1x1

# 开始进行学习(3个神经元)
for i in range(60000):  # 进行200次循环
    # 进行前向传播
    L1 = logsig(np.dot(Weight_L1, x_data) + baises_L1)
    L2 = logsig(np.dot(Weight_L2, L1) + baises_L2)
    L2_y = L2 - y_data
    err = np.sum(np.square(L2_y)) / (np.size(L2_y))
    # err = np.sum(np.square(L2_y)) / (2 * np.size(L2_y))
    # err = np.sum(np.square(L2_y)) / 200

    errhistory.append(err)
    # 到达一定误差退出循环
    # if err < errorfinal:
    #     break
    if i % 10 == 0:
        print("L2_y = ", np.size(L2_y))
    # 进行反向传播
    dalta3 = L2_y
    # dalta2 = L1 * np.dot(Weight_L2.transpose(), dalta3).T * (1 - L1)
    dalta2 = np.multiply(np.dot(Weight_L2.transpose(), dalta3), np.multiply(
        L1, (1 - L1)))

    d_dalta3 = 1 / np.size(L1, axis=1) * np.dot(dalta3, L1.T)
    d_baises3 = 1 / np.size(L1, axis=1) * np.sum(dalta3, axis=1)

    d_dalta2 = 1 / np.size(x_data, axis=1) * np.dot(dalta2, x_data.T)
    d_baises2 = 1 / np.size(x_data, axis=1) * np.sum(dalta2, axis=1)
    # 更新权值和baises的值
    Weight_L2 -= learnrate * d_dalta3
    baises_L2 -= learnrate * d_baises3

    Weight_L1 -= learnrate * d_dalta2
    baises_L1 -= learnrate * d_baises2

# print(L2 * 100)
# print(y_data * 100)
plt.figure()
plt.scatter(x_data.tolist(), y_data.tolist())
plt.scatter(x_data.tolist(), L2.tolist())
plt.show()
