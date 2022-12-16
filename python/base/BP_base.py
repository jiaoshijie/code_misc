# BP反向传播算法基础版
"""
一个简单的神经网络, 包含二个输入层, 二个输出层, 二个中间层(隐藏层)
输入层为 0.3 0.4 输出层为 0.8 0.9 初始权值和偏执值为随机值
"""
# import random
import math

# 初始化数据
input = [0.3, 0.4]  # 输入数据
output = [0.8, 0.9]  # 输出数据
W = [0.3 for i in range(8)]  # 权值
b = [0.2 for i in range(4)]  # 偏置值
learnrate = 0.1  # 学习率
errorflnal = 0.035 * 10 ** (-5)


# 激励函数
def logsig(x):
    return 1 / (1 + math.exp(-x))


def Nerves_Network(input, W, b, learnrate):
    """
    @input 输入层的数据
    @W 各个权值
    @b 各个偏执值
    @return_value ...
    """
    # 前向传播 ###
    prediction = [0, 0]
    for i in range(5000):
        # 隐藏层神经元
        L1_1 = logsig((W[0] * input[0]) + (W[2] * input[0]) + b[0])
        L1_2 = logsig((W[1] * input[1]) + (W[3] * input[1]) + b[1])

        # 输出层神经元
        prediction[0] = logsig((W[4] * L1_1) + (W[6] * L1_1) + b[2])
        prediction[1] = logsig((W[5] * L1_2) + (W[7] * L1_2) + b[3])

        # 计算代价函数 ###
        Error_value = 1 / 2 * (prediction[0] - output[0]) ** 2 + 1 / 2 * (
            prediction[1] - output[1]) ** 2
        if i % 100 == 0:
            print(i, 'W = ', W)
            print(i, 'b = ', b)
        if Error_value < errorflnal:
            break
        # 反向传播 ###
        # 输出层的各个值
        delta3_1 = prediction[0] - output[0]
        delta3_2 = prediction[1] - output[1]
        d_theta3_1 = prediction[0] * (1 - prediction[0])
        d_theta3_2 = prediction[1] * (1 - prediction[1])
        d_a3_1 = delta3_1 * d_theta3_1
        d_a3_2 = delta3_2 * d_theta3_2
        # 隐藏层的各个值
        delta2_1 = d_a3_1 * W[4] + d_a3_2 * W[5] + d_a3_1 + d_a3_2
        delta2_2 = d_a3_1 * W[6] + d_a3_2 * W[7] + d_a3_1 + d_a3_2
        d_theta2_1 = L1_1 * (1 - L1_1)
        d_theta2_2 = L1_2 * (1 - L1_2)
        d_a2_1 = delta2_1 * d_theta2_1
        d_a2_2 = delta2_2 * d_theta2_2

        # 更新数据
        W[4] -= learnrate * d_a3_1 * L1_1
        W[5] -= learnrate * d_a3_1 * L1_1
        W[6] -= learnrate * d_a3_2 * L1_2
        W[7] -= learnrate * d_a3_2 * L1_2
        W[0] -= learnrate * d_a2_1 * input[0]
        W[1] -= learnrate * d_a2_1 * input[0]
        W[2] -= learnrate * d_a2_2 * input[1]
        W[3] -= learnrate * d_a2_2 * input[1]

        b[0] -= learnrate * d_a2_1
        b[1] -= learnrate * d_a2_2
        b[2] -= learnrate * d_a3_1
        b[3] -= learnrate * d_a3_2
    return prediction


if __name__ == '__main__':
    print('\n\n\n最后的预测值为 : ', Nerves_Network(input, W, b, learnrate))
