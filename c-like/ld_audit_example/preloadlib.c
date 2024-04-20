// #include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#define __USE_GNU
#include <dlfcn.h>
#include <unistd.h>

// __attribute__((constructor)) static void init(void) {
//   printf("loaded from LD_PRELOAD\n");
// }

double exp(double x) {
  static double (*real_exp)(double) = NULL;
  if (real_exp == NULL) {
    real_exp = dlsym(RTLD_NEXT, "exp");
  }
  return real_exp(x) + 1;
}
