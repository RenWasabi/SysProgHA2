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

  size_t x = 3;
  printf("LSB x: %d\n", read_LSB(x));
  size_t y = set_LSB(x, 0);
  printf("LSB y: %d\n\n", read_LSB(y));

  printf("%lu\n", set_LSB(0,0));
  printf("%lu\n", set_LSB(0,1));
  printf("%lu\n", set_LSB(1,0));
  printf("%lu\n", set_LSB(1,1));
  
  for (size_t j=1; j<33; j++){
    int i = j;
    int set_to = 0;
    printf("i: %lu  LSB i: %d ", i,read_LSB(i));
    i = set_LSB(i, set_to);
    printf("set_to%d: %d  new i: %lu\n", set_to, read_LSB(i),i);
  }
  
  

  
  

  return 0;
}
