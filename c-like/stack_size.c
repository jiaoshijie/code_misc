#include <stdio.h>

// $ ulimit -s        # check out the current stack size
// $ ulimit -s 10240  # set the stack size to 10M

void func(int count) {
  printf("%d\n", count);
  char _1024m[1024 * 1024];
  func(count + 1);
}

int main() {
  func(1);
  return 0;
}
