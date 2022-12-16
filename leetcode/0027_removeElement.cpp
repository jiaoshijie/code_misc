#include "head.hpp"

class Solution {
public:
  int removeElement(std::vector<int>& nums, int val) {
    if (nums.empty()) return 0;
    int res = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
      if (nums[i] != val) {
        nums[res++] = nums[i];
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> nums({0, 1, 2, 2, 3, 0, 4, 2});
  int res = s.removeElement(nums, 2);
  for (int i = 0; i < res; i++) {
    std::cout << nums[i] << std::endl;
  }
  return 0;
}
