#pragma once
/* General */

/* HEADER */
/*
 * General Mechanism Prototype
 * Brief:
 * Yamit Barshatz
 */

/*
 * Includes
 */
#include "SwitchMechanism.h"
#include "ServerMechanism.h"

/*
 * Enumerations
 */
/*
 * Function: mechanism_insert.
 * Brief:	Inserts next value (User API that uses the above static functions)
 * Field:	s						: Switch mechanism structure.
 * Field:	server_side				: Server mechanism structure.
 * Field:	input					: Dedicated value.
 * Field:	output_port				: Return field - dedicated port of output value.
 * Field:	value					: Return field - dedicated value.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 *									: MEACHNISM_GENERAL_FAILURE.
 */
int mechanism_insert(
    struct switch_mechanism* s,
    struct server_mechanism* server_side,
    int input,
    int* output_port,
    int* output_value);

/*
 * Function: mechanism_finish_operation.
 * Brief:	After the input stream ends, extracts all the remained values in the switch memory to the server.
 * Field:	s						: Switch mechanism structure.
 * Field:	server_side				: Server mechanism structure.
 * Return:	Success					: MECHANISM_SUCCESS.
 *			Failure					: MECHANISM_NULL_POINTER.
 *									: MEACHNISM_GENERAL_FAILURE.
 */
mechanism_results mechanism_finish_operation(
    switch_mechanism* s,
    server_mechanism* server_side);