import math

import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt


rows = []
with open('output_A3.csv') as f:
    for line in f:
        line = line.strip()
        line = line.split(';')
        line = line[:6]
        rows.append(line)
# print(rows)
for i in range(len(rows)):
    plt.scatter(rows[i][0], rows[i][2])
plt.show()
for i in range(len(rows)):
    plt.scatter(rows[i][3], rows[i][4])
plt.show()
for i in range(len(rows)):
    plt.scatter(rows[i][4], rows[i][5])
plt.show()

