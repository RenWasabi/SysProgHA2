#include <stdio.h>
#include <stdlib.h>
#include "../include/calloc.h"
// Für memset
#include <string.h>
#include "../tests/calloc_helpers.h"

// aus Test entnommen
#define MEM_SIZE (512)
MEMORY(MEM_SIZE, mem);

int main(){

  printf("sizeof(size_t)): %lu\n", sizeof(size_t));
  printf("sizeof(mem_block): %lu\n\n", sizeof(mem_block));

  mem_block* generic_mem_pointer;
  mem_block generic_mem_block; 
  size_t testsize1 = sizeof(int);
  size_t testsize2 = sizeof(char);
  size_t testsize3 = sizeof(generic_mem_pointer);
  size_t testsize4 = sizeof(generic_mem_block);

  size_t round_to_8(size_t raw_size);
  printf("sizeof(int): %lu\n", testsize1);
  printf("rounded sizeof(int): %lu\n", round_to_8(testsize1));
  printf("sizeof(char): %lu\n", testsize2);
  printf("rounded sizeof(char): %lu\n", round_to_8(testsize2));
  printf("sizeof(generic_mem_pointer): %lu\n", testsize3);
  printf("rounded sizeof(generic_mem_pointer): %lu\n", round_to_8(testsize3));
  printf("sizeof(generic_mem_block): %lu\n", testsize4);
  printf("rounded sizeof(generic_mem_block): %lu\n", round_to_8(testsize4));

  for (size_t i=0; i<=32; i++){
    printf("%lu rounded to %lu\n", i, round_to_8(i));
      }
  
  return 0;
}
