#ifndef outops
#define outops

#include <stdio.h>

void clearScreen()
{
  printf("\e[1;1H\e[2J");
}


#endif