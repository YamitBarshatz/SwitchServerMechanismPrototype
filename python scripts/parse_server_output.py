#python
import sys
import math
in_file=sys.argv[1]
#out_file=sys.argv[2]
input_file = open(in_file, 'r')

for line in input_file:
	if line.startswith("Statistics for"):
		print line
	if line.startswith("Average time stamps:"):
		print line
	if line.startswith("Median time stamps:"):
		print line
	if line.startswith("Lower 5 precent Average"):
		print line
	if line.startswith("Upper 5 precent Average"):
		print line

input_file.close()