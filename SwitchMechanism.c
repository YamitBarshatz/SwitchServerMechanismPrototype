#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS_GLOBALS

#define FLAG_VAL (-2)

#include "SwitchMechanism.h"
#include <math.h>
/* Source */
/* Switch API */
switch_mechanism* switch_mechanism_init(
	int num_of_segments,
	int segment_length,
	int max_value)
{
	switch_mechanism* switch_handler = NULL;
	int i = 0; mehcanism_apply_switch_flow

	if (num_of_segments <= 0 || segment_length <= 0 || max_value <= 0) {
		return NULL;
	}

	switch_handler = (switch_mechanism*)malloc(sizeof(switch_mechanism));
	if (!switch_handler) {
		return NULL;
	}

	//printf("\nSwitch mechanism allocated.\n");//for_release

	switch_handler->num_of_segments = num_of_segments;
	switch_handler->segments = (switch_segment_node*)malloc(sizeof(switch_segment_node) * num_of_segments);
	if (!switch_handler->segments) {
		free(switch_handler);
		return NULL;
	}

	//printf("\nSwitch segments allocated.\n");//for_release

	for (i = 0; i < num_of_segments; i++) {
		int iter = 0;
		switch_handler->segments[i].size = segment_length;
		switch_handler->segments[i].first_size_values_cnt = segment_length;
		switch_handler->segments[i].partition_index = 0;
		//switch_handler->segments[i].current_start = 0;
		//switch_handler->segments[i].last_right_val = INIT_VALUE;
		switch_handler->segments[i].data_flow = (int*)malloc(sizeof(int) * segment_length);
		if (!switch_handler->segments[i].data_flow) {
			int j = 0;
			for (j = 0; j < i; j++) {
				free(switch_handler->segments[j].data_flow);
			}
			free(switch_handler->segments);
			free(switch_handler);
			return NULL;
		}
		switch_handler->segments[i].start = 0;
		switch_handler->segments[i].end = 0; //TODO: Wht zero? shouldnt be segment length -1?
		for (iter = 0; iter < segment_length; iter++) {
			switch_handler->segments[i].data_flow[iter] = INIT_VALUE;
			//printf("\nset segment %d index %d value %d", i, iter, switch_handler->segments[i].data_flow[iter]);//for_release
		}
		//printf("\nSwitch segment %d data allocated %d cells.\n", i, segment_length);//for_release
	}
	switch_handler->max_value = max_value;

	return switch_handler;
}

mechanism_results switch_mechanism_set_ranges_default(switch_mechanism* s)
{
	int segment = 0;
	int current_start = 0;
	int i;

	if (!s) {
		return MECHANISM_NULL_POINTER;
	}
	
	int q = (s->max_value) / (s->num_of_segments);
	int r = (s->max_value) % (s->num_of_segments);
	//printf("q is %d\n", q);//for_release
	//printf("r is %d\n", r);//for_release
	int current_end = q;
	
	for (i = 0; i < r; i++) {
		if (segment < (s->num_of_segments)) {
			//printf("segment is %d\n", segment);//for_release
			s->segments[segment].start = current_start;
			s->segments[segment].end = current_end;
			current_start += q + 1;
			current_end += q + 1;
			//printf("\nSwitch segment %d data range: [%d,%d].\n", segment, s->segments[segment].start, s->segments[segment].end);//for_release
			segment++;
		}

	}
	current_end--;
	for ( ; segment < (s->num_of_segments); segment++) {
			if (segment == (s->num_of_segments - 1)) {
				s->segments[segment].start = current_start;
				s->segments[segment].end = (s->max_value);
				//printf("\nSwitch segment %d data range: [%d,%d].\n", segment, s->segments[segment].start, s->segments[segment].end);//for_release
				break;
			}
			s->segments[segment].start = current_start;
			s->segments[segment].end = current_end;
			current_start += q;
			current_end += q;
			//printf("\nSwitch segment %d data range: [%d,%d].\n", segment, s->segments[segment].start, s->segments[segment].end);//for_release

	}

	return MECHANISM_SUCCESS;
}

int switch_find_next_segment_and_index(
	struct switch_mechanism* s,
	int input,
	int* segment,
	int* index)
{
	int seg = 0;
	int out_seg = INIT_VALUE;
	int idx = 0;
	int out_idx = INIT_VALUE;

	if (!s || !segment || !index) {
		return MECHANISM_NULL_POINTER;
	}
	//printf("num of segment is: %d", s->num_of_segments);
	for (seg = 0; seg < s->num_of_segments; seg++) {
		if (input >= s->segments[seg].start && input <= s->segments[seg].end) {
			out_seg = seg;
			//printf("\nseg: %d, size_values_cnt %d\n", seg, s->segments[seg].first_size_values_cnt);
			if ((s->segments[seg].first_size_values_cnt) > 0) {
				//printf("\nseg: %d, size_values_cnt %d\n", seg, s->segments[seg].first_size_values_cnt);
				for (idx = 0; idx < s->segments[seg].size; idx++) {
					if (s->segments[seg].data_flow[idx] == INIT_VALUE || input < s->segments[seg].data_flow[idx]) {
					//	printf("\nInsert index %d\n", idx);//for_release
						out_idx = idx;
						//printf("\nfirst_size_values_cnt %d\n", s->segments[seg].first_size_values_cnt);
					//	s->segments[seg].first_size_values_cnt--;
					//	printf("\nseg: %d, size_values_cnt %d\n", seg, s->segments[seg].first_size_values_cnt);//for_release
						break;
					}
				}
			}
			else {
				int seg_size = s->segments[seg].size;
				int part_idx = s->segments[seg].partition_index;
				for (idx = 0; idx < part_idx; idx++) {
					if (input < s->segments[seg].data_flow[idx]) {
						//printf("\nsec_size_values_cnt %d\n", s->segments[seg].first_size_values_cnt);//for_release
						break;
					}
				}
				out_idx = idx;
			}
			break;
		}
	}

	*segment = out_seg;
	if (out_idx != INIT_VALUE) {
		*index = out_idx;
		return MECHANISM_SUCCESS;
	}
	else {
		return MECHANISM_SEGMENT_OUT_OF_INDEXES;
	}
}

int switch_insert_value_to_segment(
	struct switch_mechanism* s,
	int segment,
	int index,
	int value,
	int* output)
{
	int tmp_val = INIT_VALUE;
	int current = value;
//	int temp_last_val = s->segments[segment].last_right_val;
	int i = 0;

	if (!s || !output) {
		return MECHANISM_NULL_POINTER;
	}

	if (s->segments[segment].first_size_values_cnt <= 0) {
		*output = s->segments[segment].data_flow[s->segments[segment].partition_index];
		//printf("\n2\n");
		for (int idx = 0; idx < s->segments[segment].partition_index; idx++) {
			//printf("\n4\n");
			if (value < s->segments[segment].data_flow[idx]) {
				//printf("\n5\n");
				for (i = idx; i <= s->segments[segment].partition_index; i++) {
					//printf("\n6\n");
					tmp_val = s->segments[segment].data_flow[i];
					s->segments[segment].data_flow[i] = current;
					current = tmp_val;
					//printf("\n7\n");
				}
				//printf("\n8\n");
				s->segments[segment].partition_index = (s->segments[segment].partition_index + 1) % (s->segments[segment].size);

				//printf("\ncurrent start new row 207: %d", s->segments[segment].current_start);
				return MECHANISM_SUCCESS;
			}
		}
			//printf("\n9\n");
			s->segments[segment].data_flow[s->segments[segment].partition_index] = value;
			s->segments[segment].partition_index = (s->segments[segment].partition_index + 1) % (s->segments[segment].size);
			//printf("\n10\n");
			return MECHANISM_SUCCESS;
	}
	else {
		//int init_state = 0;
		//printf("\n21\n");
		for (i = index; i < (s->segments[segment].size); i++) {
			//printf("\n22\n");
			tmp_val = s->segments[segment].data_flow[i];
		//	if (tmp_val == INIT_VALUE) {
		//		init_state = 1;
		//B	}
			s->segments[segment].data_flow[i] = current;
			current = tmp_val;
			//printf("\n23\n");
		//	printf("\nseg: %d, size_values_cnt %d\n", segment, s->segments[segment].first_size_values_cnt);//for_release

		}

		s->segments[segment].first_size_values_cnt--;
		*output = INIT_VALUE;
		//printf("\n25\n");
	}
	//printf("\n26\n");
	return MECHANISM_SUCCESS;
}

int switch_insert_next(
	struct switch_mechanism* s,
	int input,
	int* output_port,
	int* output_value)
{
	int index = INIT_VALUE;
	int port = INIT_VALUE;
	int val = INIT_VALUE;
	enum mechanism_results result;

	if (!s || !output_port || !output_value) {
		return MECHANISM_NULL_POINTER;
	}
	//printf("\nInserting value %d.\n", input);//for_release
	result = switch_find_next_segment_and_index(s, input, &port, &index);
	//printf("\nport is: %d, index is: %d", port, index);//for_release
	if (result != MECHANISM_SUCCESS && result != MECHANISM_SEGMENT_OUT_OF_INDEXES) {
		return result;
	}
	//printf("\nSet value %d at segment %d index %d\n", input, port, index);//for_release
	result = switch_insert_value_to_segment(s, port, index, input, &val);
	if (result != MECHANISM_SUCCESS) {
		return result;
	}
	//printf("\n100\n");
//	printf("\nBBBBBBBBBBBB\n");
	for (int i = 0; i < s->num_of_segments; i++) {
	//	printf("segment number: %d\n", i);
		//printf("current start: %d\n", s->segments[i].current_start);
		//printf("array data flow:\n");
		//s->segments[i].last_right_val = s->segments[i].data_flow[s->segments[i].size - 1];
	//	for (int j = 0; j < s->segments[i].size; j++) {
		//	printf("%d, ", s->segments[i].data_flow[j]);
		//}
		//printf("\n");
	}
	*output_port = port;
	*output_value = val;
	//printf("\n1010\n");

	//printf("\nOutput value %d dedicated for port %d\n", val, port);//for_release
	return MECHANISM_SUCCESS;
}

mechanism_results release_segment_data(struct switch_segment_node* segment)
{
	if (!segment) {
		return MECHANISM_NULL_POINTER;
	}
	//printf("\n100000000");

	if (segment->data_flow) {
		//printf("\n100000001000000");

		free(segment->data_flow);
		//printf("\n222000002000000");

	}

	return MECHANISM_SUCCESS;
}

mechanism_results release_switch(struct switch_mechanism* s)
{
	enum mechanism_results result;
	if (!s) {
		return MECHANISM_NULL_POINTER;
	}

	if (s->segments) {
		int i;
		for (i = 0; i < s->num_of_segments; i++) {
			//printf("\n90000000");

			result = release_segment_data(&(s->segments[i]));
			if (result != MECHANISM_SUCCESS) {
				return result;
			}
		}
		//printf("\n80000000");
		free(s->segments);
	}

	free(s);

	return MECHANISM_SUCCESS;
}


mechanism_results mehcanism_apply_switch_flow(int run_id, int num_of_segments,
	int segment_lenght, FILE* input_file, char* segment_prefix_name, int maximum_value)
{
	//printf("\ncalled mechanism apply switch\n");
	if (!segment_prefix_name) {
		printf("\nerror\n");
		return MECHANISM_NULL_POINTER;
	}

	int i;
	mechanism_results res;
//	printf("\n1");
	FILE** segments_files = (FILE**)malloc(num_of_segments * sizeof(FILE*));
	if (!segments_files) {
		return MECHANISM_ALLOC_FAILED;
	}

	char* segment_output_file = (char *)malloc(sizeof(char)*(strlen(segment_prefix_name) + 60));
	for (i = 0; i < num_of_segments; i++) {
		strcpy(segment_output_file, segment_prefix_name);
		char prefix_name[] = "switch_output_file_";
		strcat(segment_output_file, prefix_name);
		char id[10];
		_itoa(run_id, id, 10);
		strcat(segment_output_file, id);
		strcat(segment_output_file, "_");
		char index[10];
		_itoa(i, index, 10);
		strcat(segment_output_file, index);
		char num_of_seg[10];
		_itoa(num_of_segments, num_of_seg, 10);
		strcat(segment_output_file, "_");
		strcat(segment_output_file, num_of_seg);
		char len_of_seg[10];
		_itoa(segment_lenght, len_of_seg, 10);
		strcat(segment_output_file, "_");
		strcat(segment_output_file, len_of_seg);
		strcat(segment_output_file,".txt");
		segments_files[i] = fopen(segment_output_file, "w+");
	}

//	printf("\n%s\n", segment_output_file);

	free(segment_output_file);
//	printf("\n3");
	res = mechanism_switch_flow(num_of_segments, segment_lenght, input_file, segments_files, maximum_value);
//	printf("\n8");
	return res;
}

mechanism_results mechanism_switch_flow(int num_of_segments, int segment_lenght,
	FILE* input_file, FILE** output_files, int maximum_value)
{
//	printf("\n4");
	struct switch_mechanism* s;
	mechanism_results result;
	s = switch_mechanism_init(num_of_segments, segment_lenght, maximum_value);
	if (!s) {
		printf("\nSwitch was not allocated.\n");//for_release
		return MECHANISM_ALLOC_FAILED;
	}
//	printf("\n5");
	switch_mechanism_set_ranges_default(s);
	int output_port;
	int output_value;
	char value_str_from_file[10];
	char value_str_from_switch[10];
	int value_to_insert;
	while (fgets(value_str_from_file, 10, input_file) != NULL) {
		value_to_insert = atoi(value_str_from_file);
		switch_insert_next(s, value_to_insert, &output_port, &output_value);
		if (output_value != INIT_VALUE) {
			//printf("\n60000");
			_itoa(output_value, value_str_from_switch, 10);
			fputs(value_str_from_switch, output_files[output_port]);
			fputs("\n", output_files[output_port]);
			//printf("\n60001");
		}
	}
	//printf("\n60002");
	int port, i, current_val;
	for (port = 0; port < s->num_of_segments; port++) {
		//printf("\n60003");
		for (i = s->segments[port].partition_index; i < s->segments[port].size; i++) {
			//printf("\n60004");
			current_val = s->segments[port].data_flow[i];
			if (current_val != INIT_VALUE) {
				//printf("\n60005");
				//printf("\nport: %d, value: %d", port, current_val);//for_release
				_itoa(current_val, value_str_from_switch, 10);
				fputs(value_str_from_switch, output_files[port]);
				fputs("\n", output_files[port]);
				//printf("\n60006");
			}
		}
		for (i = 0; i < s->segments[port].partition_index; i++) {
			//printf("\n60004");
			current_val = s->segments[port].data_flow[i];
			if (current_val != INIT_VALUE) {
				//printf("\n60005");
				//printf("\nport: %d, value: %d", port, current_val);//for_release
				_itoa(current_val, value_str_from_switch, 10);
				fputs(value_str_from_switch, output_files[port]);
				fputs("\n", output_files[port]);
				//printf("\n60006");
			}
		}
	}
//	printf("\n7");
	//printf("\n60007");
	release_switch(s);
	//printf("\n60008");
	return MECHANISM_SUCCESS;
}

/* End of Switch API */