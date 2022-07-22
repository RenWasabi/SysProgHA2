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

int check_permission(addr_t entry, req_type req){
  addr_t filter = 0b0000000000000111;
  // the actual permissions
  addr_t actual_perm = entry & filter;
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

void set_info(addr_t* entry, pt_info info){
  int position;
  if (info == PRESENCE){
    position = 15;
  }
  else if (info == ACCESSED){
    position = 14;
  }
  else if (info == MODIFIED){
    position = 13;
  }
  else{
    printf("Error occured while trying to set info bit.\n");
    return;
  }

  *(entry) = *(entry) | 1 << position;
  return; 
}

int check_presence(addr_t entry){
  // presence_bit is a 16 bit number with 15 zeros
  // and the result as MSB
  int presence_bit = entry & (1 << 15);
  if (presence_bit == 0){
    return 0;
  }
  else{
    return 1;
  }
}

int read_page_nr(addr_t va){
  addr_t mask = 0b0000111100000000;
  addr_t pg_nmb = va & mask;
  pg_nmb = pg_nmb >> 8;
  return pg_nmb;
}

addr_t construct_phys_addr(addr_t va, addr_t pt_entry){
  addr_t mask_offset = 0b0000000011111111;
  addr_t offset = va & mask_offset;
  addr_t mask_kachel = 0b0000111100000000;
  addr_t kachel_nr = pt_entry & mask_kachel;
  addr_t phys_addr = offset | kachel_nr;
  return phys_addr;
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
  // access the page table entry corresponding to the virtual addr
  addr_t* pg_table = (addr_t*) ptbr;
  addr_t entry = pg_table[read_page_nr(va)];
  // check if the entry is valid (present)
  if (check_presence(entry)==0){
    return MY_NULL
  }
  // check if the process is allowed to access in the requested way
  if (check_permission(entry, req)==0){
    return MY_NULL
  }
  // set info in page table
  set_info(&entry, ACCESSED);
  if (req == WRITE){
    set_info(&entry, MODIFIED);
  }
  // calculate and return the physical address
  addr_t phys_addr = construct_phys_addr(va, entry);
  return phys_addr;
}

addr_t mmu_check_request(request r)
{
  // check if proc_id is valid and switch ptbr
  if (switch_process(r.p_num) == 1){
    //printf("invalid request (remove this warning)\n");
    return MY_NULL;
  }
  addr_t phys_addr = mmu_translate(r.addr, r.type);
  return phys_addr;
}
