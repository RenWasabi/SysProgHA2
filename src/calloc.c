#include "../include/calloc.h"
// Für memset
#include <string.h>

static void * MEM;
static size_t MEM_SIZE;

/* Die aktuelle Position für das Next Fit Verfahren */
static mem_block * last_allocation = NULL;

void my_calloc_init(void * mem, size_t mem_size){
	MEM = mem;
	MEM_SIZE = mem_size;

	/* Initial existiert genau ein mem_block direkt am Anfang des Speichers */
	mem_block * beginning = MEM;

	beginning->next = NULL;
	beginning->prev = NULL;

	/* Der verwaltete Speicher des initialen mem_blocks ist die des
	 * gesamten Speichers minus die Größe seiner eigenen Verwaltungsstruktur
	 * Da sowohl MEM_SIZE ein Vielfaches von 8 ist und sizeof(mem_block) auch
	 * mindestens ein vielfaches von 8 oder mehr ist, ist das LSB
	 * auch direkt 0 -> free.
	 */
	beginning->size = MEM_SIZE - sizeof(mem_block);

	/* Unser Zeiger für das Next Fit Verfahren */
	last_allocation = beginning;

}

/* +------------------------------------+ *
 * | Hier ist Platz für Hilfsfunktionen | *
 * +------------------------------------+ */

size_t round_to_8(size_t raw_size){
  size_t rounded_size;

  if (raw_size % 8 == 0){
    rounded_size = raw_size;}
  else {
    size_t factor = raw_size/8;
    rounded_size = (factor+1)*8;}

  return rounded_size;
}

int read_LSB(size_t size){
  //check value for 2^0
  int LSB = size & (1 << 0);
  return LSB;
}

// we need to work with return value because of call by value
size_t set_LSB(size_t size, int value){
  size_t new_size;

  if (value == 0){
    new_size = size &= ~(1 << 0);
  }
  else if (value == 1){
  //set value (i.e. to 1) for 2^0
  new_size = size |= 1 << 0;
  }
  else{
    printf("invalid value in set_LSB request\n");
  }
  return new_size;
}

//not tested
int read_memblock_status(mem_block* block){
  int status = read_LSB(block->size);
  return status;
}

// not tested
void set_memblock_status(mem_block* block, int status){
  size_t block_size = block->size;
  size_t new_block_size;
  new_block_size = set_LSB(block_size, status);
  block->size = new_block_size;
  return;  
}


// create a new memblock after memblock prev, within what remains of prev's data segment
// prev_actual_size is the size needed in prev
void* create_mem_block(mem_block* prev,size_t prev_actual_size){

  // only create a new block if the beginning mem_block already exists 
  if (prev == NULL){
    printf("Couldn't create new mem_block as beginning is missing.\n");
    return NULL;
  }

  void* prev_address = (void*) prev;
  void* new_address = prev_address+sizeof(mem_block)+prev_actual_size;

  // create mem_block
  mem_block* new = (mem_block*) new_address;

  // check that it aligns (8 Byte alignment)
  int address = (int) new;
  if (address % 8 != 0){
    printf("New address %p would not align! Returning...\n", new);
    return NULL;
  }
  
  // adjust pointers
  new->next = prev->next;
  if (new->next != NULL){
    new->next->prev = new;
  }
  prev->next = new;
  new->prev = prev;

  // set size and status "free" in new mem_block
  // of these, only prev->size might not be a multiple of 8 => no action needed
  size_t new_size = (prev->size)-prev_actual_size-sizeof(mem_block);
  new->size = set_LSB(new_size,0);
  // correct size and status "used" for previous element
  prev->size = set_LSB(prev_actual_size,1);
  
  void* new_begin_data = new+sizeof(mem_block);
  return new_begin_data;
}


// actual_needed should already be rounded to a multiple of 8
mem_block* find_block_next_fit(size_t actual_needed){

  // check first
  mem_block* current = last_allocation;
  int current_status = read_LSB(current->size);
  size_t current_size = set_LSB(current->size, 0);
  if ((current_status==0) && (current_size >= actual_needed)){
    return current;
  }
  // if current is end of list, go to the beginning 
  if (current->next == NULL){
    current = MEM;
  }
  else{
    current = current->next;
  }

  // check loop
  while(current != last_allocation){
    // just copied above code, couldn't think of more elegant way for now
     current_status = read_LSB(current->size);
     current_size = set_LSB(current->size, 0);
     if ((current_status==0) && (current_size >= actual_needed)){
     return current;
     }

    // if current is end of list, go to the beginning 
    if (current->next == NULL){
       current = MEM;
     }
    else{
       current = current->next;
     }
  }

  // went a circle, no fitting element
  return NULL;
}





/* -------------------------------------- */

void * my_calloc(size_t nmemb, size_t size, int c) {
  
  // calculate needed memory space
  size_t actual_needed = round_to_8(nmemb*size);
  
  // find fitting element
  mem_block* reserve_elem = find_block_next_fit(actual_needed);
  if (reserve_elem == NULL){
    printf("Es könnte kein Speicher reserviert werden.");
    return NULL;
  }

  // regular handling or splitting memory element
  //the minimum size a new storage element requires
  size_t new_elem_size = sizeof(mem_block)+8;
  // since reserve_elem was chosen, LSB needs to be 0 anyway
  // size >= needed, otherwise element wouldn't have been chosen, so upper limit is sufficient

   // will be NULL in first cases, still initialized here for access
  void* new_begin_data = NULL;
  // Fall a) und c)
  if (reserve_elem->size < actual_needed+new_elem_size){
    reserve_elem->size = set_LSB(reserve_elem->size, 1);
  }
  // Fall b)
  else{
    // reserve_elem data will be adjusted in create function
    new_begin_data = create_mem_block(reserve_elem, actual_needed);
  }

  last_allocation = reserve_elem;
  // for easier calculations
  void* reserve_elem_as_void = (void*) reserve_elem;
  void* reserved_begin_data = reserve_elem_as_void+sizeof(mem_block);

  // Speicher initialisieren

  return reserved_begin_data;
}

void my_free(void *ptr){
	// TODO
}
