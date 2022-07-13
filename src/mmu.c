#include "../include/mmu.h"

/* Memory start address: Startadresse unseres 12 bit Adressraumes */
static void *mem_start_addr;

/* page table base register = Seitentabellenbasisregister */
static addr_t *ptbr;

/* +------------------------------------+ *
 * | Hier ist Platz für Hilfsfunktionen | *
 * +------------------------------------+ */



/* -------------------------------------- */

void mmu_init(void* mem)
{
	mem_start_addr = mem;
	ptbr = mem;
}

int switch_process(int proc_id)
{
	return 0;
}

addr_t mmu_translate(addr_t va, req_type req)
{
	return MY_NULL;
}

addr_t mmu_check_request(request r)
{
	return MY_NULL;
}
