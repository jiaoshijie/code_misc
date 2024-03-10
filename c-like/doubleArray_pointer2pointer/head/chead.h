#ifndef __CHEAD__
#define __CHEAD__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

void name_print(char * name)
{
  printf("My name is %s\n", name);
}

void stack_print()
{
  char ch = 0;
  printf("stack space's address: %p\n", &ch);
}

void heap_print()
{
  char *ch = (char *)malloc(sizeof(char));
  printf("ch addr: %p, and heap space's address: %p\n", &ch, ch);
  free(ch);
}
