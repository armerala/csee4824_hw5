#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcs.h"

/**
 * Prints the cache out in a for debug
 */
void print_cache(cache_entry* cache, size_t rows, size_t cols)
{
	int i,j;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%i,", cache[i * rows + j].value);
		}
		printf("\n");
	}
}

int main(int argc, char** argv) 
{
	FILE *lh_fp, *rh_fp;
	char *lh_buf, *rh_buf;
	size_t lh_size, rh_size;

	size_t cache_size;
	cache_entry* cache;

	// open input files
	// note, we assume txt files are already null-terminated
	if(argc != 3)
	{
		printf("usage: lcs <sequence file 1>.txt <sequence file 2>.txt\n");
		return -1;
	}

	lh_fp = fopen(*(argv + 1), "rb");
	rh_fp = fopen(*(argv + 2), "rb");

	if(lh_fp == NULL || rh_fp == NULL)
	{
		perror("Error: ");
		return -1;
	}

	// get sizes & rewind
	fseek(lh_fp, 0, SEEK_END);
	fseek(rh_fp, 0, SEEK_END);

	lh_size = ftell(lh_fp);
	rh_size = ftell(rh_fp);

	fseek(lh_fp, 0, SEEK_SET);
	fseek(rh_fp, 0, SEEK_SET);

	printf("Left-hand sequence length:  %lu \n", lh_size - 1);
	printf("Right-hand sequence length: %lu \n", rh_size - 1);

	// alloc buffers, read contents, close files
	lh_buf = (char*) malloc(sizeof(char) * lh_size);
	rh_buf = (char*) malloc(sizeof(char) * rh_size);

	cache_size = lh_size * rh_size * sizeof(cache_entry);
	cache = (cache_entry*) malloc(cache_size);
	memset((void*)cache, 0, cache_size);
	
	fread(lh_buf, 1, lh_size, lh_fp);
	fread(rh_buf, 1, rh_size, rh_fp);
	lh_buf[lh_size] = '\0';
	lh_buf[rh_size] = '\0';

	printf("Left-hand sequence:  %s \n", lh_buf);
	printf("Right-hand sequence: %s \n", rh_buf);

	fclose(lh_fp);
	fclose(rh_fp);

	//run the algorithm
	lcs_no_branching(lh_buf, rh_buf, cache, lh_size-1, rh_size-1);
	print_cache(cache, lh_size-1, rh_size-1);

	// clean up
	free(lh_buf);
	free(rh_buf);
	free(cache);
	return 0;
}
