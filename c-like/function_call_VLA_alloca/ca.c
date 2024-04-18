#include <alloca.h>

int func1(int n) {
  int *a = (int *)alloca(n);
  a[n - 1] = n * 2;
  a[n - 1] += 2;
  return a[n - 1];
}

int main() {
  int a = func1(10);

  a = func1(100);

}
