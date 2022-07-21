#include "../include/mmu.h"

/* Memory start address: Startadresse unseres 12 bit Adressraumes */
static void *mem_start_addr;

/* page table base register = Seitentabellenbasisregister */
static addr_t *ptbr;

/* +------------------------------------+ *
 * | Hier ist Platz für Hilfsfunktionen | *
 * +------------------------------------+ */

// for testing
void* get_ptbr(){
  return ptbr;
}

int check_permission(addr_t va, req_type req){
  addr_t filter = 0b0000000000000111;
  // the actual permissions
  addr_t actual_perm = va & filter;
  // an address with 0 except for our bit needed (mask for our req)
  addr_t req_model = filter & req;
  addr_t result = actual_perm & req_model;
  if (result == 0){
    return 0;
  }
  else{
    return 1;
  }  
}


/* -------------------------------------- */

void mmu_init(void* mem)
{
	mem_start_addr = mem;
	ptbr = mem;
}

int switch_process(int proc_id)
{
  // check if proc_id is valid
  if (proc_id < 0 || proc_id > PROC_NUM-1){
      return 1;
  }
  // switch page table base register
  ptbr = mem_start_addr+proc_id*PT_AMOUNT*sizeof(addr_t);
  return 0;
}

addr_t mmu_translate(addr_t va, req_type req)
{
  return MY_NULL;
  
}

addr_t mmu_check_request(request r)
{
  // check if proc_id is valid and switch ptbr
  if (switch_process(r.p_num) == 1){
    //printf("invalid request (remove this warning)\n");
    return MY_NULL;
  }
   return MY_NULL;
}
