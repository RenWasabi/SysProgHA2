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

  for (size_t i=0; i<32; i++){
    printf("%lu has LSB: %d\n", i, read_LSB(i));
  }

  return 0;
}
