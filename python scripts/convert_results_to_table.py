#python

import sys
import math
import os
in_file1=sys.argv[1]
in_file2=sys.argv[2]
input_file1 = open(in_file1, 'r')
input_file2 = open(in_file2, 'r')

class results_info:
	segments = 0
	length = 0
	average = 0
	median = 0
	lower = 0
	upper = 0

results = []
res_ob = results_info()

for line in input_file1:
	if (not line.startswith("Average time stamps:")) and (not line.startswith("Median time stamps:")) and (not line.startswith("Lower 5 precent Average")) and (not line.startswith("Upper 5 precent Average")):
		continue
	if line.startswith("Average time stamps:"):
		res_ob.average = float(line.split(" ")[3])
	if line.startswith("Median time stamps:"):
		res_ob.median = float(line.split(" ")[3])
	if line.startswith("Lower 5 precent Average"):
		res_ob.lower = float(line.split(" ")[4])
	if line.startswith("Upper 5 precent Average"):
		res_ob.upper = float(line.split(" ")[4])
results.append(res_ob)

flag = 0
current = None
for line in input_file2:
	if (not line.startswith("Average time stamps:")) and (not line.startswith("Median time stamps:")) and (not line.startswith("Lower 5 precent Average")) and (not line.startswith("Upper 5 precent Average")) and (not line.startswith("Statistics")):
		continue
	if line.startswith("Statistics"):
		res_ob = results_info()
		res_ob.segments = int(line.split(" ")[2])
		res_ob.length = int((line.split(" ")[7]).split(":")[0])
		results.append(res_ob)
		flag = 0
		current = res_ob
		continue
	if line.startswith("Average time stamps:"):
		flag = 1
	if line.startswith("Median time stamps:"):
		flag = 2
	if line.startswith("Lower 5 precent Average"):
		flag = 3
	if line.startswith("Upper 5 precent Average"):
		flag = 4
	
	exist_checker = 0
	for obj in results:
		if obj.segments == current.segments and obj.length == current.length:
			exist_checker = 1
			value = float(line.split(": ")[1])
			if flag == 1:
				obj.average = value
			if flag == 2:
				obj.median = value
			if flag == 3:
				obj.lower = value
			if flag == 4:
				obj.upper = value
	flag = 0;
	
	
print "Number of segments, Segments length, Average, Median, Lower 5, Upper 5"
for o in results:
	row = str(o.segments) + ", "
	row += str(o.length) + ", "
	row += str(o.average) + ", "
	row += str(o.median) + ", "
	row += str(o.lower) + ", "
	row += str(o.upper)	
	print row
input_file1.close()
input_file2.close()