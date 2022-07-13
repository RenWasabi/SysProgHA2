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



/* -------------------------------------- */

void * my_calloc(size_t nmemb, size_t size, int c) {
	// TODO
	return NULL;
}

void my_free(void *ptr){
	// TODO
}
