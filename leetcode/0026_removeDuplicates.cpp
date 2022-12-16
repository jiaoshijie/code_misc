#include "head.hpp"

class Solution {
public:
  int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int res = 1, modify = 1, lastnum = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
      if (nums[i] != lastnum) {
        lastnum = nums[i];
        nums[modify++] = nums[i];
        res++;
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> nums({0, 0, 1, 1, 1, 2, 2, 3, 3, 4});
  int len = s.removeDuplicates(nums);
  for (int i = 0; i < len; i++) {
    std::cout << nums[i] << std::endl;
  }
  return 0;
}
