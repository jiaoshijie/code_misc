#include <iostream>

constexpr int value(int v) { return v * 2; }

int main(void) {
  constexpr static int v = value(2345);

  return 0;
}
