int func1(int a, int b, int *c) {
  return a + b;
}

void func2(int *c) {
  int a = 99;
  int b = 1;
  int d = func1(a, b, c);
  a = a + d;
}

void func3(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
  a = g + h;
}

void func4() {
  int a1 = 1;
  int a2 = 2;
  int a3 = 3;
  int a4 = 4;
  int a5 = 5;
  int a6 = 6;
  int a7 = 7;
  int a8 = 8;
  int a9 = 9;
  func3(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

int main() {
  int *c = 0;
  func2(c);
  return 0;
}
