#include "head.hpp"

/**
 * TODO: 优化时间 44.07% 😭
 * 思路:
 * 1. 将数组排序
 * 2. 依次取一个数的相反数target
 * 3. 使用双指针法来遍历
 * wirte a article
 * */

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    if (nums.size() < 3) return res;
    // -4 -1 -1 0 1 2
    std::sort(nums.begin(), nums.end());
    int left = 0, right = nums.size() - 1, index = 0, target = nums[index] * -1;
    while(index < (int)nums.size()) {
      target = nums[index] * -1;
      left = index + 1;  // DONE: Why is this "index + 1"?
      right = nums.size() - 1;
      while(left < right) {
        if (nums[left] + nums[right] == target) {
          res.push_back(std::vector<int>({nums[left], nums[right], nums[index]}));
          left++;
          right--;
          while(left < right && nums[left] == nums[left - 1]) left++;
          while(left < right && nums[right] == nums[right + 1]) right--;
        } else if (nums[left] + nums[right] > target) {
          right--;
        } else if (nums[left] + nums[right] < target) {
          left++;
        }
      }
      index++;
      while(index < right && nums[index] == nums[index - 1]) index++;
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> nums({0, 0, 0, 0});
  auto res = s.threeSum(nums);
  for (auto i : res) {
    for (auto j : i) {
      std::cout << j << ' ';
    }
    std::cout << std::endl;
  }
  return 0;
}
