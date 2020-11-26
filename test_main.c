#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include "GeneralMechanism.h"
#include <assert.h>
#include <time.h>
#define MAX_INT 2147483647
typedef enum test_rusults {
	TEST_SUCCESS,
	TEST_FAILURE
} test_results;

test_results test_server_mechanism_init(int num_of_port)
{
	printf("test_server_mechanism_init starts:\n");
	server_mechanism* server = server_mechanism_init(num_of_port);
	if (!server) {
		return TEST_FAILURE;
	}
	mechanism_results res = release_server(server);
	if (res != MECHANISM_SUCCESS) {
		return TEST_FAILURE;
	}
	printf("test_server_mechanism_init ends:\n");
	return TEST_SUCCESS;
}

test_results test_server_insert()
{
	int i, j;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(100);
	for (i = 0; i < 100; i++) {
		for (j = 2000; j > 0; j--) {
			result = server_insert(server, i, j);
			if (result != MECHANISM_SUCCESS) {
				return MEACHNISM_GENERAL_FAILURE;
			}
		}
	}

	release_server(server);
	return TEST_SUCCESS;
}


test_results test_general_mechanism_1()
{
	int port = INIT_VALUE;
	int value = INIT_VALUE;
	int i = 0;
	int j = 0;
	enum mechanism_results result;
	struct switch_mechanism* s = NULL;
	struct server_mechanism* server_side = NULL;

	server_side = server_mechanism_init(5);
	s = switch_mechanism_init(5, 10, MAX_INT);
	switch_mechanism_set_ranges_default(s);

	for (i = 6; i < 50;) {
		for (j = 0; j < 10; j++) {
			result = mechanism_insert(s, server_side, i, &port, &value);
			if (result != MECHANISM_SUCCESS) {
				return TEST_FAILURE;
			}
		}
		i += 10;
	}

	for (i = 0; i < 50; i++) {
		result = mechanism_insert(s, server_side, i, &port, &value);
		if (result != MECHANISM_SUCCESS) {
			return TEST_FAILURE;
		}
	}

	result = mechanism_finish_operation(s, server_side);
	if (result != MECHANISM_SUCCESS) {
		return TEST_FAILURE;
	}

	release_switch(s);
	release_server(server_side);
	return TEST_SUCCESS;
}

//server

test_results test_pop_next_value(int k)
{
	int data_array[15] = { 9, 10, 11,
							2, 4,
							7, 10,
							8,
							1, 2, 3, 4,
							5, 8, 10 };
	int indexes[10] = { 0, 3, 5, 7, 8, 12 };
	int index_aux_array[10] = { 2, 4, 6, 7, 11, 14 };
	int partial_sorted_array[15] = { -1 };
	int i;
//	int min = pop_next_value(data_array, indexes, index_aux_array, k);
	for (i = 0; i < 15; i++) {
		partial_sorted_array[i] = pop_next_value(data_array, indexes, index_aux_array, k);
	}
	printf("\n");
	for (i = 0; i < 15; i++) {
		printf("%d, ", partial_sorted_array[i]);
	}
//	printf("\n The minimun is: %d", min);
//	if (min == -1) {
//		return TEST_FAILURE;
//	}
	return TEST_SUCCESS;
}

test_results test_merge_k()
{
	int i;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(1);

	for (i = 10; i > 0; i--) {
		result = server_insert(server, 0, i);
		if (result != MECHANISM_SUCCESS) {
			return MEACHNISM_GENERAL_FAILURE;
		}
	}

	printf("\nOriginal array: \n");
	for (i = 0; i < 10; i++) {
		printf("%d, ", server->ports[0].segment_data[i]);
	}
	printf("\n\n Hi \n");

	printf("\nindexes:\n");
	for (i = 0; i < 10; i++) {
		printf("%d, ", server->ports[0].indexes[i]);
	}
	printf("\n");
	result = merge_k(&(server->ports[0]), server->ports[0].indexes, 10, server->ports[0].last_inserted_value_index);
	
	printf("\nhello\n");
	for (i = 0; i < 10; i++) {
		printf("%d, ", server->ports[0].segment_data[i]);
	}

	release_server(server);
	return TEST_SUCCESS;
}

test_results test_merge_iteration()
{
	int i;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(1);

	for (i = 10; i > 0; i--) {
		result = server_insert(server, 0, i);
		if (result != MECHANISM_SUCCESS) {
			return MEACHNISM_GENERAL_FAILURE;
		}
	}
	result = merge_iteration(&(server->ports[0]), 0, 2);

	printf("\nmerge_iteration_array:\n");
	for (i = 0; i < 10; i++) {
		printf("%d, ", server->ports[0].segment_data[i]);
	}
	printf("\n\n");
	release_server(server);
	return TEST_SUCCESS;
}

test_results test_merge_sort_port()
{
	int i;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(2);

	printf("\n\n Hi \n");

	for (i = 10; i > 0; i--) {
		result = server_insert(server, 0, i);
		if (result != MECHANISM_SUCCESS) {
			return MEACHNISM_GENERAL_FAILURE;
		}
	}

	/*int data_array[15] = { 9, 10, 11,
						2, 4,
						7, 10,
						8,
						1, 2, 3, 4,
						5, 8, 10 };*/
	result = merge_sort_port(&(server->ports[0]), 0, 3);

	printf("\ntest_merge_sort_port array:\n");
	for (i = 0; i < 10; i++) {
		printf("%d, ", server->ports[0].segment_data[i]);
	}

	return TEST_SUCCESS;
}

test_results test_merge_sort_port_2()
{
	int i;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(1);

	for (i = 1000; i >= 0; i--) {
		result = server_insert(server, 0, i);
		if (result != MECHANISM_SUCCESS) {
			return MEACHNISM_GENERAL_FAILURE;
		}
	}

	result = merge_sort_port(&(server->ports[0]), 0, 100);
//	printf("\nresult is: %d:\n", result);
	printf("\ntest_merge_sort_port array:\n");
	for (i = 0; i <= 1000; i++) {
		printf("The %d'th is %d\n", i, server->ports[0].segment_data[i]);
	}

	release_server(server); 
	return TEST_SUCCESS;
}

test_results test_merge_sort()
{
	int i, j;
	mechanism_results result;
	server_mechanism* server = server_mechanism_init(100);
	for (i = 0; i < 10; i++) {
		for (j = (i+1) * 1000; j > i * 1000; j--) {
			result = server_insert(server, i, j);
			if (result != MECHANISM_SUCCESS) {
				return MEACHNISM_GENERAL_FAILURE;
			}
		}
	}
	
	int* merged_array = NULL;
	int size;
	result = merge_sort(server, &merged_array, 10, &size);
	
	if (result != MECHANISM_SUCCESS) {
		free(server);
		return TEST_FAILURE;
	}

	int size_of_merged_array = 0;

	for (i = 0; i < server->num_of_ports; i++) {
		size_of_merged_array += server->ports[i].last_inserted_value_index + 1;
	}

	for (i = 0; i < size_of_merged_array; i++) {
		printf("the %d value is %d\n", i, merged_array[i]);
	}
	for (i = 0; i < size_of_merged_array - 1; i++) {
		if (merged_array[i] > merged_array[i + 1]) {
			printf("Not sorted in line %d\n", i);
		}
//		printf("sorted\n");
	}
	release_server(server);
	return TEST_SUCCESS;
}

test_results test_mechanism_switch_flow()
{
	char input_file_name[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\test_file.txt";
	FILE* input_file = fopen(input_file_name, "r");
	FILE* output_file_1 = fopen("C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\output_1.txt", "w+");
	FILE* output_file_2 = fopen("C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\output_2.txt", "w+");
	FILE* output_files[2] = { output_file_1, output_file_2 };
	mechanism_switch_flow(2, 4, input_file, &output_files, 20);
	fclose(input_file);
	fclose(output_file_1);
	fclose(output_file_2);
	return TEST_SUCCESS;
}

test_results test_mechanism_apply_switch_flow()
{

}

test_results test_read_file()
{
	char input_file_name[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\test_file.txt";
	FILE* input_file = fopen(input_file_name, "r");
	char values[10];
	while (fgets(values, 10, input_file) != NULL) {
		printf("reading file hello %s\n", values);
	}
	fclose(input_file);
	printf("file end\n");
	return TEST_SUCCESS;
}

test_results test_set_ranges_default()
{
	printf("\nhello\n");
	switch_mechanism* s = switch_mechanism_init(20, 10, 100);
	switch_mechanism_set_ranges_default(s);
	for (int segment = 0; segment < s->num_of_segments; segment++) { //TODO: set the ranges, maybe in define
	//	printf("\nSwitch segment %d data range: [%d,%d].\n", segment, s->segments[segment].start, s->segments[segment].end);
	}
	return TEST_SUCCESS;
}

test_results test_convert_array_to_output_file()
{
	char input_file_name[] = 
		"C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Server_files\\output_file.txt";
	FILE* test_file = fopen(input_file_name, "w+");
	int test_array[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	convert_array_to_output_file(test_array, 12, test_file);
	fclose(test_file);
	return TEST_SUCCESS;
}

test_results test_mechanism_server_insert_data_from_files()
{
	char input_file_name[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\test_file.txt";
	FILE* input_file = fopen(input_file_name, "r");
	server_mechanism* server = server_mechanism_init(10);
	mechanism_server_insert_data_from_files(server, 1, input_file);

	for (int i = 0; i <= server->ports[1].last_inserted_value_index; i++) {
		printf("%d\n", server->ports[1].segment_data[i]);
	}
	release_server(server);
	fclose(input_file);
	printf("file end\n");
	return TEST_SUCCESS;
}

test_results test_mechanism_apply_server_flow()
{
	char input_files_directory[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\Segments_files\\output_";
	char segment_prefix_name[] = "C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Server_files\\merged_output_file_";
	mechanism_apply_server_flow(1, 16, 16, 7, input_files_directory, segment_prefix_name);
	return TEST_SUCCESS;
}

test_results test_create_random_input()
{
	create_random_input("C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Switch_files\\test_file\\random_test_file100M.txt");
	return TEST_SUCCESS;
}


test_results test_check_if_sorted()
{
	check_if_sorted("C:\\Users\\yamit\\Desktop\\Project_Mechanism_files\\Server_files\\merged_output_file_2_20_20_10k.txt", 10000);
	return TEST_SUCCESS;
}

test_results checking_time()
{

	clock_t start, end;
	double cpu_time_used;

	start = clock();
	for (int i = 0; i < 20000000; i++);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("\n time: %lf\n", cpu_time_used);
	return TEST_SUCCESS;
}

//int main()
//{
	//	assert(test_server_mechanism_init(100) == TEST_SUCCESS);
	//	assert(test_server_mechanism_init(0) == TEST_FAILURE);
	//	assert(test_general_mechanism_1() == TEST_SUCCESS);
	//	assert(test_server_insert() == TEST_SUCCESS);
	//	assert(test_pop_next_value(1) == TEST_SUCCESS);
	//	assert(test_pop_next_value(2) == TEST_SUCCESS);
	//	assert(test_pop_next_value(3) == TEST_SUCCESS);
	//	assert(test_pop_next_value(4) == TEST_SUCCESS);
	//	assert(test_pop_next_value(5) == TEST_SUCCESS);
	//	assert(test_pop_next_value(6) == TEST_SUCCESS);
	//	assert(test_pop_next_value(7) == TEST_FAILURE); //should crash
	//	assert(test_merge_k() == TEST_SUCCESS);
	//	assert(test_merge_iteration() == TEST_SUCCESS);
	//	assert(test_merge_sort_port() == TEST_SUCCESS);
	//	assert(test_merge_sort_port_2() == TEST_SUCCESS);
	//	assert(test_merge_sort() == TEST_SUCCESS);
	//	assert(test_read_file() == TEST_SUCCESS);
	//	assert(test_mechanism_switch_flow() == TEST_SUCCESS);
	//	assert(test_mechanism_apply_switch_flow() == TEST_SUCCESS);
	//	assert(test_set_ranges_default() == TEST_SUCCESS);
	//	assert(test_convert_array_to_output_file() == TEST_SUCCESS);
	//	assert(test_mechanism_server_insert_data_from_files() == TEST_SUCCESS);
	//	assert(test_mechanism_apply_server_flow() == TEST_SUCCESS);
	//	assert(test_create_random_input() == TEST_SUCCESS);
	//	assert(test_check_if_sorted() == TEST_SUCCESS);
	//assert(checking_time() == TEST_SUCCESS);
	//End of mechanism test
//	return 0;
//}


//Todo: Free all allocations - (!!!)
//Todo: timing - compare time with and without swtich mechanism assist.
//Todo: Write desc of relese functions
//Todo: Change int to mechanism result where needed
//Todo: Change name of variables
//Todo: Add signature to al functions (server)


