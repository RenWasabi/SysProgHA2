./a.#include <stdio.h>
#include <stdlib.h>
#include "./include/calloc.h"
// Für memset
#include <string.h>
#include "./tests/calloc_helpers.h"

// aus Test entnommen
#define MEM_SIZE (512)
MEMORY(MEM_SIZE, mem);

int main(){


  my_calloc_init(mem, MEM_SIZE);
  


  return 0;
}
