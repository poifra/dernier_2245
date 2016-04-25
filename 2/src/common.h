#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdint.h>

#define new(x) malloc(sizeof (x))

void error(bool b, const char* fmt, ...);

/*
Changed the location of this definition because it is used in pm_clean
*/

enum page_flags
{
  verification = 0x1,
  dirty        = 0x2
};

typedef struct page
{
  uint8_t flags;
  int32_t frame_number;
} page;

#endif

