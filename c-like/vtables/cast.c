#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *p = (int *)malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    p[i] = i + 1;
  }

  for (int i = 0; i < 10; i++) {
    printf("%p: %d\n", &p[i], p[i]);
  }

  puts("----------------------------------------");

  for (int i = 0; i < 10; i++) {
    printf("%p: %d\n", &((void **)p)[i], ((void **)p)[i]);
  }

  puts("----------------------------------------");

  for (int i = 0; i < 10; i++) {
    printf("%p: %p\n", &((void **)p)[i], ((void **)p)[i]);
  }

  int breakpoint = 0;

  return 0;
}
