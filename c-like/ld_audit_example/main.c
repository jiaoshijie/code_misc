#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  (void) argc;

  char *program = *argv++;

  if (*argv) {
    printf("%s: %s\n", program, *argv++);
  }

  srand(time(NULL));

  int x = rand() % 10;
  printf("x = %d => %lf\n", x, exp(x));
  x = rand() % 10;
  printf("x = %d => %lf\n", x, exp(x));

  return 0;
}
