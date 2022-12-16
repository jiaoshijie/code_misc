#include "head.hpp"

class Solution {
public:
  int mySqrt(int x) {
    if (x < 2) return x;
    if (x < 4) return 1;
    unsigned int l = 0, r = 65536, mid = 0, last_mid = 1;
    while(l < r) {
      mid = (l + r) / 2;
      if (last_mid == mid) return mid;
      last_mid = mid;
      if (mid * mid > x) {
        r = mid;
      }
      else if (mid * mid < x) {
        l = mid;
      }
      else return mid;
    }

    return r;
  }
};

int main() {
  Solution s;
  std::cout << s.mySqrt(2147395599) << std::endl;
  return 0;
}
