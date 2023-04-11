import numpy as np
import matplotlib.pyplot as plt

f = open("time.txt", "r")
x = []
y1 = []
y2 = []
for line in f:
    val = line.split()
    x.append(val[0])
    y1.append(val[1])
    y2.append(val[2])

plt.plot(x, y1, color="red")
plt.plot(x, y2, color="blue")
plt.xlabel("Number of points in polygon")
plt.ylabel("Time")
plt.show()
f.close()