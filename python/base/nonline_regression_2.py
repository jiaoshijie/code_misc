import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# 初始化数据
x_data = np.linspace(-1, 1, 200)[:, np.newaxis]
noise = np.random.normal(0, 0.02, x_data.shape)  # 数据干扰项
y_data = np.square(x_data) + noise

# 定义x和y的placeholder
x = tf.placeholder(tf.float32, [None, 1])
y = tf.placeholder(tf.float32, [None, 1])

# 定义中间层， 10层
theta_L1 = tf.Variable(tf.random.normal([1, 10]))
biases_L1 = tf.Variable(tf.zeros([1, 10]))
theta_plus_b_L1 = tf.matmul(x, theta_L1) + biases_L1
# 中间层的输出
L1 = tf.nn.tanh(theta_plus_b_L1)

# 定义输出层
theta_L2 = tf.Variable(tf.random.normal([10, 1]))
biases_L2 = tf.Variable(tf.zeros([1, 1]))
theta_plus_b_L2 = tf.matmul(L1, theta_L2) + biases_L2
# 预测值
prediction = tf.nn.tanh(theta_plus_b_L2) + biases_L2

# 定义代价函数
loss = tf.reduce_mean(tf.square(y - prediction))  # 这一步是什么意思？？？
# 使用梯度下降算法进行计算
train_run = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

# 定义Session运行程序
with tf.Session() as sess:
    # 初始化变量
    sess.run(tf.global_variables_initializer())
    for _ in range(2000):
        sess.run(train_run, feed_dict={x: x_data, y: y_data})

    # 获取训练数据
    prediction_value = sess.run(prediction, feed_dict={x: x_data})

    # 开始画图
    plt.figure()
    plt.scatter(x_data, y_data)
    plt.plot(x_data, prediction_value, 'r-', lw=5)
    plt.show()
