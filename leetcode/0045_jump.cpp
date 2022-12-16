#include "head.hpp"

class Solution {
public:
  int jump(std::vector<int>& nums) {
    if (nums.size() == 1) return 0;
    size_t out = 0, i = 0, j = 0;
    while(i < nums.size()) {
      if (nums[i] + i >= nums.size() - 1) {
        out++;
        break;
      }
      j = i + 1;
      size_t len = 0, t = j;
      while(j <= i + nums[i]) {
        if (j - i + nums[j] > len) {
          len = j - i + nums[j];
          t = j;
        }
        j++;
      }
      i = t;
      out++;
    }
    return out;
  }
};

int main() {
  Solution s;
  std::vector<int> array = {1, 2};
  std::cout << s.jump(array) << std::endl;
  return 0;
}
