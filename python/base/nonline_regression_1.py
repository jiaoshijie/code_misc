import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# 生成数据
x_data = np.linspace(-0.5, 0.5, 200)[:, np.newaxis]
noise = np.random.normal(0, 0.02, x_data.shape)
y_data = np.square(x_data) + noise

# 定义x和y的空间
x = tf.placeholder(tf.float32, [None, 1])
y = tf.placeholder(tf.float32, [None, 1])

# 定义中间层， 有10个神经元
theta_L1 = tf.Variable(tf.random.normal([1, 10]))
biases_L1 = tf.Variable(tf.zeros([1, 10]))
Wx_plus_b_L1 = tf.matmul(x, theta_L1) + biases_L1
L1 = tf.nn.tanh(Wx_plus_b_L1)

# 定义输出层
theta_L2 = tf.Variable(tf.random.normal([10, 1]))
biases_L2 = tf.Variable(tf.zeros([1, 1]))
Wx_plus_b_L2 = tf.matmul(L1, theta_L2) + biases_L2
prediction = tf.nn.tanh(Wx_plus_b_L2)

# 定义代价函数
loss = tf.reduce_mean(tf.square(y - prediction))
# 使用梯度下降算法进行数据计算
train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

with tf.Session() as sess:
    # 变量初始化
    sess.run(tf.global_variables_initializer())
    for _ in range(200):
        print(sess.run(loss, feed_dict={x: x_data, y: y_data}))
        sess.run(train_step, feed_dict={x: x_data, y: y_data})

    # 获得预测值
    prediction_value = sess.run(prediction, feed_dict={x: x_data})

    # 画图
    plt.figure()
    plt.scatter(x_data, y_data)
    plt.plot(x_data, prediction_value, "r-", lw=2)
    plt.show()
