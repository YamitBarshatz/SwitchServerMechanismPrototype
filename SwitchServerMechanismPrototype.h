/* 
 * Switch - Server Mechanism Prototype
 * Breif:
 * Yamit Barshatz
 */

#include <stdio.h>

/* Switch range node */
struct switch_segment_node {
    int start;
    int end;
    int size;
    int *data_flow;
};

/* Switch data base */
struct switch_mechanism {
    int size;
    struct switch_segment_node *data_mechanism;
};

/* Switch API */
struct switch_mechanis* switch_mechanism_init(int num_of_segments, int segment_length);
int switch_mechanism_set_ranges_default(struct switch_mechanis* switch);