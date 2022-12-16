#pragma once
#include <iostream>
#include <cmath>
#include "Complex.hpp"

class FFT {
private:
  /*************2.**************/
  int rev(int k, const int len) {
    int l= 0, r = len - 1;
    while (l != r) {
      if (k & 1) {
        l = (l + r) / 2 + 1;
      } else {
        r = (l + r) / 2;
      }
      k >>= 1;
    }
    return l;
  }

  void SwapVar(Complex *f, const int *pos, const int len) {
    for (int i = 0; i < len; i++) {
      if (i < pos[i]) {
        std::swap(f[i], f[pos[i]]);
      }
    }
  }

public:
  const double Pi = acos(-1);

  void FFT_Recursion(Complex *f, int len, int flag) {  // flag: 1 为逆变换，2为变换
    if (len == 1) return;
    int tot = len >> 1;
    Complex *a1 = new Complex[tot];
    Complex *a2 = new Complex[tot];
    for (int i = 0; i < tot; i++) {
      a1[i] = f[i << 1];
      a2[i] = f[i << 1 | 1];
    }
    FFT_Recursion(a1, tot, flag);
    FFT_Recursion(a2, tot, flag);
    for (int i = 0; i < tot; i++) {
      // 2pi 的合理性
      Complex temp(cos(flag * 2 * i * Pi / len), sin(flag * 2 * i * Pi / len));
      f[i] = a1[i] + temp * a2[i];
      f[i + tot] = a1[i] - temp * a2[i];
    }
  }

  void FFT_nonRecursion(Complex *f, const int *pos, int len, int flag) {  // flag: 1 为逆变换，2为变换
    SwapVar(f, pos, len);
    for (int i = 2; i <= len; i <<= 1) {
      // 2pi 的合理性
      Complex wn(cos(flag * 2 * Pi / i), sin(flag * 2 * Pi / i));
      for (int j = 0; j < len; j += i) {  // TODO: why this is prossible? "2 que"
        Complex w(1, 0);
        for (int k = j; k < j + i / 2; k++) {
          Complex u = f[k];
          Complex t = w * f[k + i / 2];
          f[k] = u + t;
          f[k + i / 2] = u - t;
          w = w * wn;
        }
      }
    }
  }

  void GetPos(int *pos, const int len) {
    for (int i = 1; i < len; i++) {
      // 1.
      pos[i] = pos[i >> 1] >> 1;
      if (i & 1) pos[i] |= len >> 1;

      // 2.
      // pos[i] = rev(i, len);
    }
  }


};

