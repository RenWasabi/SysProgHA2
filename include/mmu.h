#ifndef MMU_H
#define MMU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* NULL-ptr Äquivalent */
#define MY_NULL 0x0000;

/* Speichergröße bleibt für die HA konstant */
#define MEM_SIZE (4*1024)
#define PAGE_SIZE 256
#define PT_AMOUNT (MEM_SIZE/PAGE_SIZE)

/* Standardwerte, können sich ändern */
#define PROC_NUM 32

/* Dieses Macro erstellt den Speicher mit der Größe "size"
 * und dem Namen "name". Alignment ist entsprechend angepasst,
 * um den in der HA genutzten phy Adressraum bei 0 beginnen lassen
 * zu können. */
#define MEMORY(size, name) \
	static char name[size] __attribute__((aligned(MEM_SIZE)))

/* Bitmasken für die Zugriffsrechte */
typedef enum mmu_permission {
	PERM_NO_ACCESS = 0b000,	/* kein Zugriff */
	PERM_READ_ONLY = 0b001,	/* nur lesend Zugriff */
	PERM_READ_WRITE = 0b011,/* lesend und schreibend Zugriff */
	PERM_EXECUTE = 0b100,   /* Seite als ausführbar (Code) markiert */
	PERM_FULL_ACCESS = 0b111/* vereint lesend, schreibend und ausführbar */
} permission;

/* Bitmasken für die Informationsbits */
typedef enum pt_information {
	PRESENCE = 0b1000,	/* gesetzt, wenn die Seite im physischen Speicher ist */
	ACCESSED = 0b0100,	/* gesetzt, wenn auf die Seite ein Zugriff erfolgt */
	MODIFIED = 0b0010	/* gesetzt, wenn die Seite verändert wurde */
} pt_info;

/* sowohl die virtuellen Adressen als auch die Seitentabelleneinträge sind
   16 bit breit, die physischen Adressen entsprechend 12 bit <= 16bit */
typedef uint16_t addr_t;

/* page table entry = Seitentabelleneintrag
 * |15....12|11.......8|7....0|
 * |Infofeld|Seitenzahl|Offset| */
typedef struct __attribute__((packed)) _pte {
	addr_t offset:8;
	addr_t page_num:4;
	pt_info info:4;
} pte;

typedef enum _req_type {
	READ = 0b001,
	WRITE = 0b010,
	EXECUTE = 0b100
} req_type;

/* Anfragestruktur: enthält zuzugreifende Adresse,
 * Nummer des anfragenden Prozesses und die Art
 * der Anfrage */
typedef struct request_struct {
	addr_t addr;
	uint8_t p_num;
	req_type type;
} request;

/* Initialisiert den Adressraumpointer */
void mmu_init(void *mem);

/* PTBR neu setzen
 * @param proc_id: Prozess-ID des als nächstes laufenden Prozesses
 * @return: status code: gibt 1 zurück, falls Prozess-ID ungültig
 *                       gibt 0 zurück, falls erfolgreich */
int switch_process(int proc_id);

/* Implementiert die Grundfunktion der MMU
 * @param va: virtuelle Adresse, welche mittels Pagetablelookup
 *            in eine physische Adresse umgewandelt werden soll
 * @param req: Zugriffsart (Rechtecheck nicht vergessen)
 * @return: physische Adresse */
addr_t mmu_translate(addr_t va, req_type req);

/* Anfrage eines Prozesses
 * da die Vorgabe u.a. auf einen Scheduler verzichtet, müssen hier
 * entsprechende Initialisierungen vorgenommen werden, bevor
 * mmu_translate() aufgerufen werden kann
 * @param r: zu verarbeitende Anfrage eines Prozesses
 * @return: physische Adresse der Anfrage sonst NULL */
addr_t mmu_check_request(request r);

#endif
