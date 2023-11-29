import math

import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt


rows = []
with open('C:/Users/vladimir/Desktop/vladimir/HSE/2 курс/аисд/contest/output.csv') as f:
    for line in f:
        line = line.strip()
        line = line.split(';')
        line = line[:3]
        rows.append(line)
# print(rows)
for i in range(len(rows)):
    a = 0
    b = abs(float(rows[i][0])) - math.pi
    a = b
    # b = abs(float(rows[i][2]))  # for second graphic
    # if b < 0.5:
    #     a = 0.5
    # elif b < 1:
    #     a = 1
    # elif b < 1.5:
    #     a = 1.5
    # elif b < 2:
    #     a = 2
    # elif b < 2.5:
    #     a = 2.5
    # elif b < 3:
    #     a = 3
    # elif b < 3.5:
    #     a = 3.5
    # elif b < 4:
    #     a = 4
    # elif b < 4.5:
    #     a = 4.5
    # else:
    #     a = 5
    plt.scatter(rows[i][0], a)

plt.show()

