#include "head.hpp"

class Solution {
public:
  // NOTICE: TIMEOUT
  // bool dfs(std::vector<int>& nums, size_t pos) {
  //   if (pos >= nums.size() - 1) return true;
  //   if (nums[pos] == 0) return false;
  //   for (int i = 1; i <= nums[pos]; i++) {
  //     if (dfs(nums, pos + i)) return true;
  //   }
  //   return false;
  // }

  bool canJump(std::vector<int> &nums) {
    // if (dfs(nums, 0)) return true;
    // NOTICE: IT'S OK
    size_t i = 0;
    while(i < nums.size() - 1) {
      if (nums[i] == 0) return false;
      int temp = 0;
      for (int j = 1; j <= nums[i]; j++) {
        if (i + j >= nums.size() - 1) return true;
        if (!temp || j + nums[i + j] >= temp + nums[i + temp])
          temp = j;
      }
      i += temp;
    }
    return true;
  }
};

int main() {
  std::vector<int> nums = {3,2,1,0,4};
  Solution s;
  std::cout << s.canJump(nums) << std::endl;
  return 0;
}
