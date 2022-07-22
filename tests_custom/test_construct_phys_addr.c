#include "../include/mmu.h"
MEMORY(MEM_SIZE,mem);

//abgewandelt aus test_mmu_simple.c
addr_t* setup_pt()
{
	addr_t *tmp = (addr_t*)mem;
	tmp[5*PT_AMOUNT+0xa] = (PRESENCE<<12)|(PERM_FULL_ACCESS);
	tmp[5*PT_AMOUNT+0xa] += 0x500;
	return tmp;
}

addr_t mock(){
  return MY_NULL
}


int main(){
  // aus mmu_test_simple.c
  MEMORY(MEM_SIZE,mem);
  mmu_init(mem);
  
  addr_t* mem_table_start = setup_pt();
  addr_t va = mem_table_start[5*PT_AMOUNT+0xa];

  request test_req;
  // page nr should always correspond to second left digit of addr
  test_req.addr = 0xf2df;
  test_req.p_num = 0;
  test_req.type = WRITE;

  addr_t va_1 = 0x0f12;
  addr_t entry_1 = 0x1fbc;
  printf("phys_addr: %p\n", construct_phys_addr(va_1, entry_1));

   
  return 0;
}
