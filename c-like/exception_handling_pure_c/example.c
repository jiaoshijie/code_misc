#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// https://www.youtube.com/watch?v=eQcRcgOnl9o

jmp_buf save_state;

double compute_avg(double *values, size_t length) {
  double sum = 0;

  if (length == 0) {
    longjmp(save_state, 1);  // NOTE: throw exception
  }

  for (size_t i = 0; i < length; i++) {
    sum += values[i];
  }

  return sum / (double) length;
}

int main(int argc, char *argv[]) {
  size_t arrlength  = argc - 1;
  double *darr = (double *)malloc(sizeof(double) * arrlength);
  for (size_t i = 0; i < arrlength; i++) {
    darr[i] = atof(argv[i + 1]);
  }

  if (setjmp(save_state) == 0) {  // NOTE: try
    double avg = compute_avg(darr, arrlength);
    printf("Average = %lf\n", avg);
  } else {  // NOTE: catch
    printf("invalid input\n");
  }

  return 0;
}
