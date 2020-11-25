#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include "TypesMechanism.h"


int create_random_input(char* path)
{
	FILE* fp = fopen(path, "w+");
	if (!fp) {
		return MECHANISM_NULL_POINTER;
	}
	int curr_val;
	int max_val = 0;
	char curr_val_str[10];

	for (int i = 0; i < 10000000; i++) {
		curr_val = rand();
		if (curr_val > max_val) {
			max_val = curr_val;
		}
		sprintf(curr_val_str, "%d", curr_val);
		fputs(curr_val_str, fp);
		fputs("\n", fp);
	}
	fclose(fp);
	printf("\n%d\n", max_val);
	return max_val;
}

mechanism_results check_if_sorted(char* path, int size)
{

	FILE* fp = fopen(path, "r");
	if (!fp) {
		printf("\nnWARNING ERROR!!!!\n\n");
	}
	int* temp_array = (int*)malloc(size * sizeof(int));
	char str_num[10];
	int i, flag = 1;

	for (i = 0; i < size; i++) {
		fgets(str_num, 10, fp);
		temp_array[i] = atoi(str_num);
	}

	for (i = 0; i < size - 1; i++) {
		if (temp_array[i] > temp_array[i + 1]) {
			flag = 0;
			printf("Not sorted in line %d\n", i);
		}
	}

	if (flag) {
		printf("Sorted!\n\n");
	}
	free(temp_array);
	fclose(fp);
	return MECHANISM_SUCCESS;
}