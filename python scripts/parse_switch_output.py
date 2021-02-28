#python
import sys
import math
import os
in_dir=sys.argv[1]

class stats_info:
	x = 0
	y = 0
	total_num_of_runs = 0
	min_run_length = (-1)
	max_run_length = 0
	all_runs_length = None

stats = []

for filename in os.listdir(in_dir):
	if not filename.endswith(".txt") or not filename.startswith("switch_output_file_1_"):
		continue
	file_stats = stats_info()
	file_stats.x = int(filename.split("_")[5])
	file_stats.y = int(filename.split("_")[6].split(".")[0])
	first_run_in_segment = 0
	prev_v = -1
	current_run_length = 0
	file_stats.all_runs_length = []
	value = -1
	f = open(sys.argv[1] + "\\" + filename, 'r')
	for line in f:
		#updating previous value before getting a new one
		prev_v = value
		#get next value
		value = int(line)
		#current segment run continue
		if value >= prev_v:
			current_run_length += 1
			continue
		#end offirst run at this segment
		if first_run_in_segment == 0:
			file_stats.min_run_length = current_run_length
			file_stats.max_run_length = current_run_length
			file_stats.all_runs_length.append(current_run_length)
			file_stats.total_num_of_runs = 1
			first_run_in_segment = 1
			current_run_length = 1
			continue
		#end of run and it is not the first at this segment
		if file_stats.min_run_length > current_run_length:
			file_stats.min_run_length = current_run_length
		if file_stats.max_run_length < current_run_length:
			file_stats.max_run_length = current_run_length
		file_stats.total_num_of_runs += 1
		file_stats.all_runs_length.append(current_run_length)
		current_run_length = 1
	if file_stats.min_run_length > current_run_length:
		file_stats.min_run_length = current_run_length
	if file_stats.max_run_length < current_run_length:
		file_stats.max_run_length = current_run_length
	file_stats.total_num_of_runs += 1
	file_stats.all_runs_length.append(current_run_length)
	f.close()
	#check if x,y exist - if yes update values
	exist_checker = 0
	for obj in stats:
		if obj.x == file_stats.x and obj.y == file_stats.y:
			exist_checker = 1
			if file_stats.min_run_length < obj.min_run_length:
				obj.min_run_length = file_stats.min_run_length
			if file_stats.max_run_length > obj.max_run_length:
				obj.max_run_length = file_stats.max_run_length
			obj.total_num_of_runs += file_stats.total_num_of_runs
			obj.all_runs_length += file_stats.all_runs_length
	#if x,y does not exist append it
	if exist_checker == 0:
		stats.append(file_stats)

print "Number of segments, Segments length, Average number of runs,  Minimum run length, Maximum run Length, Median run length, Average run length"
for o in stats:
	#print o.total_num_of_runs
	avg_num_of_runs = (o.total_num_of_runs / o.x)
	o.all_runs_length.sort()
	median_r_length_indx = int(o.total_num_of_runs / 2)
	#print o.all_runs_length
	#print median_r_length_indx
	avg_r_length = sum(o.all_runs_length) / float(o.total_num_of_runs)
	row = str(o.x) + ", "
	row += str(o.y) + ", "
	row += str(avg_num_of_runs) + ", "
	row += str(o.min_run_length) + ", "
	row += str(o.max_run_length) + ", "
	row += str(o.all_runs_length[median_r_length_indx]) + ", "
	row += str(avg_r_length)	
	print row
#	print o.min_run_length, o.max_run_length, o.all_runs_length[median_r_length_indx], avg_r_length