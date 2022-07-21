#include "../include/mmu.h"

int main(){
  // aus mmu_test_simple.c
  MEMORY(MEM_SIZE,mem);
  mmu_init(mem);

  printf("%lu\n",sizeof(pte));
  printf("%lu\n",sizeof(addr_t));
  printf("%lu\n",PT_AMOUNT);
  printf("start | ptbr: %p (no process)\n", get_ptbr());
  
  for (int process=-5; process<35; process++){
    printf("out: %d | ptbr: %p (process %d)\n", switch_process(process), get_ptbr(), process);
  }

  void* test = get_ptbr()+PT_AMOUNT;
  printf("test: %p\n", test);

  // aus uni-test, sollte der page table mit index 5 entsprechen
  addr_t *tmp = (addr_t*)mem;
  printf("%p \n", tmp+5*PT_AMOUNT);

  
  return 0;
}
