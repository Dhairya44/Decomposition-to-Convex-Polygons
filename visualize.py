import matplotlib.pyplot as plt 
import numpy as np

fig, (p1, p2, p3) = plt.subplots(1, 3, sharey = True)
fig.set_figheight(5)
fig.set_figwidth(15)
fig.suptitle("Polygon Decomposition")

f = open("input.txt", "r")
m = int(f.readline())
polygon = []
for i in range(m):
    polygon.append([float(x) for x in f.readline().split()])
f.close()
# polygon.reverse()
x = []
y = []
for i in range(len(polygon)):
    x.append(polygon[i][0])
    y.append(polygon[i][1])
    # p1.text(polygon[i][0], polygon[i][1], str(i+1), fontsize=10)
    # p2.text(polygon[i][0], polygon[i][1], str(i+1), fontsize=10)
x.append(polygon[0][0])
y.append(polygon[0][1])
p1.title.set_text("Input Polygon")
p1.plot(x,y)

f = open("output.txt", "r")
n = int(f.readline())
polygons = []
for i in range(n):
    p = int(f.readline())
    polygon = []
    for j in range(p):
        polygon.append([float(x) for x in f.readline().split()])
    polygons.append(polygon)

for polygon in polygons:
    x = []
    y = []
    for i in range(len(polygon)):
        x.append(polygon[i][0])
        y.append(polygon[i][1])
    x.append(polygon[0][0])
    y.append(polygon[0][1])
    p2.plot(x,y)
# p2.legend([i+1 for i in range(len(polygons))])
s = "Convex Polygons: " + str(len(polygons))
p2.title.set_text(s)

n = int(f.readline())
polygons = []
for i in range(n):
    p = int(f.readline())
    polygon = []
    for j in range(p):
        polygon.append([float(x) for x in f.readline().split()])
    polygons.append(polygon)

for polygon in polygons:
    x = []
    y = []
    for i in range(len(polygon)):
        x.append(polygon[i][0])
        y.append(polygon[i][1])
    x.append(polygon[0][0])
    y.append(polygon[0][1])
    p3.plot(x,y)
s = "Convex Polygons after Merging: " + str(len(polygons))
p3.title.set_text(s)
# p3.legend([i+1 for i in range(len(polygons))])


t1 = f.readline()
t2 = f.readline()
s = str(m)+" "+ t1[0:-1] + " " + t2
with open("time.txt", "a") as f:
    f.write(s)

plt.show()
