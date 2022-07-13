#include <stdio.h>

#include "calloc_helpers.h"

// Simple test that checks out of memory behavior

#define MEM_SIZE (152)
MEMORY(MEM_SIZE, mem);

int main() {

	my_calloc_init(mem, MEM_SIZE);

	void * ptr_1 = my_calloc(90, 1, 'A'); // this should work
	void * ptr_2 = my_calloc(90, 1, 'B'); // this shouldn't

	mem_print_blocks(mem);

	int error = 0;

	printf("\nFirst allocation:\n");
	printf("Expected: %s\n", "not NULL");
	printf("Got     : %p\n", ptr_1);

	if(!ptr_1) {
		fprintf(stderr, "%s", "First allocation did not match expected outcome");
		error++;
	}

	printf("\nLast allocation:\n");
	printf("Expected: %p\n", NULL);
	printf("Got     : %p\n", ptr_2);

	if(ptr_2) {
		fprintf(stderr, "%s", "Last allocation did not match expected outcome");
		error++;
	}

	if(error) {
		exit(1);
	}
}
