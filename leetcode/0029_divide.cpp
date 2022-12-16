#include "head.hpp"

// 10 -> 2^1 * 3 + 2^0 * 3
// 10/3 -> 2^1 + 2^0 = 3

class Solution {
public:
  int divide(int dividend, int divisor) {
    int sign = 1, power = 0;
    if (dividend < 0 || divisor < 0) {
      sign = dividend < 0 && divisor < 0 ? 1 : -1;
    }
    long long temp = std::abs((long)divisor), div = std::abs((long)dividend), res = 0;
    while (div >= 0 && div >= temp) {
      power = 0;
      while (div >= temp) {
        temp = temp << 1;
        power++;
      }
      power--;
      div -= (temp >> 1);
      res += (1ll << power);
      temp = std::abs((long)divisor);
    }
    if (res * sign > INT32_MAX || res * sign < INT32_MIN) return INT32_MAX;
    return sign * res;
  }
};

int main() {
  Solution s;
  std::cout << s.divide(INT32_MIN, -1) << std::endl;
  return 0;
}
