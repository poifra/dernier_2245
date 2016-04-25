#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conf.h"
#include "physical_memory.h"
#include "common.h"

// Initialise la mémoire physique
void
pm_init (struct physical_memory *pm, FILE * backing_store, FILE * pm_log)
{
	pm->backing_store = backing_store;
	pm->log = pm_log;
   pm->currentFrame = 0;

	for (unsigned int i = 0; i < PHYSICAL_MEMORY_SIZE; i++)
	{
		pm->memory[i] = ' ';
	}
}

// Retourne le numéro d'une trame (frame) libre
uint16_t
pm_find_free_frame (struct physical_memory *pm)
{
   if (pm->currentFrame == NUM_FRAMES){
      error(true,"404 RAM not found \n");
      exit(-1);
   }
   else{
      return pm->currentFrame++;
   }

}

// Charge la page demandée du backing store
uint16_t
pm_demand_page (struct physical_memory * pm, uint16_t page_number)
{
	uint16_t frame = pm_find_free_frame (pm);
   fseek (pm->backing_store, (page_number << 8), SEEK_SET);
	fread (pm->memory, sizeof (char), PAGE_FRAME_SIZE, pm->backing_store);
	return frame;
}

// Sauvegarde la page spécifiée
void
pm_backup_frame (struct physical_memory *pm, uint16_t frame_number,
                 uint16_t page_number)
{
   fseek(pm->backing_store, (page_number << 8), SEEK_SET);
   fwrite(pm->memory, sizeof(char), PAGE_FRAME_SIZE, pm->backing_store);
}

void
pm_clean (struct physical_memory *pm, struct page *page_table)
{
	// Assurez vous d'enregistrer les modifications apportées au backing store!
   for (int i = 0; i < NUM_PAGES; i++)
      if(page_table[i].flags & 0x2) //if dirty, save it
         pm_backup_frame(pm, page_table[i].frame_number, i);
   
	// Enregistre l'état de la mémoire physique.
	if (pm->log)
	{
		for (unsigned int i = 0; i < PHYSICAL_MEMORY_SIZE; i++)
		{
			if (i % 80 == 0)
			{
				fprintf (pm->log, "%c\n", pm->memory[i]);
			}
			else
			{
				fprintf (pm->log, "%c", pm->memory[i]);
			}
		}
	}
}
