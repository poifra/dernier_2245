#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdint.h>
#include <stdio.h>
#include "conf.h" 

struct physical_memory
{
  FILE* backing_store;
  FILE* log;
  char memory[PHYSICAL_MEMORY_SIZE];
};

/* Initialise la mémoire physique */
void pm_init(struct physical_memory*, FILE*, FILE*);
uint16_t pm_find_free_frame(struct physical_memory*);
uint16_t pm_demand_page(struct physical_memory*, uint16_t);
void pm_backup_frame(struct physical_memory*, uint16_t, uint16_t);
void pm_clean(struct physical_memory*);

#endif
