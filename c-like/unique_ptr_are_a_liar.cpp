#include <iostream>
#include <memory>
#include <vector>

// extern "C" {
//   void func(int *p) {
//     printf("raw c function: %d\n", *p);
//   }
// }

// void func(std::unique_ptr<int>& p) {
//   std::cout << *p << std::endl;
// }

int main(void) {
  int *p = nullptr;
  {
    std::unique_ptr<int> u(new int{10});
    p = &*u;
    printf("%p\n", p);
    std::cout << *p << std::endl;
  }
  printf("%p\n", p);
  std::cout << *p << std::endl;
  return 0;
}
