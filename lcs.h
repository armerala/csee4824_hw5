#ifndef __LCS_H__
#define __LCS_H__

#include <stddef.h>
#include <stdio.h>

/**
 * A structure to hold a cache object
 */
typedef struct {
	int value;     // lcs table value
	int came_from; // previous index in the sequence
}cache_entry;

extern void lcs_no_branching(char* a, char* b, cache_entry* cache, size_t m, size_t n);

#endif //__LCS_H__
