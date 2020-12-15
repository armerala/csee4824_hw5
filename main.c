#include <stdio.h>
#include <stdlib.h>

#define LH_SEQ_LENGTH 4096 // bytes
#define RH_SEQ_LENGTH 4096 // bytes

int main(void) 
{
	// alloc buffers
	char* lh_seq = (char*) malloc(sizeof(char) * LH_SEQ_LENGTH);
	char* rh_seq = (char*) malloc(sizeof(char) * RH_SEQ_LENGTH);

	printf("Left-hand sequence length:  %i \n", LH_SEQ_LENGTH);
	printf("Right-hand sequence length: %i \n", RH_SEQ_LENGTH);

	// clean up
	free(lh_seq);
	free(rh_seq);
	return 0;
}
