
#include <stdint.h>
#include <stdio.h>

#include "tlb.h"

// Ne pas modifier cette fonction
void
tlb_init (struct tlb *tlb, FILE * log)
{
  for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
      tlb->entries[i].page_number = -1;
      tlb->entries[i].frame_number = -1;
    }

  tlb->log = log;
  tlb->next_entry_available = 0;
}

// Ne pas modifier cette fonction
void
tlb_clean (struct tlb *tlb)
{
  if (tlb->log)
    {
      for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
	{
	  fprintf (tlb->log,
		   "%d: %d -> %d\n",
		   i,
		   tlb->entries[i].page_number, tlb->entries[i].frame_number);
	}
    }
}


// Sur entrée d'un numéro de page, retourne le numéro de frame
// associé. S'il n'y a pas d'entrée correspondante à la page,
// -1 est retourné.
int32_t
tlb_lookup (struct tlb *tlb, uint16_t page_number)
{
  for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
      if (tlb->entries[i].page_number == page_number)
	tlb->entries[i].used = time (NULL);
      return tlb->entries[i].frame_number;
    }
  return -1;
  // Complétez cette fonction.
}

// Ajoute une entré dans le tlb. Pour bien mettre en oeuvre
// cette fonction, il est nécessaire d'avoir un algorithme
// de remplacement pour bien gérer un tlb plein.
void
tlb_add_entry (struct tlb *tlb, uint16_t page_number, uint16_t frame_number)
{
  // Complétez cette fonction.
  int lru;
  if (tlb->next_entry_available < TLB_NUM_ENTRIES)
    {
      tlb->entries[tlb->next_entry_available].page_number = page_number;
      tlb->entries[tlb->next_entry_available].frame_number = frame_number;
      tlb->entries[tlb->next_entry_available].used = time (NULL);
      tlb->next_entry_available++;
    }
  else
    {
      //LRU replacement
      for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
	{
	  if (tlb->entries[i].used < tlb->entries[lru].used)
	    {
	      lru = i;
	    }
	}
      //replace with new entry
      tlb->entries[lru].page_number = page_number;
      tlb->entries[lru].frame_number = frame_number;
      tlb->entries[lru].used = time (NULL);
    }
  return;
}
