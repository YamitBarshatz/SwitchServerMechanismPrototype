#include "GeneralMechanism.h"
/* Source */
/* General Mechanism API */
int mechanism_insert(
	struct switch_mechanism* s,
	struct server_mechanism* server_side,
	int input,
	int* output_port,
	int* output_value)
{
	mechanism_results result;

	if (!s || !server_side) {
		printf("\nServer NULL.\n");
		return MECHANISM_NULL_POINTER;
	}

	result = switch_insert_next(s, input, output_port, output_value);
	if (result != MECHANISM_SUCCESS) {
		return MEACHNISM_GENERAL_FAILURE;
	}
	if (output_value != INIT_VALUE) {
		printf("\nServer action port %d value %d.\n", *output_port, *output_value);
		result = server_insert(server_side, *output_port, *output_value);
		if (result != MECHANISM_SUCCESS) {
			return MEACHNISM_GENERAL_FAILURE;
		}
	}
	else {
		printf("\nSegment not full\n");
	}

	return MECHANISM_SUCCESS;
}

mechanism_results mechanism_finish_operation(
	switch_mechanism* s,
	server_mechanism* server_side)
{
	mechanism_results result;
	int port;
	int i;

	if (!s || !server_side) {
		printf("\nServer NULL.\n");
		return MECHANISM_NULL_POINTER;
	}

	for (port = 0; port < s->num_of_segments; port++) {
		for (i = 0; i < s->segments[port].size; i++) {
			printf("\nport: %d, value: %d", port, s->segments[port].data_flow[i]);
			result = server_insert(server_side, port, s->segments[port].data_flow[i]);
			if (result != MECHANISM_SUCCESS) {
				return MEACHNISM_GENERAL_FAILURE;
			}
			printf("\n");
		}
	}

	return MECHANISM_SUCCESS;
}

/*mechanism_results mechanism_full_flow(
	struct switch_mechanism* s,
	struct server_mechanism* server_side,
	int input,
	int* output_port,
	int* output_value)
{

}*/
