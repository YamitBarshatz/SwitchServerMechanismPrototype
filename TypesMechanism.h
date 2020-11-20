#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_VALUE (-1)
typedef enum mechanism_results {
	MECHANISM_SUCCESS,
	MEACHNISM_GENERAL_FAILURE,
	MECHANISM_NULL_POINTER,
	MECHANISM_SEGMENT_OUT_OF_INDEXES,
	MECHANISM_PORT_NOT_MATCH,
	MECHANISM_ALLOC_FAILED,
	MECHANISM_NO_ACTION,
	MECHANISM_FILE_NOT_EXISTS

} mechanism_results;


