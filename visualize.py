import matplotlib.pyplot as plt 

fig, (p1, p2) = plt.subplots(1, 2, sharey = True)
fig.set_figheight(5)
fig.set_figwidth(15)
fig.suptitle("Polygon Decomposition")

f = open("input.txt", "r")
n = int(f.readline())
polygon = []
for i in range(n):
    polygon.append([float(x) for x in f.readline().split()])
f.close()

x = []
y = []
for i in range(len(polygon)):
    x.append(polygon[i][0])
    y.append(polygon[i][1])
    p1.text(polygon[i][0], polygon[i][1], str(i+1), fontsize=10)
    p2.text(polygon[i][0], polygon[i][1], str(i+1), fontsize=10)
x.append(polygon[0][0])
y.append(polygon[0][1])
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

print("Total ploygons after decomposition: ", str(len(polygons)))
plt.show()