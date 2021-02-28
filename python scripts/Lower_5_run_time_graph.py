from mpl_toolkits import mplot3d

import numpy as np
import matplotlib.pyplot as plt

import sys
import math

in_file=sys.argv[1]
input_file = open(in_file, 'r')

z_line = []
x_line = []
y_line = []

for line in input_file:
	if line.startswith("Number of segment"):
		continue
	obj = line.split(", ")
	obj = line.split(", ")
	x = float(obj[0])
	y = float(obj[1])
	if x == 0 and y == 0:
		continue
	x_line.append(x)
	y_line.append(y)
	z_line.append(float(obj[4]))

fig = plt.figure()
ax = plt.axes(projection="3d")

ax.plot3D(x_line, y_line, z_line, 'gray')
ax.scatter3D(x_line, y_line, z_line, 'gray')


plt.show()