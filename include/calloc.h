#ifndef MY_CALLOC_H
#define MY_CALLOC_H

#include <stddef.h>

/* Dieses Struct enthält alle notwendigen Information die benötigt werden
 * um den Speicherbereich zu verwalten. Dabei liegt ein mem_block im Speicher
 * immer direkt vor dem zu verwaltenden Speicherbereich.
 * Ein mem_block Struct sollte immer 8 Byte aligned im Speicher liegen.
 */
typedef struct _mem_block {

	/* Zeigt auf den nächsten Speicherblock
	 * NULL falls dieses der letzte Block ist
	 */
	struct _mem_block * next;

	/* Zeigt auf den vorherigen Speicherblock
	 * NULL falls dieses der erste Block ist
	 */
	struct _mem_block * prev;

	/* Größe des verwalteten Speicherbereichs.
	 * Der Speicherbereich fängt direkt nach dem Block an.
	 * size enthält folgende Informationen:
	 * - Die Größe des verwalteten Speicherbereichs inklusive Padding
	 * - Ob der Speicher frei oder belegt ist im LSB
	 *   -> LSB ist 1: Speicher ist belegt
	 *   -> LSB ist 0: Speicher ist frei
	 */
	size_t size;
} mem_block;

/* Initialisiert den Speicher und erstellt den ersten memory block.
 * @param mem: Zeiger auf den Anfang des Speicherbereichs. 8 Byte aligned.
 * @param mem_size: Gesamte Größe des Speicherbereichs.
 */
void my_calloc_init(void * mem, size_t mem_size);

/* Alloziert neuen Speicher und Initialisiert diesen auf den angegebenen Wert.
 * Wie calloc aus stdlib.h aber mit Zusatz, dass bestimmt werden kann womit der
 * Speicher initialisiert wird.
 * @param: Anazahl der Elemente
 * @param size: Größe eines Elements
 * @param c: Das Byte mit dem der neu allozierte Speicher Initialisiert wird.
 * @return Zeiger auf den benutzbaren Speicher (nicht auf das mem_block Struct!).
 *         -> NULL falls kein ausreichend großer Speicher gefunden werden konnte.
 */
void * my_calloc(size_t nmemb, size_t size, int c);


/* Gibt den Speicher wieder frei und macht diesen für spätere Allokationen verfügbar.
 * Dabei soll der Block mit freien Blöcken, die vor und nach diesem liegen "verschmelzen".
 * @param ptr: Zeiger auf den Speicher (nicht auf das mem_block Struct!).
 *             Der Zeiger muss ursprünglich von einem my_calloc Aufruf kommen.
 */
void my_free(void *ptr);


// Hilfsfunktionen:

// returns the input size rounded up to 8 ([Byte])
size_t round_to_8(size_t raw_size);

// returns the LSB of a size variable
int read_LSB(size_t size);

// returns size with bit set to value
size_t set_LSB(size_t size, int value);

// reads status of memblock
// 1: used, 0: free
int read_memblock_status(mem_block* block);

// sets status of memblock
// 1: used, 0: free
void set_memblock_status(mem_block* block, int status);

// create a new mem_block within the data segment of the mem_block prev
// prev_actual_size is the actual space needed in the data segment of prev
void* create_mem_block(mem_block* prev,size_t prev_actual_size);

// find fitting and free block using next_fit strategy
mem_block* find_block_next_fit(size_t actual_needed);

// not sure if this one is necessary
void null_pointers(mem_block* block);

// merges a block with the (free) block before it, returns merged block
mem_block* merge_with_prev(mem_block* back);

// merges a block with the (free) block after it, returns merged block
mem_block* merge_with_next(mem_block* front);

// merges a block with its previous and next block, returns merged block
mem_block* merge_two_sides(mem_block* middle);

#endif
