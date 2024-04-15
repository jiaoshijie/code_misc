#include <stdio.h>

// $ cc -O2 integer_overflow_undefined.c -fsanitize=undefined
// $ man gcc   # search for `-fsanitize=undefined`
// Will print some information in runtime when overflow occurs.

void func(int a) {
  if (a + 100 > a) {
    puts("GT");
  } else {
    puts("LT");
  }
  puts("----------------------------------------");
}

int main() {
  func(10);

  int a = 0x7fffffff;
  func(a);

  // set c be 2147483647
  int c;
  scanf("%d", &c);
  func(c);
  return 0;
}
