import tensorflow.compat.v1 as tf
import numpy as np
#from sklearn.preprocessing import MinMaxScaler

def min_max_scaler(data):
    numerator = data - np.min(data, 0)
    denominator = np.max(data, 0) - np.min(data, 0)
    # noise term prevents the zero division
    return numerator / (denominator + 1e-7)

xy_data = np.loadtxt("GameData-faker.csv", delimiter=',', dtype=np.float32)
xy_data = min_max_scaler(xy_data)
x_data = xy_data[:, 0:-1]
y_data = xy_data[:, [-1]]

xy_test = np.loadtxt("GameData-faker.csv", delimiter=',', dtype=np.float32)
xy_test = min_max_scaler(xy_test)
x_test = xy_test[:, 0:-1]
y_test = xy_test[:, [-1]]

X = tf.placeholder(tf.float32, shape=[None, 12])
Y = tf.placeholder(tf.float32, shape=[None, 1])
W = tf.Variable(tf.random_normal([12,1]), name="weight")
b = tf.Variable(tf.random_normal([1]), name="bias")

hypothesis = tf.sigmoid(tf.matmul(X,W)+b)

cost = -tf.reduce_mean(Y*tf.log(hypothesis) + (1-Y)*tf.log(1-hypothesis))

train = tf.train.GradientDescentOptimizer(learning_rate=0.01).minimize(cost)

predicted = tf.cast(hypothesis > 0.5, dtype=tf.float32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(predicted, Y), dtype=tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())

    for step in range(10001):
        cost_val, _ = sess.run([cost, train], feed_dict={X: x_data, Y: y_data})

        if(step%200==0):
            print(step, cost_val)

    h,c,a = sess.run([hypothesis, predicted, accuracy], \
                     feed_dict={X: x_test, Y: y_test})

    print('hypothesis:\n',h,sep='')
    print('predicted:\n', c,sep='')
    print('accuracy:\n', a,sep='')

    print('weight:\n', sess.run(W),sep='')
    
