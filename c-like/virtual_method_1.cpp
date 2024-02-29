#include <iostream>

class A {
public:
  /* virtual */ void func() {
    std::cout << "A\n";
  }
};

class B: public A {
public:
  void func() {
    std::cout << "B\n";
  }
};

int main(void) {
  A* pa = new B;
  B* pnull = nullptr;
  pa->func();
  pnull->func();
  return 0;
}
