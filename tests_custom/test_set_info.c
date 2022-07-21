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
  test_req.addr = va;
  test_req.p_num = 0;
  test_req.type = WRITE;

  pt_info test_info = PRESENCE;

  printf("before: %hu\n", test_req.addr);
  printf("set to: %d\n", test_info);
  set_info(&test_req.addr, test_info);
  printf("after: %hu\n", test_req.addr);


  


  
  return 0;
}
