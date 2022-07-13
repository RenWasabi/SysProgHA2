#include <stdio.h>

#include "calloc_helpers.h"

// Simple test that does a single allocation
#define MEM_SIZE (104)
MEMORY(MEM_SIZE, mem);

int main() {

	my_calloc_init(mem, MEM_SIZE);

	// Uncomment to print memory layout
	// mem_print_blocks(mem);

	char * ptr = my_calloc(10, 1, 0);
	char * expected = (((char *) mem) + sizeof(mem_block));
	printf("Expected: %p\nFound   : %p\n", expected, ptr);

	// Uncomment to print memory layout
	// mem_print_blocks(mem);

	if( expected != ptr ) {
		fprintf(stderr, "Did not match!\n");
		exit(1);
	}
}
