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
  void* data1 = my_calloc(3, 15, 0);
  void* data2 = my_calloc(5, 2, 0);
  void* data3 = my_calloc(1, 59,0);
  printf("data1: %p\n", data1);
  printf("data2: %p\n", data2);
  printf("data3: %p\n\n", data3);

  void* mem1_v = data1-sizeof(mem_block);
  mem_block* mem1 = (mem_block*) mem1_v;
  mem_block* created = mem1;
  printf("created: %p\n", created);
  printf("size: %d\n", set_LSB(created->size,0));
  printf("status: %d\n", read_LSB(created->size));
  printf("created->next: %p\n", created->next);
  printf("created->prev: %p\n\n", created->prev);

  void* mem2_v = data2-sizeof(mem_block);
  mem_block* mem2 = (mem_block*) mem2_v;
  created = mem2;
  printf("created: %p\n", created);
  printf("size: %d\n", set_LSB(created->size,0));
  printf("status: %d\n", read_LSB(created->size));
  printf("created->next: %p\n", created->next);
  printf("created->prev: %p\n\n", created->prev);

  void* mem3_v = data3-sizeof(mem_block);
  mem_block* mem3 = (mem_block*) mem3_v;
  created = mem3;
  printf("created: %p\n", created);
  printf("size: %d\n", set_LSB(created->size,0));
  printf("status: %d\n", read_LSB(created->size));
  printf("created->next: %p\n", created->next);
  printf("created->prev: %p\n\n", created->prev);

  created = mem3->next;
  printf("created: %p\n", created);
  printf("size: %d\n", set_LSB(created->size,0));
  printf("status: %d\n", read_LSB(created->size));
  printf("created->next: %p\n", created->next);
  printf("created->prev: %p\n", created->prev);


  return 0;
}
