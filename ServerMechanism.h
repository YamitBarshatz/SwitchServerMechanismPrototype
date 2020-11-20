#pragma once
/* Server */

/* HEADER */
/*
 * Server Mechanism Prototype
 * Brief:
 * Yamit Barshatz
 */

/*
 * Includes
 */
#include "TypesMechanism.h"

/*
 * Definitions
 */
#define INIT_SERVER_SEGMENT_SIZE 1000
#define INIT_SERVER_INDEXES_SIZE 1000

/*
 * Enumerations
 */
//typedef enum mechanism_server_results {
//
//} mechanism_server_results;

/*
 * Structs
 */

/* Server */
/*
 * Server port node
 * Brief:	This struct manages port's data in the server.
 * Fields:	current_size_of_segment				: Segment range.
 * Field:	current_size_of_indexes_array		: Segment size.
 * Field:	last_inserted_value_index			: The index in segment_data array of the last value that has been inserted.
 * Field:	num_of_runs							: Stores the number of runs in the port.
 * Field:	indexes								: The value of the i'th cell tells in which index the i'th run starts.
 * Field:	segment_data						: An array that stores the data from specific segment.
 */

typedef struct server_port_node {
    int current_size_of_segment;
    int current_size_of_indexes_array;
    int num_of_runs;
    int last_inserted_value_index;
    int* indexes;
    int* segment_data;
} server_port_node;


/*
 * Server mechanism
 * Brief:	This struct manages mechanism's ports (segments) at the server side.
 * Field:	num_of_ports			: Number of ports (segments) (pipes in the switch memory).
 * Field:	ports					: An array of all ports.
 */

typedef struct server_mechanism {
    int num_of_ports;
    server_port_node* ports;
} server_mechanism;

/* Server API */
//TODO:ADD DESCRIPTION
server_mechanism* server_mechanism_init(int num_of_ports);
mechanism_results server_insert(server_mechanism* server_side, int port, int value);
mechanism_results release_server(server_mechanism* server);

mechanism_results merge_k(server_port_node* port_to_merge,
    int* indexes, int k, int index_end_of_last_run);
mechanism_results merge_iteration(server_port_node* port_to_merge, int port_num, int k);
mechanism_results merge_sort_port(server_port_node* port_to_merge, int port_num, int k);
//merge_sort (with memcpy)
mechanism_results merge_sort(server_mechanism* server, int** output_array, int k, int* size);
//static functions
int pop_next_value(int* data_array, int* indexes, int* index_aux_array, int k);

mechanism_results mechanism_apply_server_flow(int run_id, int num_of_segments,
    int segment_lenght, int k, char* input_files_directory, char* segment_prefix_name);