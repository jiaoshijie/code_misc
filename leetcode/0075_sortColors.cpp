#include "head.hpp"

using std::vector;

class Solution {
public:
  void sortColors(vector<int> &nums) {
    size_t red = 0, white = 0, len = nums.size();
    for (auto i : nums) {
      if (i == 0)
        red++;
      else if (i == 1)
        white++;
    }
    white = red + white;
    size_t i = 0;
    while (i < red)
      nums[i++] = 0;
    while (i < white)
      nums[i++] = 1;
    while (i < len) nums[i++] = 2;
  }
};

int main() {
  Solution s;
  vector<int> nums = {2, 0, 2, 1, 1, 0};
  s.sortColors(nums);
  for (auto i : nums) {
    std::cout << i;
  }
  std::cout << std::endl;
  return 0;
}
