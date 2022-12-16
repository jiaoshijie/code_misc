#include "head.hpp"

class Solution {
public:
  int Pow10(int i) {
    int res = 1;
    while (i--) {
      res *= 10;
    }
    return res;
  }
  bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    int digitCapacity = 0;
    int temp = x;
    while (temp) {
      temp /= 10;
      digitCapacity++;
    }
    int t = 0;
    temp = x;
    for (int i = 0; i < digitCapacity / 2; i++) {
      t = t * 10 + temp % 10;
      temp /= 10;
    }
    return t == (x / Pow10(digitCapacity - digitCapacity / 2)) ? true : false;
  }
};

int main() {
  std::cout << std::boolalpha;
  Solution s;
  std::cout << s.isPalindrome(123454321) << std::endl;
  return 0;
}
