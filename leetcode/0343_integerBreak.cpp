#include "head.hpp"

class Solution {
public:
  // only consider `n` divide into 2 parts.
  // if n == 10, and consider it divied into (1,9) (2,8) (3,7)...
  // and then assuming n == 9 and consider its max product, 1 * the max product of 9
  // and then 2 * the max product of 8 ......
  // select max result.
  int integerBreak(int n) {
    int *arr = new int[n + 1]{0, 0, 1};
    for (int i = 3; i <= n; ++i) {
      for (int j = 1; j <= i / 2; ++j) {
        arr[i] = std::max(arr[i], std::max(j, arr[j]) * std::max(i - j, arr[i - j]));
      }
    }
    return arr[n];
  }
};

int main() {
  Solution s;
  assert(s.integerBreak(2) == 1);
  assert(s.integerBreak(3) == 2);
  assert(s.integerBreak(10) == 36);
  return 0;
}
