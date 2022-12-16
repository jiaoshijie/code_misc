#pragma once
#include <iostream>

class Complex {
private:
  double r, i;  // real, imaginary number
public:
  Complex() : r(0), i(0) {}
  Complex(double r, double i) : r(r), i(i) {}
  void init(double r, double i) {
    this->r = r;
    this->i = i;
  }
  Complex operator +(const Complex &b) {  // 复数加法
    return Complex(this->r + b.r, this->i + b.i);
  }
  Complex operator -(const Complex &b) {  // 复数减法
    return Complex(this->r - b.r, this->i - b.i);
  }
  Complex operator *(const Complex &b) {  // 复数乘法
    return Complex(this->r * b.r - this->i * b.i,
                   this->r * b.i + this->i * b.r);
  }
  friend std::ostream & operator << (std::ostream &out, Complex a);  // Complex &a

  double get_r() const {  // 获取复数实部值
    return this->r;
  }
  double get_i() const {  // 获取复数虚部值
    return this->i;
  }
};

inline std::ostream & operator << (std::ostream &out, Complex a) {
  if (a.i == 0) out << a.r;
  else if (a.r == 0) out << a.i << "i";
  else out << a.r << " + " << a.i << "i";
  return out;
}
