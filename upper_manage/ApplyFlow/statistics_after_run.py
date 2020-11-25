#python
import sys
import math
in_file=sys.argv[1]
#out_file=sys.argv[2]
input_file = open(in_file, 'r')
count_stamps = 0
column = []
time_stamp_counter = 0
for line in input_file:
	if line.startswith("Merge sort cpu time is:"):
		current_time = float(line.split(": ")[1])
		time_stamp_counter += current_time
		column.append(float(current_time))
		count_stamps += 1
		print "stamp #",count_stamps,":	",current_time
		
print "\n"		
print "Average time stamps:",time_stamp_counter/count_stamps

column.sort()
#print(column)
Median = int(count_stamps/2)
print "Median time stamps:", column[Median]

five_precent_size = int(count_stamps/20) + (count_stamps % 20 > 0)
lower_counter=0

for i in range(0, five_precent_size):
	lower_counter += column[i]

print "Lower 5 precent Average:", lower_counter/five_precent_size

upper_counter=0

for i in range(count_stamps - five_precent_size, count_stamps):
	upper_counter += column[i]

print "Upper 5 precent Average:", upper_counter/five_precent_size

print "\n"

input_file.close()
