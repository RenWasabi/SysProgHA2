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

  request test_req;
  test_req.addr = MY_NULL;
  test_req.p_num = 0;
  test_req.type = WRITE;

  addr_t va = mem_table_start[5*PT_AMOUNT+0xa];

  int perm = check_permission(va, test_req.type);

  printf("check_perm: %d\n",perm);



  
  return 0;
}
