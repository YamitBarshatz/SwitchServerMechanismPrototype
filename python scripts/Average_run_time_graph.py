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
output_plot=sys.argv[2]


#Average 3D graphs:
avg_line_m = []
avg_x_line_m = []
avg_y_line_m = []
avg_line_d = []
avg_x_line_d = []
avg_y_line_d = []
avg_line_mor = []
avg_x_line_mor = []
avg_y_line_mor = []
avg_line = []
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
	Z = float(obj[2])
	if Z >= minor:
		avg_line_mor.append(Z)
		avg_x_line_mor.append(x)
		avg_y_line_mor.append(y)
	if Z < minor and Z > details:
		avg_line_d.append(Z)
		avg_x_line_d.append(x)
		avg_y_line_d.append(y)
	if Z <= details:
		avg_line_m.append(Z)
		avg_x_line_m.append(x)
		avg_y_line_m.append(y)
	avg_line.append(Z)	
	x_line.append(x)
	y_line.append(y)
	
avg_main_g = fig.gca(projection='3d')

avg_main_g.plot_trisurf(x_line, y_line, avg_line, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/Average_graph_3D_Main")
plt.cla()

avg_main_g.plot_trisurf(avg_x_line_mor, avg_y_line_mor, avg_line_mor, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/Average_graph_3D_Minor")
plt.cla()

avg_main_g.plot_trisurf(avg_x_line_d, avg_y_line_d, avg_line_d, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/Average_graph_3D_Detailed")
plt.cla()

avg_main_g.plot_trisurf(avg_x_line_m, avg_y_line_m, avg_line_m, cmap=plt.cm.Spectral)
plt.savefig(output_plot + "/Average_graph_3D_Minimum")
plt.cla()

#Average 2D graphs:



#plt.show()