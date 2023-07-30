import sys
from polygenerator import (
    random_polygon,
    random_star_shaped_polygon,
    random_convex_polygon,
)

# these two are only for demonstration
original_stdout = sys.stdout # Save a reference to the original standard output

import matplotlib.pyplot as plt
import random
def plot_polygon(polygon, out_file_name):
    plt.figure()
    plt.gca().set_aspect("equal")

    for i, (x, y) in enumerate(polygon):
        plt.text(x, y, str(i), horizontalalignment="center", verticalalignment="center")

    # just so that it is plotted as closed polygon
    polygon.append(polygon[0])

    xs, ys = zip(*polygon)
    plt.plot(xs, ys, "r-", linewidth=0.4)

    plt.savefig(out_file_name, dpi=300)
    plt.close()


# this is just so that you can reproduce the same results
# random.seed(5)

# take input in numpoints
# num_points = int(input())
# num_points = random(3, 100)
# num_points = random.randint(100, 300)
num_points = 20 
# num_points = random.randrange(3, 100)
polygon = random_polygon(num_points)
# reverse the point of polygon
# polygon.reverse()
polygon = polygon[::-1]

with open("input.txt", "w") as f:
    sys.stdout = f
    print(polygon.__len__())
    for point in polygon:
        print(round(5*point[0],7), round(5*point[1], 7))
