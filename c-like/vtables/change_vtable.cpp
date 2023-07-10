#include <iostream>
#include <cstring>

class A {
public:
  virtual void vfoo_1() {
    std::cout << "a_vfoo_1\n";
  }

  virtual void vfoo_2(int a) {
    std::cout << "a_vfoo_2: " << a << std::endl;
  }

  virtual int vfoo_3(int a, int b) {
    return a + b;
  }
};

typedef void (*void_pfunc_void)();
typedef void (*void_pfunc_int)(int);
typedef int (*int_pfunc_int_int)(int, int);

struct other_vtable {
  void_pfunc_void pf1;
  void_pfunc_int pf2;
  int_pfunc_int_int pf3;
};

void g_f1() {
  std::cout << "g_f1\n";
}

void g_f2(int a) {
  std::cout << "g_f2: " << a * 10 << std::endl;
}

int g_f3(int a, int b) {
  return a * b;
}

int main(void) {
  A *a = new A;
  other_vtable *ovt = new other_vtable;
  ovt->pf1 = g_f1;
  ovt->pf2 = g_f2;
  ovt->pf3 = g_f3;

  void *ptr = a;

  a->vfoo_1();
  a->vfoo_2(10);
  printf("a->vfoo_3: %d\n", a->vfoo_3(2, 5));
  puts("-------------------------------");

  memcpy(ptr, &ovt, sizeof(void *));

  a->vfoo_1();
  a->vfoo_2(10);
  printf("a->vfoo_3: %d\n", a->vfoo_3(2, 5));

  return 0;
}
