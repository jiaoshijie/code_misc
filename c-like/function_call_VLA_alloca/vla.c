int func1(int n) {
  int b = 0xbe;
  int a[n];
  int c = 0xef;
  a[n - 2] = 10;
  a[n - 1] = n * 2;
  a[n - 1] += 2;
  return a[n - 1];
}

int main() {
  int a = func1(10);

  a = func1(100);

  return 0;
}
