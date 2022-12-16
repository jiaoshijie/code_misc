#include "head.hpp"

class Solution {
public:
  int reverse(int x) {
    if (x == INT32_MIN) return 0;
    int x_sign = x > 0 ? 1 : -1;
    x = x_sign * x;
    int res = 0, last_r = 0;
    while(x) {
      last_r = res;
      if (last_r > INT32_MAX / 10) return 0;
      res = res * 10 + x % 10;
      x /= 10;
    }
    return x_sign * res;
  }
};

int main() {
  Solution s;
  int x = INT32_MAX;
  std::cout << s.reverse(x) << std::endl;
  return 0;
}
