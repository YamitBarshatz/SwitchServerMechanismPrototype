#!/bin/bash

num_of_seg=16
num_of_segments_list=( 1 4 8 16 32 64 128 )
segment_length_list=( 4 8 16 32 64 128 )
k=10
switch_input_path=/home/yamit/SwitchServerMechanismPrototype_git/FlowInputs/RandomInput/random_test_file_1M.txt
switch_output_path=/home/yamit/SwitchServerMechanismPrototype_git/FlowOutputs/switch/v1.00/
server_input_path=$switch_output_path
server_output_path=/home/yamit/SwitchServerMechanismPrototype_git/FlowOutputs/server/v1.00/
server_output_stats=/home/yamit/SwitchServerMechanismPrototype_git/FlowOutputs/server/v1.00/stats/tmp_stats.txt
max_val=524288
num_of_vals=1000000
iterations=( 1 2 3 4 5 6 7 8 9 10 )
Mechanism=../SwitchServerMechanismPrototype/a.out

for m in "${num_of_segments_list[@]}";
do
	echo Number of segments: $m
	for n in "${segment_length_list[@]}";
	do
		rm $server_output_stats
		echo Segments length: $n
		for i in $iterations;
		do  
			echo Itertion: $i
			echo switch flow
			./$Mechanism switch $i $m $n $switch_input_path $switch_output_path $max_val
			echo server flow
			./$Mechanism server $i $m $n $k $server_input_path $server_output_path >> $server_output_stats
			echo check if sorted
			outF=/home/yamit/SwitchServerMechanismPrototype_git/FlowOutputs/server/v1.00/merged_output_file_${i}_${m}_${n}.txt
			#touch $outF
			echo $outF
			#cat $outF
			./$Mechanism validate $outF $num_of_vals
		done
		echo "Statistics for $m segments with length of $n:"
		python ..//SwitchServerMechanismPrototype/statistics_after_run.py $server_output_stats
		echo 
	done
done
echo End
