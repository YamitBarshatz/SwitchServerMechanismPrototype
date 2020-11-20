/*
#include <SwitchServerMechanismPrototype.h>
*/
/* Switch API */
/*
struct switch_mechanis* switch_mechanism_init(int num_of_segments, int segment_length)
{
	struct switch_mechanis* switch_handler = NULL;
	int i = 0;

	if (num_of_segments <= 0 || segment_length <= 0) {
		return -1;
	}

	switch_handler = (struct switch_mechanis*)malloc(sizeof(struct switch_mechanism));
	if (!switch_handler) {
		return NULL;
	}

	printf("\nSwitch mechanism allocated.\n");

	switch_handler->size = num_of_segments;
	switch_handler->switch_segment_node = (struct switch_segment_node*)malloc(sizeof(struct switch_segment_node) * num_of_segments);
	if (!switch_handler->switch_segment_node) {
		free(switch_handler);
		return NULL;
	}

	printf("\nSwitch segments allocated.\n");

	for (i = 0; i < num_of_segments; i++) {
		int start = 0;
		switch_handler->switch_segment_node[i].size = segment_length;
		switch_handler->switch_segment_node[i].data_flow = (int*)malloc(sizeof(int) * segment_length);
		if (!switch_handler->switch_segment_node[i].data_flow) {
			int j = 0;
			for (j = 0; j < i; j++) {
				free(switch_handler->switch_segment_node[j].data_flow);
			}
			free(switch_handler->switch_segment_node);
			free(switch_handler);
			return NULL;
		}
		switch_handler->switch_segment_node[i].start = 0;
		switch_handler->switch_segment_node[i].end = 0;
		for (start = 0; start < segment_length; start++) {
			switch_handler->switch_segment_node[i].data_flow[start] = 0;
		}
		printf("\nSwitch segment %d data allocated.\n", i);
	}

	return switch_handler;
}

int switch_mechanism_set_ranges_default(struct switch_mechanis* switch)
{
	int segment = 0;
	int current_start = 0;
	int current_end = 10;

	if (!switch) {
		return -1;
	}

	for (segment = 0; segment < switch.size; segment++) {
		switch->data_mechanism[segment].start = current_start;
		switch->data_mechanism[segment].end = current_end;
		current_start += 10;
		current_end += 10;
		printf("\nSwitch segment %d data range: [%d,%d].\n", segment, switch->data_mechanism[segment].start, switch->data_mechanism[segment].end);
	}

	return 0;
}
*/