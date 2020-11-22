#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS_GLOBALS

#include "ServerMechanism.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_INT 2147483647
/* Source */
/* Server API */

static int flag = 0;

struct server_mechanism* server_mechanism_init(int num_of_ports)
{
	int i = 0, j = 0;
	struct server_mechanism* server_side = NULL;
	if (num_of_ports <= 0) {
		return NULL;
	}

	server_side = (server_mechanism*)malloc(sizeof(server_mechanism));
	if (!server_side) {
		return NULL;
	}

	server_side->num_of_ports = num_of_ports;

	server_side->ports = (server_port_node*)malloc(sizeof(server_port_node) * num_of_ports);
	if (!server_side->ports) {
		free(server_side);
		return NULL;
	}

//	printf("\nServer mechanism allocated.\n"); //for_release

	for (i = 0; i < num_of_ports; i++) {
		server_side->ports[i].indexes = (int*)calloc(INIT_SERVER_INDEXES_SIZE, sizeof(int));
		if (!(server_side->ports[i].indexes)) {
			for (j = 0; j < i; j++) {
				free(server_side->ports[j].indexes);
			}
			free(server_side);
			return NULL;
		}
		server_side->ports[i].segment_data = (int*)malloc(sizeof(int) * INIT_SERVER_SEGMENT_SIZE);
		if (!server_side->ports[i].segment_data) {
			for (j = 0; j < i; j++) {
				free(server_side->ports[j].indexes);
				free(server_side->ports[j].segment_data);
			}
			free(server_side);
			return NULL;
		}
		memset(server_side->ports[i].segment_data, INIT_VALUE, INIT_SERVER_SEGMENT_SIZE * sizeof(int));
		server_side->ports[i].current_size_of_indexes_array = INIT_SERVER_INDEXES_SIZE;
		server_side->ports[i].current_size_of_segment = INIT_SERVER_SEGMENT_SIZE;
		server_side->ports[i].last_inserted_value_index = INIT_VALUE;
		server_side->ports[i].num_of_runs = 0;
	}

//	printf("\nServer ports allocated.\n"); //for_release
	return server_side;
}

mechanism_results server_insert(
	server_mechanism* server_side,
	int port,
	int value)
{
	server_port_node* current_port_node = NULL;
//	printf("\nServer side action.\n"); //for_release

	if (!server_side) {
//		printf("\nServer NULL.\n"); //for_release
		return MECHANISM_NULL_POINTER;
	}

	if (port > server_side->num_of_ports) {
		return MECHANISM_PORT_NOT_MATCH;
	}

	int last_inserted_value_index = server_side->ports[port].last_inserted_value_index;
	int current_size_of_segment = server_side->ports[port].current_size_of_segment;
	int current_size_of_indexes_array = server_side->ports[port].current_size_of_indexes_array;
	int num_of_runs = server_side->ports[port].num_of_runs;
	
	if (last_inserted_value_index == current_size_of_segment - 1) {
		printf("\n\nhhhhh\n");
		int* resized_segment_array =
			(int*)realloc(server_side->ports[port].segment_data,
				current_size_of_segment * 2 * sizeof(int));
		if (!resized_segment_array) {
			free(server_side->ports[port].segment_data);
			return MECHANISM_ALLOC_FAILED;
		}

		server_side->ports[port].segment_data = resized_segment_array;
		resized_segment_array = NULL;

		memset(server_side->ports[port].segment_data + current_size_of_segment,
			INIT_VALUE, current_size_of_segment * sizeof(int));
//		printf("\n Segment data array in port %d resized from %d to %d", port, current_size_of_segment, current_size_of_segment * 2); //for_release
		server_side->ports[port].current_size_of_segment *= 2;
	}
//	printf("\nlast_inserted_value_index 1: %d\n", last_inserted_value_index);
	server_side->ports[port].segment_data[++last_inserted_value_index] = value;
	server_side->ports[port].last_inserted_value_index = last_inserted_value_index;
//	printf("\nlast_inserted_value_index 2: %d\n", last_inserted_value_index);
	
	if (last_inserted_value_index == 0) {
		server_side->ports[port].indexes[num_of_runs] = last_inserted_value_index;
		server_side->ports[port].num_of_runs++;
		num_of_runs++;
	}
	else if (server_side->ports[port].segment_data[last_inserted_value_index - 1] >
		server_side->ports[port].segment_data[last_inserted_value_index]) {
		if (num_of_runs == current_size_of_indexes_array) {
			printf("\n\njjjjj\n");

			int* resized_indexes_array =
				(int*)realloc(server_side->ports[port].indexes, current_size_of_indexes_array * 2 * sizeof(int));
			if (!resized_indexes_array) {
				free(server_side->ports[port].indexes);
				printf("\n\n333333\n");
				return MECHANISM_ALLOC_FAILED;
			}
			
			server_side->ports[port].indexes = resized_indexes_array;
			resized_indexes_array = NULL;

			memset(server_side->ports[port].indexes + current_size_of_indexes_array,
				0, current_size_of_indexes_array * sizeof(int));
//			printf("\n Indexes array in port %d resized from %d to %d", port, current_size_of_indexes_array, current_size_of_indexes_array * 2); //for_release
			server_side->ports[port].current_size_of_indexes_array *= 2;
//			printf("\n New size of indexes array is: %d\n", server_side->ports[port].current_size_of_indexes_array);
		}
		/*if (num_of_runs == 1000) {
			printf("\n1num of runs is 1000.\nserver_side->ports[port].indexes[num_of_runs-1] = %d\n", server_side->ports[port].indexes[num_of_runs-1]);
			printf("\n2num of runs is 1000.\nserver_side->ports[port].indexes[num_of_runs] = %d\n", server_side->ports[port].indexes[num_of_runs]);
		}
		if (num_of_runs == 1001) {
			printf("\n1num of runs is 1001.\nserver_side->ports[port].indexes[num_of_runs-1] = %d\n", server_side->ports[port].indexes[num_of_runs - 1]);
			printf("\n2num of runs is 1001.\nserver_side->ports[port].indexes[num_of_runs] = %d\n", server_side->ports[port].indexes[num_of_runs]);
		}*/
		server_side->ports[port].indexes[num_of_runs] = last_inserted_value_index;
		server_side->ports[port].num_of_runs++;
		num_of_runs++;
	}

//	printf("\nServer insert %d to port %d index %d\n", value, port, last_inserted_value_index); //for_release

	return MECHANISM_SUCCESS;
}


mechanism_results release_server(struct server_mechanism* server)
{
	if (!server) {
		return MECHANISM_NULL_POINTER;
	}
	if (!(server->ports)) {
		free(server);
		return MECHANISM_SUCCESS;
	}

	int port;
	for (port = 0; port < server->num_of_ports; port++) {
		free(server->ports[port].indexes);
		free(server->ports[port].segment_data);
	}
	free(server->ports);
	free(server);
	return MECHANISM_SUCCESS;
}

static mechanism_results merge_k_check_aux(server_port_node* port_to_merge,
	int* indexes, int k, int index_end)
{
	if (!port_to_merge || !indexes) {
		return MECHANISM_NULL_POINTER;
	}

	if (!(port_to_merge->indexes) || !(port_to_merge->segment_data)) {
		return MECHANISM_NULL_POINTER;
	}

	if (k < 1 || k > port_to_merge->num_of_runs) {
		return MECHANISM_SEGMENT_OUT_OF_INDEXES;
	}

	if (index_end < 0 || index_end >= port_to_merge->current_size_of_segment) {
		return MECHANISM_SEGMENT_OUT_OF_INDEXES;
	}

	return MECHANISM_SUCCESS;
}

int pop_next_value(int* data_array, int* indexes, int* index_aux_array, int k)
{
	if (!data_array || !indexes || !index_aux_array || k <= 0 ) {
		return -1;
	}
	int flag_local = 1;
	int current_min;
	int index_of_run_with_min_val = 0;
	int i, current_run_index, current_value;
	for (i = 0; i < k; i++) {
		current_run_index = indexes[i];
		if (current_run_index > index_aux_array[i]) {
//			printf("\n i run is over: %d", i);
			continue;
		}

		if (flag_local) {
			current_min = data_array[current_run_index];
			flag_local = 0;
//			printf("\npop next value init_current_min: %d, current_run_index: %d, i: %d\n", current_min, current_run_index, i);
		}
		current_value = data_array[current_run_index];
//		printf("\nrun: %d, current idx: %d, current val: %d\n", i, current_run_index, current_value); //for_release
		if (current_value <= current_min) {
			current_min = current_value;
			index_of_run_with_min_val = i;
		}
	}
	indexes[index_of_run_with_min_val]++;
//	printf("\n\n\nAAA\n\n\n");
//	printf("\npop next value current min: %d, current_run_index: %d, index_of_run_with_min_val: %d\n", current_min, current_run_index, index_of_run_with_min_val); //for_release
/*	if (current_min == MAX_INT) {
		printf("\n\n\nit's happening!\n\n\n");
	}*/
	return current_min;
}

mechanism_results merge_k(server_port_node* port_to_merge,
	int* indexes, int k, int index_end_of_last_run)
{
//	printf("\nStart merge_k\n");//for_release
	mechanism_results check_res = merge_k_check_aux(port_to_merge,
		indexes, k, index_end_of_last_run);
	if (check_res != MECHANISM_SUCCESS) {
		return check_res;
	}
	
	if (k == 1) {
		return MECHANISM_SUCCESS;
	}

	int index_start_of_first_run = indexes[0];
	int* aux_array =
		(int*)malloc(sizeof(int) * port_to_merge->current_size_of_segment);
	if (!aux_array) {
		return MECHANISM_ALLOC_FAILED;
	}

	int* index_aux_array =
		(int*)malloc(sizeof(int) * k);
	if (!index_aux_array) {
		free(aux_array);
		return MECHANISM_ALLOC_FAILED;
	}
	int i;
//	printf("\nindexes:\n");
//	for (i = 0; i < k; i++) {
//		printf("%d, ", indexes[i]);
//	} //for_release


//	printf("\nindex_aux_array:\n"); //for_release
	for (i = 0; i < k-1; i++) {
		index_aux_array[i] = indexes[i+1] - 1;
	}

	index_aux_array[k-1] = index_end_of_last_run;
	/*for (i = 0; i < k; i++) {
		printf("%d, ", index_aux_array[i]);
	}*///for_release
	
	//printf("\nmerge_k aux_array index end of last run: %d:\n", index_end_of_last_run);
	 //for_release
	int num_of_values_in_iteration = index_end_of_last_run - index_start_of_first_run + 1;
	for (i = 0; i < num_of_values_in_iteration; i++) {
		aux_array[i] = pop_next_value(port_to_merge->segment_data, indexes, index_aux_array, k);
	}
/*	printf("\nmerge_k aux_array:\n");
	printf("\naux_array:\n");
	for (i = 0; i < num_of_values_in_iteration; i++) {
		printf("%d, ", aux_array[i]);
	}
	printf("\n\n");*/ //for_release
	memcpy((port_to_merge->segment_data) + index_start_of_first_run, aux_array,
		(index_end_of_last_run - index_start_of_first_run + 1) * sizeof(int));
/*	printf("\nsegment data:\n");
	for (i = 0; i <= 1000; i++) {
		printf("The %d'th is %d\n", i, port_to_merge->segment_data[i]);
	}
	printf("\nEnd segment data\n");*/

	free(index_aux_array);
	free(aux_array);
//	printf("\nEnd merge_k\n"); //for_release
	return MECHANISM_SUCCESS;
}

mechanism_results merge_iteration(server_port_node* port_to_merge, int port_num, int k)
{
	//one iteration
//	printf("\nmerge_iteration:\n"); //for_release
	if (!port_to_merge) {
		return MECHANISM_NULL_POINTER;
	}
	int current_index = 0;
	int original_num_of_runs = port_to_merge->num_of_runs;
	int num_of_merged_runs, i;
	mechanism_results res;

	for (num_of_merged_runs = 0; num_of_merged_runs < original_num_of_runs;) {
		int remainder = original_num_of_runs - num_of_merged_runs;
		int size_of_current_indexes_array = remainder >= k ? k : remainder;
		int index_end_of_last_run;
		int* indexes_array = (int*)malloc(size_of_current_indexes_array * sizeof(int));

		if (!indexes_array) {
			return MECHANISM_NULL_POINTER;
		}

		if (remainder > k) {
			index_end_of_last_run = ((port_to_merge->indexes[num_of_merged_runs + k]) - 1);
		//	printf("\n1 index_end_of_last_run: %d", index_end_of_last_run); //for_release
		}//TODO:CHECK
		else {
			index_end_of_last_run = port_to_merge->last_inserted_value_index;
		//	printf("\n2 index_end_of_last_run: %d\n", index_end_of_last_run); //for_release
		}

		for (i = 0; i < size_of_current_indexes_array; i++) {
			indexes_array[i] = port_to_merge->indexes[num_of_merged_runs + i];
			//printf("\nport_to_merge->indexes[num_of_merged_runs + %d]: %d\n", i, port_to_merge->indexes[num_of_merged_runs + i]);
			//printf("\nindexes_array[%d]: %d\n", i, indexes_array[i]);
			//printf("\nnum_of_merged_runs: %d i: %d, num_of_merged_runs + i: %d\n", num_of_merged_runs, i, num_of_merged_runs + i); //for_release
		}
		
		//TODO:CHECK

/*		printf("\nmerge_iteration before:\n");
		for (i = 0; i < port_to_merge->last_inserted_value_index; i++) {
			printf("port: %d, index: %d, value: %d\n", port_num, i, port_to_merge->segment_data[i]);
		}*/

		res = merge_k(port_to_merge, indexes_array, size_of_current_indexes_array, index_end_of_last_run);
		if (res != MECHANISM_SUCCESS) {
			free(indexes_array);
			return res;
		}
/*		printf("\nmerge_iteration after:\n");

		for (i = 0; i < port_to_merge->last_inserted_value_index; i++) {
			
			printf("222port: %d, index: %d, value: %d\n", port_num, i, port_to_merge->segment_data[i]);
		}*/

		free(indexes_array); //TODO: allocate and free outside loop
		port_to_merge->num_of_runs -= (size_of_current_indexes_array - 1);
		num_of_merged_runs += size_of_current_indexes_array;

  	}

//	int updated_num_of_runs = (original_num_of_runs / k) + ((original_num_of_runs % k) == 0 ? 0 : 1);
	int* updated_indexes_array = (int*)malloc(port_to_merge->num_of_runs * sizeof(int));
	if (!updated_indexes_array) {
		return MECHANISM_NULL_POINTER;
	}

	for (i = 0; i < port_to_merge->num_of_runs; i++) {
		updated_indexes_array[i] = port_to_merge->indexes[i * k];
	}

//	printf("indexes: %d", port_to_merge->indexes[0]); //for_release

//	printf("\nSTART FREE CHECK\n");
//	fflush(stdout);
	if (flag != 0) {
		free(port_to_merge->indexes); //FIX THE MEMORY LEAK
	}
	else {
		flag = 1;
	}
//	printf("\nEND FREE CHECK\n");
//	fflush(stdout);
	port_to_merge->indexes = updated_indexes_array;
	port_to_merge->current_size_of_indexes_array = port_to_merge->num_of_runs;
//	printf("\nend merge iteration"); //for_release
	return MECHANISM_SUCCESS;
}

mechanism_results merge_sort_port(server_port_node* port_to_merge, int port_num, int k)
{	
	if (!port_to_merge) {
		return MECHANISM_NULL_POINTER;
	}

	if (k < 2) {
		return MECHANISM_NO_ACTION; //TODO: find a better error code.
	}

	mechanism_results res = MECHANISM_SUCCESS;
	while (port_to_merge->num_of_runs > 1) {
		res = merge_iteration(port_to_merge, port_num, k);
		if (res != MECHANISM_SUCCESS) {
			return res;
		}
	}

//	printf("\n Merge_sort_port:\n"); //for_release

	//int i;
	//for (i = 0; i <= port_to_merge->last_inserted_value_index; i++) {
	//	printf("port %d, the %d value is %d\n",port_num , i, port_to_merge->segment_data[i]);
	//} //for_release

	return res;
}

mechanism_results merge_sort(server_mechanism* server, int* output_array, int k,
	int* size)
{
	clock_t start, end;
	double cpu_time_used;

	printf("\nMerge_sort start measure time...\n");//for_release
	start = clock();
	if (!server) {
		return MECHANISM_NULL_POINTER;
	}

	if (!server->ports) {
		return MECHANISM_NULL_POINTER;
	}

	int i;

	//for (i = 0; i < server->num_of_ports; i++) {
	////	printf("size: %d\n", size_of_output_array);
	//	size_of_output_array += server->ports[i].last_inserted_value_index + 1;
	////	printf("size: %d\n", size_of_output_array);
	////	printf("server->ports[%d].last_inserted_value_index: %d\n",i, server->ports[i].last_inserted_value_index);
	//} //for_release

	//*size = size_of_output_array;
	//int* temp_array = (int*)malloc(sizeof(int) * size_of_output_array);
	//printf("\n\n1\n");
	//*output_array = temp_array;
	int j;
	int iter = 0;
	mechanism_results res;
	for (int i = 0; i < server->num_of_ports; i++) {
		flag = 0;
		res = merge_sort_port(&(server->ports[i]), i, k);
		if (res != MECHANISM_SUCCESS) {
			return res;
		}
	//	printf("\n Merge_sort:\n"); //for_release
		memcpy((output_array) + iter, server->ports[i].segment_data,
			(server->ports[i].last_inserted_value_index + 1) * sizeof(int));

		for (j = 0; j <= server->ports[i].last_inserted_value_index; j++) {
	//		printf("port %d, the %d value is %d\n", i, j, (*output_array + iter)[j]);
		} //for_release
		iter += server->ports[i].last_inserted_value_index + 1;

	}
	//printf("\n\n2\n");

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nMerge sort cpu time is: %lf\n", cpu_time_used);
	return MECHANISM_SUCCESS;
}

mechanism_results mechanism_apply_server_flow(int run_id, int num_of_segments,
	int segment_lenght, int k, char* input_files_directory, char* output_prefix_name)
{
	//printf("Server is running now\n");
	if (!input_files_directory) {
		return MECHANISM_NULL_POINTER;
	}

	int port;
	server_mechanism* server = server_mechanism_init(num_of_segments);
	if (!server) {
		return MECHANISM_ALLOC_FAILED;
	}

	FILE* fp = NULL;
	FILE* output_file = NULL;

	char* segment_input_file = (char*)malloc(sizeof(char) * (strlen(input_files_directory) + 60));
	if (!segment_input_file) {
		return MECHANISM_ALLOC_FAILED;
	}
	//char segment_prefix_name[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Server_files\\merged_output_file_";
	char* merged_file_output_name = (char*)malloc(sizeof(char) * (strlen(output_prefix_name) + 50));
	if (!merged_file_output_name) {
		free(segment_input_file);
		return MECHANISM_ALLOC_FAILED;
	}
	int* output_array = NULL;
	int size_of_output_array = 0;

	strcpy(merged_file_output_name, output_prefix_name);
	char prefix_name[] = "merged_output_file_";
	strcat(merged_file_output_name, prefix_name);
	char id[10];
	sprintf(id, "%d", run_id);
	strcat(merged_file_output_name, id);
	strcat(merged_file_output_name, "_");
	char num_of_seg[10];
	sprintf(num_of_seg, "%d", num_of_segments);
	strcat(merged_file_output_name, num_of_seg);
	char len_of_seg[10];
	sprintf(len_of_seg, "%d", segment_lenght);
	strcat(merged_file_output_name, "_");
	strcat(merged_file_output_name, len_of_seg);
	strcat(merged_file_output_name, ".txt");
//	printf("\n\n%s\n\n", merged_file_output_name); //for_release
	output_file = fopen(merged_file_output_name, "w+");

	for (port = 0; port < num_of_segments; port++) {
		strcpy(segment_input_file, input_files_directory);

		char prefix_name[] = "switch_output_file_";
		strcat(segment_input_file, prefix_name);

		char id[10];
		sprintf(id, "%d", run_id);

		strcat(segment_input_file, id);
		strcat(segment_input_file, "_");
		char index[10];
		sprintf(index, "%d", port);
		strcat(segment_input_file, index);
		char num_of_seg[10];
		sprintf(num_of_seg, "%d", num_of_segments);
		strcat(segment_input_file, "_");
		strcat(segment_input_file, num_of_seg);
		char len_of_seg[10];
		sprintf(len_of_seg, "%d", segment_lenght);
		strcat(segment_input_file, "_");
		strcat(segment_input_file, len_of_seg);
		strcat(segment_input_file, ".txt");
		fp = fopen(segment_input_file, "r");
//		printf("\n%s\n", segment_output_file);
//		printf("port iss: %d", port);
		mechanism_server_insert_data_from_files(server, port, fp);
		fclose(fp);
	}
	
	//if (!(output_array)) {
	//	return MECHANISM_ALLOC_FAILED;
	//}
	int i = 0;
	for (i = 0; i < server->num_of_ports; i++) {
		//	printf("size: %d\n", size_of_output_array);
		size_of_output_array += server->ports[i].last_inserted_value_index + 1;
		//	printf("size: %d\n", size_of_output_array);
		//	printf("server->ports[%d].last_inserted_value_index: %d\n",i, server->ports[i].last_inserted_value_index);
	}
	//printf("\n\n11\n");

	output_array = (int*)malloc(sizeof(int) * size_of_output_array);

	merge_sort(server, output_array, k, &size_of_output_array);
//	//printf("\nmerge sort pass\n"); //for_release
	//printf("\n\n21\n");

	convert_array_to_output_file(output_array, size_of_output_array, output_file);
	fclose(output_file);
	//printf("\n\n31\n");
	if (output_array) {
		printf("\nfree output array\n\n");
		free(output_array);
	}
	//printf("\n\n41\n");

	free(segment_input_file);
	free(merged_file_output_name);

	release_server(server);

	return MECHANISM_SUCCESS;
}

mechanism_results mechanism_server_insert_data_from_files(server_mechanism* server, int port, FILE* fp)
{

	if (!server || !fp) {
		return MECHANISM_NULL_POINTER;
	}
	int output_port;
	int output_value;
	char value_str_from_file[10];
	int value_to_insert;

	while (fgets(value_str_from_file, 10, fp) != NULL) {
		value_to_insert = atoi(value_str_from_file);
		server_insert(server, port, value_to_insert);
		}
	return MECHANISM_SUCCESS;
}

mechanism_results convert_array_to_output_file(int* output_array, int size_of_output_array, FILE* output_file)
{
	if (!output_array || !output_file) {
		return MECHANISM_NULL_POINTER;
	}

	int i;
	char temp[10];
	for (i = 0; i < size_of_output_array; i++) {
		sprintf(temp, "%d", output_array[i]);

		fputs(temp, output_file);
		fputs("\n", output_file);
	}

	return MECHANISM_SUCCESS;
}