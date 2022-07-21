#include "../include/mmu.h"

int main(){
  // aus mmu_test_simple.c
  MEMORY(MEM_SIZE,mem);
  mmu_init(mem);

  request test_req;
  test_req.addr = MY_NULL;
  test_req.p_num = 0;
  test_req.type = READ;

  for (int i=0; i<34; i++){
    test_req.p_num = i;
    printf("ptbr: %p\n", get_ptbr());
    mmu_check_request(test_req);
  }

  
  return 0;
}
