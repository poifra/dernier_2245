#include <stdio.h>

#include <stdbool.h>

#include "conf.h"
#include "physical_memory.h"
#include "common.h"
#include "stdlib.h"

// Initialise la mémoire physique
void
pm_init (struct physical_memory *pm, FILE * backing_store, FILE * pm_log)
{
	pm->backing_store = backing_store;
	pm->log = pm_log;

	for (unsigned int i = 0; i < PHYSICAL_MEMORY_SIZE; i++)
	{
		pm->memory[i] = ' ';
	}
}

// Retourne le numéro d'une trame (frame) libre
uint16_t
pm_find_free_frame (struct physical_memory *pm)
{
	uint16_t frameFound = -1;
	for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i += PAGE_FRAME_SIZE)
	{
		if (pm->memory[i] == ' ')
		{
			frameFound = i;
			break;
		}
	}
	if (frameFound == -1)
	{
      error(true, "no free frame :(");
	}
	return frameFound;
}

// Charge la page demandée du backing store
uint16_t
pm_demand_page (struct physical_memory *pm, uint16_t page_number)
{
	uint16_t frame = pm_find_free_frame(pm);
   fread(pm->memory, sizeof(char), PAGE_FRAME_SIZE, pm->backing_store);
	return frame;
}

// Sauvegarde la page spécifiée
void
pm_backup_frame (struct physical_memory *pm, uint16_t frame_number,
                 uint16_t page_number)
{
}

void
pm_clean (struct physical_memory *pm)
{
	// Assurez vous d'enregistrer les modifications apportées au backing store!

	// Enregistre l'état de la mémoire physique.
	if (pm->log)
	{
		for (unsigned int i = 0; i < PHYSICAL_MEMORY_SIZE; i++)
		{
			if (i % 80 == 0) {
				fprintf (pm->log, "%c\n", pm->memory[i]);
			}
			else {
				fprintf (pm->log, "%c", pm->memory[i]);
			}
		}
	}
}
