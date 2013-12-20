
#ifndef __HADL_ARRAY__
#define __HADL_ARRAY__

/**
 * \file hadl-array.h
 * 
 * Array type.
 *
 * Arrays are used to model memory components.
 * They have no definite size, but are allocated by "segments" when needed, i.e. when writing to a previously unallocated index.
 * Segment size is given by the symbolic constant HADL_SEG_SIZE defined in file hadl-custom.h.
 *
 * An array is organized as a tree of segments: the path to a given segment will be longer if the index of the cell to access is bigger.
 * The path is calculated based on the index value, decomposed into a set of fields, each of which gives the index of a child node in
 * the tree.
 * Parameters for path calculations are defined in hadl-custom.h :
 *    - HADL_ADDR_WIDTH is the address width, in bits
 *    - HADL_ADDR_SUBDIV is the number of bits per field in path calculation
 *
 * Each cell of a segment is a linked list, each node of which contains the following information :
 *    - status: defined (already written) / undefined (never written before)
 *    - value
 *    - time of data availability for this value
 *
 * Time of availability is defined as : time of write operation + 1.
 */

#include "hadl-custom.h"

/**
 * Array type.
 */
typedef void** HADL_Array_t;

static HADL_Array_t* HADL_Array_new();

template<class T, class D>
static D HADL_Array_getValue(HADL_Array_t *array, int index, HADL_Time_t *time);

template<class T>
static void HADL_Array_setValue(HADL_Array_t *array, int index, T value, HADL_Time_t *time);

template<class T, class D>
static void HADL_Array_setField(HADL_Array_t *array, int index, D value, int r[][3], int n, HADL_Time_t *time);

template<class T>
static void HADL_Array_print(HADL_Array_t *array);

// Include .cpp for template instantiation
#include "hadl-array.cpp"

#endif

