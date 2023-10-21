#include <iostream>

int main(void) {
  // TODO: int **a;
  int b[2][3] = {1, 2, 3, 4, 5, 6};
  std::cout << &b[0] << std::endl;
  std::cout << &b[1] << std::endl;
  std::cout << &b[0][0] << std::endl;
  std::cout << &b[0][1] << std::endl;
  // std::cout << &a[0] << std::endl;
  // std::cout << &a[0] + 1 << std::endl;
  // std::cout << (*(&a[0] + 1))[1] << std::endl;
  std::cout << "------------------------------------\n";
  int **a;
  a = (int**)malloc(sizeof(int*) * 2);
  int count = 1;
  for (int i = 0; i < 2; i++) {
    a[i] = (int*)malloc(sizeof(int) * 3);
    for (int j = 0; j < 3; ++j) {
      a[i][j] = count++;
    }
  }

  std::cout << &a[0] << std::endl;
  std::cout << &a[1] << std::endl;

  std::cout << &a[0][0] << std::endl;
  std::cout << &a[0][1] << std::endl;

  std::cout << (*(&a[0] + 1))[1] << std::endl;

  // NOTE: Segment fault
  // const char* p = "abc";
  // char* c = (char*)p;
  // c[1] = 'g';
  // std::cout << c << std::endl;
  return 0;
}
