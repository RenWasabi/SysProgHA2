#include <stdio.h>

#include "calloc_helpers.h"

// More complex test that does multiple allocation and frees
// In the end everything should be properly free'd

#define MEM_SIZE ((size_t)(1024 * 1024)) // 1MB
static char mem[MEM_SIZE] __attribute__((aligned(8)));

int main() {

	int error = 0;

	my_calloc_init(mem, MEM_SIZE);

	size_t initial_free_memory = mem_size_free(mem);

	mem_print_blocks(mem);

	printf("Allocating three times\n");

	void * ptr1 = my_calloc(100, 1, 'A');
	void * ptr2 = my_calloc(1024, 512, 'B');
	void * ptr3 = my_calloc(1, 1, 'C');

	mem_print_blocks(mem);

	printf("Freeing all\n");

	my_free(ptr2);
	my_free(ptr1);
	my_free(ptr3);

	// last_allocated sollte wieder auf dem ersten Block sein
	mem_print_blocks(mem);

	char * str1 = my_calloc(10, 1, 'D');
	char * str2 = my_calloc(10, 1, 'E');
	char * str3 = my_calloc(10, 1, 'F');

	my_free(str2);

	// Sollte nach F liegen, da Next Fit
	str2 = my_calloc(10, 1, 'G');

	// Zu 0-terminierten string bauen
	str1[9] = '\0';
	str2[9] = '\0';
	str3[9] = '\0';

	mem_print_blocks(mem);

	unsigned int block_count = mem_block_count(mem);
	printf("Expected block count: %u\n", 5);
	printf("Final block count   : %u\n", block_count);
	if(block_count != 5) {
		fprintf(stderr, "Final block count did not match expected count\n");
		error++;
	}

	printf("Concatenating data\n");
	char * concat = mem_concat_data(mem);
	char * str_expected = "DDDDDDDDDFFFFFFFFFGGGGGGGGG";
	printf("Expected: %s\n", str_expected);
	printf("Found   : %s\n", concat);

	if(strcmp(concat, str_expected) != 0) {
		fprintf(stderr, "Did not match!\n");
		error++;
	}

	printf("Freeing everything\n");

	my_free(str1);
	my_free(str2);
	my_free(str3);

	mem_print_blocks(mem);

	size_t final_free_space = mem_size_free(mem);
	printf("Initial memory   : %zd\n", initial_free_memory);
	printf("Final free memory: %zd\n", final_free_space);
	if(final_free_space != initial_free_memory) {
		fprintf(stderr,"Error: Final free memory did not match initial size\n");
		error++;
	}

	unsigned int final_block_count = mem_block_count(mem);
	printf("Expected block count: %u\n", 1);
	printf("Final block count   : %u\n", final_block_count);
	if(final_block_count != 1) {
		fprintf(stderr, "Final block count did not match expected count\n");
		error++;
	}

	if(error) {
		exit(1);
	}
}
