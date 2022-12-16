#include "head.hpp"

class Solution {
public:
  double myPow(double x, int n) {
    double res = x, temp = 1;
    if (n > 0) {
      while (n > 1) {
        if (n % 2) {
          temp *= res;
          n--;
        } else {
          res *= res;
          n /= 2;
        }
      }
      return res * temp;
    } else if (n < 0) {
      while (n < -1) {
        if (n % 2) {
          temp *= res;
          n++;
        } else {
          res *= res;
          n /= 2;
        }
      }
      return 1 / (temp * res);
    }
    return 1;
  }
};

int main() {
  Solution s;
  // std::cout << s.myPow(2.0, -2147483648) << std::endl;
  std::cout << s.myPow(1.72777, 7) << std::endl;
  return 0;
}
