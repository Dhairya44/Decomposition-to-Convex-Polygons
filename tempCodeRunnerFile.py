f = open("output.txt", "r")
# n = int(f.readline())
# polygons = []
# for i in range(n):
#     p = int(f.readline())
#     polygon = []
#     for j in range(p):
#         polygon.append([float(x) for x in f.readline().split()])
#     polygons.append(polygon)

# for polygon in polygons:
#     x = []
#     y = []
#     for i in range(len(polygon)):
#         x.append(polygon[i][0])
#         y.append(polygon[i][1])
#     x.append(polygon[0][0])
#     y.append(polygon[0][1])
#     p2.plot(x,y)
# # p2.legend([i+1 for i in range(len(polygons))])
# s = "Convex Polygons: " + str(len(polygons))
# p2.title.set_text(s)

# n = int(f.readline())
# polygons = []
# for i in range(n):
#     p = int(f.readline())
#     polygon = []
#     for j in range(p):
#         polygon.append([float(x) for x in f.readline().split()])
#     polygons.append(polygon)

# for polygon in polygons:
#     x = []
#     y = []
#     for i in range(len(polygon)):
#         x.append(polygon[i][0])
#         y.append(polygon[i][1])
#     x.append(polygon[0][0])
#     y.append(polygon[0][1])
#     p3.plot(x,y)
# s = "Convex Polygons after Merging: " + str(len(polygons))
# p3.title.set_text(s)