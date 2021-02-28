from mpl_toolkits import mplot3d

import numpy as np
import matplotlib.pyplot as plt

import sys
import math

in_file=sys.argv[1]
num_of_segments=sys.argv[2]
input_file = open(in_file, 'r')

x_line = []
y_line = []

for line in input_file:
	if line.startswith("Number of segment"):
		continue
	obj = line.split(", ")
	x = obj[0]
	y = float(obj[1])
	z = float(obj[4])
	if not x == num_of_segments:
		continue
	x_line.append(y)
	y_line.append(z)

# plotting the points  
plt.plot(x_line, y_line, color='red', linestyle='dashed', linewidth = 3, 
         marker='o', markerfacecolor='yellow', markersize=12) 
  
output_plot=sys.argv[3]

plt.savefig(output_plot + "/Lower_5_precent_graph_-_" + sys.argv[2] + "_segments")
#plt.show() 