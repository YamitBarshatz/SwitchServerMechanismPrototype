from mpl_toolkits import mplot3d
from matplotlib import cm
import numpy as np
import matplotlib.pyplot as plt
from random import randint
import sys
import math
from matplotlib import colors

fig = plt.figure()

in_file=sys.argv[1]
input_file = open(in_file, 'r')
output_plot = sys.argv[2]
roll_t = sys.argv[3]
roll = int(roll_t)

enroll = None
if roll == 2:
	enroll = "Average"
if roll == 3:
	enroll = "Median"
if roll == 4:
	enroll = "5_Low"
if roll == 5:
	enroll = "5_High"

#Average 3D graphs:
line_m = []
x_line_m = []
y_line_m = []
line_d = []
x_line_d = []
y_line_d = []
line_mor = []
x_line_mor = []
y_line_mor = []
data_line = []
x_line = []
y_line = []

minimum = 0
details = 1
minor = 5

for line in input_file:
	if line.startswith("Number of segment"):
		continue
	obj = line.split(", ")
	obj = line.split(", ")
	x = float(obj[0])
	y = float(obj[1])
	if x == 0 and y == 0:
		continue
	Z = float(obj[roll])
	if Z >= minor:
		line_mor.append(Z)
		x_line_mor.append(x)
		y_line_mor.append(y)
	if Z < minor and Z > details:
		line_d.append(Z)
		x_line_d.append(x)
		y_line_d.append(y)
	if Z <= details:
		line_m.append(Z)
		x_line_m.append(x)
		y_line_m.append(y)
	data_line.append(Z)	
	x_line.append(x)
	y_line.append(y)
	
main_g = fig.gca(projection='3d')

main_g.plot_trisurf(x_line, y_line, data_line, cmap=plt.cm.Spectral)
plt.show()
plt.savefig(output_plot + "/" + enroll + "_graph_3D_Main_to_side_view")
"""
plt.cla()

main_g.plot_trisurf(x_line_mor, y_line_mor, line_mor, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/" + enroll + "_graph_3D_Minor")
plt.cla()

main_g.plot_trisurf(x_line_d, y_line_d, line_d, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/" + enroll + "_graph_3D_Detailed")
plt.cla()

main_g.plot_trisurf(x_line_m, y_line_m, line_m, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/" + enroll + "_graph_3D_Minimum")
plt.cla()
"""