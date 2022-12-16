#include "head.hpp"

// https://www.tutorialcup.com/interview/array/first-missing-positive.htm
/*
 * 思路:
 * */

class Solution {
public:
  int firstMissingPositive(std::vector<int>& nums) {
    int len = nums.size(), num, nextnum;
    for (int i = 0; i < len; i++) {
      if (nums[i] <= 0 || nums[i] > len) continue;
      num = nums[i];
      while(nums[num - 1] != num) {
        nextnum = nums[num - 1];
        nums[num - 1] = num;
        num = nextnum;
        if (num <= 0 || num > len) break;
      }
    }
    for (int i = 0; i < len; i++) {
      if (nums[i] != i + 1) return i + 1;
    }
    return len + 1;
  }
};

int main() {
  Solution s;
  std::vector<int> nums = {7,8,9,11,12};
  std::cout << s.firstMissingPositive(nums) << std::endl;
  return 0;
}
