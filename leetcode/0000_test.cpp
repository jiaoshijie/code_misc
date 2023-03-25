#include "head.hpp"

void func(int& x) {
  std::cout << typeid(x).name() << std::endl;
}

int main() {
  int a = 2;
  int* x = new int(10);
  auto y = &x;
  // std::cout << x << ' ' << *x << std::endl;
  // std::cout << y << ' ' << *y << ' ' << **y << std::endl;
  // std::cout << &a << std::endl;
  func(a);
  // std::cout << typeid(y).name() << std::endl;
  // std::cout << typeid(a).name() << std::endl;
  // std::cout << typeid(x).name() << std::endl;
  std::cout << *a << std::endl;
  return 0;
}
