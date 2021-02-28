#from mpl_toolkits import mplot3d

#import numpy as np
import math
import matplotlib.pyplot as plt

import sys


in_file=sys.argv[1]
output_plot=sys.argv[2]
"""
criteria=sys.argv[3]
criteria2=sys.argv[4]
criteria2=sys.argv[4]
criteria2=sys.argv[4]
"""
roll_t = sys.argv[3]
roll = int(roll_t)
case = sys.argv[4]

input_file = open(in_file, 'r')

enroll = None
if roll == 2:
	enroll = "Average"
if roll == 3:
	enroll = "Median"
if roll == 4:
	enroll = "5_Low"
if roll == 5:
	enroll = "5_High"

colors = ["red", "yellow", "pink", "black", "blue", "purple", "grey"]
ii=0
x1_line = []
x4_line = []
x8_line = []
x16_line = []
x32_line = []
x64_line = []
x128_line = []
y1_line = []
y4_line = []
y8_line = []
y16_line = []
y32_line = []
y64_line = []
y128_line = []
y_line = []


main_g=plt
#for seg in ("1", "4", "8", "16", "32", "64", "128"):

	#print(seg)
for line in input_file:
	if line.startswith("Number of segment"):
		continue
	obj = line.split(", ")
	x = (obj[0])
	y = (obj[1])
	z = float(obj[roll])
	
	#if (not x == seg) and (case == "0"):
	#	continue
	#if (not y == seg) and (case == "1"):
	#	continue
	#print(line)
	if case == "1":
		if y =="1":
			x1_line.append(x)
			y1_line.append(z)
		if y =="4":
			x4_line.append(x)
			y4_line.append(z)
		if y =="8":
			x8_line.append(x)
			y8_line.append(z)
		if y =="16":
			x16_line.append(x)
			y16_line.append(z)
		if y =="32":
			x32_line.append(x)
			y32_line.append(z)
		if y == "64":
			x64_line.append(x)
			y64_line.append(z)
		if y == "128":
			x128_line.append(x)
			y128_line.append(z)

#plotting the points  

main_g.plot(x1_line, y1_line, color='red', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)
main_g.plot(x4_line, y4_line, color='pink', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)
main_g.plot(x8_line, y8_line, color='black', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)
main_g.plot(x16_line, y16_line, color='yellow', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)
main_g.plot(x32_line, y32_line, color='purple', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)
main_g.plot(x64_line, y64_line, color='blue', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)		
main_g.plot(x128_line, y128_line, color='grey', linestyle='dashed', linewidth = 3, 
		 marker='o', markerfacecolor='blue', markersize=12)		 
main_g.show()

target = None
if case == "0":
	target = "num_of_segments"
else:
	target = "segments_length"
plt.savefig(output_plot + "/" + enroll + "_graph_all_include_-_" + target)

#plt.show() 