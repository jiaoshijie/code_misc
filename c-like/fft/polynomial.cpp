#include <iostream>
#include "Complex.hpp"
#include "FFT.hpp"

static void run();

int main() {
  run();
  return 0;
}

// 多项式
void run() {
  FFT fft;
  int n, m;
  std::cin >> n >> m;
  int len = 1;
  while(len <= m + n) len = len << 1;
  Complex *a = new Complex[len];
  Complex *b = new Complex[len];
  int t;
  for (int i = 0; i <= n; i++) {
    std::cin >> t;
    a[i].init(t, 0);
  }
  for (int i = 0; i <= m; i++) {
    std::cin >> t;
    b[i].init(t, 0);
  }
  int *pos = new int[len];
  fft.GetPos(pos, len);
  fft.FFT_nonRecursion(a, pos, len, 1);
  fft.FFT_nonRecursion(b, pos, len, 1);
  Complex *fc = new Complex[len];
  for (int i = 0; i < len; i++) {
    fc[i] = a[i] * b[i];
  }
  fft.FFT_nonRecursion(fc, pos, len, -1);
  for (int i = 0; i <= m + n; i++)
    std::cout << fc[i].get_r() / len << std::endl;
}
