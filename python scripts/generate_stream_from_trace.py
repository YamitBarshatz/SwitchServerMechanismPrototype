import sys
import math

in_file=sys.argv[1]
input_file = open(in_file, 'r')

for line in input_file:
	if not "length" in line:
		continue
	val = line.split("length ")[1]
	if " " in val:
		continue
	print val.split("\n")[0]