#include "head.hpp"

class Solution {
public:
#if 0
  int count(std::vector<int>& nums, int s, int e) {
    int sum = 0;
    for (int i = s; i <= e; i++) {
      sum += nums[i];
    }
    return sum;
  }
  void dfs(std::vector<int>& nums, int len, int m, int s, int e, int sum, int &res) {
    if (len == 0) return;
    sum = sum - nums[m];
    if (sum > res) res = sum;
    dfs(nums, len - 1, s, s + 1, e, sum, res);
    dfs(nums, len - 1, e, s, e - 1, sum, res);
  }
  int maxSubArray_dfs_timeout(std::vector<int>& nums) {
    int sum = count(nums, 0, nums.size() - 1);
    int res = sum;
    dfs(nums, nums.size() - 1, 0, 1, nums.size() - 1, sum, res);
    dfs(nums, nums.size() - 1, nums.size() - 1, 0, nums.size() - 2, sum, res);
    return res;
  }
#endif
  // https://www.tutorialcup.com/interview/array/maximum-subarray.htm
  // https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d
  // TODO: write a article
  int maxSubArray(std::vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    int max = nums[0], tempMax = max;
    for (size_t i = 1; i < nums.size(); i++) {
      tempMax = std::max(nums[i], tempMax + nums[i]);
      max = std::max(max, tempMax);
    }
    return max;
  }
};

int main() {
  Solution s;
  // std::vector<int> nums = {-1, -1, 9, -1, -1};
  // std::vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
  std::vector<int> nums = {5, 4, -1, 7, 8};
  // std::vector<int> nums = {-3, 1, -2, 2};
  // std::vector<int> nums = {-1, -2};
  // std::vector<int> nums = { -84,-87,-78,-16,-94,-36,-87,-93,-50,-22,-63,-28,-91,-60,-64,-27,-41,-27,-73,-37,-12,-69,-68,-30,-83,-31,-63,-24,-68,-36,-30,-3,-23,-59,-70,-68,-94,-57,-12,-43,-30,-74,-22,-20,-85,-38,-99,-25,-16,-71,-14,-27,-92,-81,-57,-74,-63,-71,-97,-82,-6,-26,-85,-28,-37,-6,-47,-30,-14,-58,-25,-96,-83,-46,-15,-68,-35,-65,-44,-51,-88,-9,-77,-79,-89,-85,-4,-52,-55,-100,-33,-61,-77,-69,-40,-13,-27,-87,-95,-40 };
  std::cout << s.maxSubArray(nums) << std::endl;
  return 0;
}
