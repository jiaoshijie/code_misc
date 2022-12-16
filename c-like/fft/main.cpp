#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Complex.hpp"
#include "FFT.hpp"
#include "loadpython.hpp"

static void run();
static double X(int i, int len);
static double Y(double i);
static void example();

static FFT fft;

int main() {
  run();
  return 0;
}

void example() {
  int len = 8;
  Complex *e = new Complex[len];
  e[0].init(3, 0);
  e[1].init(1 + sqrt(2) / 2, 0);
  e[2].init(0, 0);
  e[3].init(1 - sqrt(2) / 2, 0);
  e[4].init(1, 0);
  e[5].init(1 - sqrt(2) / 2, 0);
  e[6].init(0, 0);
  e[7].init(1 + sqrt(2) / 2, 0);
  fft.FFT_Recursion(e, len, -1);
  for (int i = 0; i < len; i++) {
    std::cout << e[i].get_r() / len << std::endl;
  }
}

void run() {
  LoadPy lpy;
  int len = 1024;
  double *x = new double[len], *y1 = new double[len], *y2 = new double[len];
  for (int i = 0; i < len; i++) {
    x[i] = X(i, len);
    y1[i] = Y(x[i]) + (rand() % 1000) / 1000.0 * 0.3;
  }
  int *pos = new int[len];
  fft.GetPos(pos, len);
  Complex *cy = new Complex[len];
  for (int i = 0; i < len; i++) {
    cy[i].init(y1[i], 0);
  }

  fft.FFT_nonRecursion(cy, pos, len, -1);

  for (int i = 0; i < len; i++) {
    cy[i].init(cy[i].get_r() / len, cy[i].get_i() / len);
  }

  int fix = 30;
  for (int i = fix; i < len - fix; i++) {
    cy[i].init(0, 0);
  }

  fft.FFT_nonRecursion(cy, pos, len, 1);
  for (int i = 0; i < len; i++) {
    y2[i] = cy[i].get_r();
    // y2[i] = cy[i].get_r() / al;
  }
  lpy.runpy(x, y1, y2, len);
}


double X(int i, int len) {
  return 2 * fft.Pi * i / len;
}


double Y(double i) {
  return 2 * cos(2 * i) + 3 * sin(4 * i);
}
