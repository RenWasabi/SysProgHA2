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
	//test
	printf("beginning: %p\n", beginning);
	printf("last_allocation: %p\n", last_allocation);
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




/* -------------------------------------- */

void * my_calloc(size_t nmemb, size_t size, int c) {
	// TODO
	return NULL;
}

void my_free(void *ptr){
	// TODO
}
