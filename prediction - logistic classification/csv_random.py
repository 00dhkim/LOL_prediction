import numpy as np
import random

data = np.loadtxt("GameData-adidasu.csv", delimiter=',', dtype=int)

for i in range(len(data)):
    if random.randint(0,1):
        data[i][0],data[i][1] = data[i][1],data[i][0]
        data[i][2],data[i][3] = data[i][3],data[i][2]
        data[i][4],data[i][5] = data[i][5],data[i][4]
        data[i][6],data[i][7] = data[i][7],data[i][6]
        data[i][8],data[i][9] = data[i][9],data[i][8]
        data[i][10],data[i][11] = data[i][11],data[i][10]
        data[i][12] = 0
            
np.savetxt("GameData-adidasu-random.csv", data, delimiter=',', fmt='%d')
