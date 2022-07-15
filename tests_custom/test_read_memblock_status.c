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

  my_calloc_init(mem, MEM_SIZE);
  MEM_SIZE (512)
MEMORY(MEM_SIZE, mem);


  /* Initial existiert genau ein mem_block direkt am Anfang des Speichers */
  mem_block * beginning = MEM;

  beginning->next = NULL;
  beginning->prev = NULL;
  beginning->size = MEM_SIZE - sizeof(mem_block);
  

  
  

  return 0;
}
