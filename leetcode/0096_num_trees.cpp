#include "head.hpp"

class Solution {
public:
  int numTrees(int n) {
    int *arr = new int[n + 1];
    arr[0] = 1;
    arr[1] = 1;
    for (int i = 2; i <= n; ++i) {
      int res = 0;
      for (int j = 0; j < i; ++j) {
        res += arr[j] * arr[i - j - 1];
      }
      arr[i] = res;
    }
    return arr[n];
  }
};

int main() {
  Solution s;
  std::cout << s.numTrees(19) << std::endl;
  assert(s.numTrees(3) == 5);
  assert(s.numTrees(2) == 2);
  assert(s.numTrees(1) == 1);
  return 0;
}
