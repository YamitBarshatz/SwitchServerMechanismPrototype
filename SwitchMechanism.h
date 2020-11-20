#pragma once
/* Switch */

/* HEADER */
/*
 * Switch Mechanism Prototype
 * Brief:
 * Yamit Barshatz
 */

/*
 * Includes
 */
#include "TypesMechanism.h"

/*
 * Enumerations
 */
//typedef enum mechanism_switch_results {

//} mechanism_switch_results;

/*
 * Structs
 */

/*
 * Switch segment node
 * Brief:	This struct manages segment's data.
 * Fields:	start & end				: Segment range.
 * Field:	size					: Segment size.
 * Field:	data_flow				: An array that stores the dinamic data (simulets one pipeline row in the switch memory).
 */
typedef struct switch_segment_node {
    int start;
    int end;
    int size;
    int first_size_values_cnt;
    int* data_flow;
    int partition_index;
 //   int current_start;
 //   int last_right_val;
  //  int last_left_val
} switch_segment_node;

/*
 * Switch mechanism
 * Brief:	This struct manages mechanism's segments at the switch side.
 * Field:	size					: Number of segments (pipes in the switch memory).
 * Field:	max_value				: Maximum value in flow.
 * Field:	segments				: An array of all segments (simultes the whole memory in the switch, parted into segments).
 */
typedef struct switch_mechanism {
    int num_of_segments;
    int max_value;
    switch_segment_node* segments;
} switch_mechanism;

/*
 * Switch API
 */

 /*
  * Function: switch_mechanism_init.
  * Brief:	Sets default ranges for each segment.
  * Field:	num_of_segments			: Number of segments.
  * Field:	segment_length			: Segment's length.
  * Field:	max_value				: Maximum value in flow.
  * Return:	Switch mechanism pointer.
  */
switch_mechanism* switch_mechanism_init(
    int num_of_segments,
    int segment_length,
    int max_value);
/*
 * Function: switch_mechanism_set_ranges_default.
 * Brief:	Sets default ranges for each segment.
 * Field:	s						: Switch mechanism structure.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 */
mechanism_results switch_mechanism_set_ranges_default(switch_mechanism* s);

/*
 * Function: switch_find_next_segment_and_index.
 * Brief:	Calculates the segment and the index to insert next value.
 * Field:	s						: Switch mechanism structure.
 * Field:	input					: Dedicated value.
 * Field:	segment					: Return field - segment of dedicated value.
 * Field:	index					: Return field - index of dedicated value.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 *									: MECHANISM_SEGMENT_OUT_OF_INDEXES.
 */
int switch_find_next_segment_and_index(
    struct switch_mechanism* s,
    int input,
    int* segment,
    int* index);

/*
 * Function: switch_insert_value_to_segment.
 * Brief:	Inserts value to specific segment and index (Uses switch_insert_next function described below).
 * Field:	s						: Switch mechanism structure.
 * Field:	segment					: Segment of dedicated value.
 * Field:	index					: Index of dedicated value.
 * Field:	value					: Dedicated value.
 * Field:	output					: Omitted value.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 */
int switch_insert_value_to_segment(
    struct switch_mechanism* s,
    int segment,
    int index,
    int value,
    int* output);

/*
 * Function: switch_insert_next.
 * Brief:	Insert next value - should be a static function.
 * Field:	s						: Switch mechanism structure.
 * Field:	input					: Dedicated value.
 * Field:	output_port				: Return field - dedicated port of output value.
 * Field:	output_value			: Return field - output value.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 *									: Mechanism result.
 */
int switch_insert_next(
    struct switch_mechanism* s,
    int input,
    int* output_port,
    int* output_value);
//TODO: Add description
mechanism_results release_segment_data(struct switch_segment_node* segment);
mechanism_results release_switch(struct switch_mechanism* s);


mechanism_results mehcanism_apply_switch_flow(int run_id, int num_of_segments,
    int segment_lenght, FILE* input_file, char* segment_prefix_name, int maximum_value);
/* End of Switch API */

mechanism_results mechanism_switch_flow(int num_of_segments, int segment_lenght,
    FILE* input_file, FILE** output_files, int maximum_value);