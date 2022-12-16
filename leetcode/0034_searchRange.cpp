#include "head.hpp"

// NOTE: 94.50%

class Solution {
public:
  std::vector<int> searchRange(std::vector<int> &nums, int target) {
    std::vector<int> res = {-1, -1};
    dfs(nums, 0, nums.size() - 1, target, res);
    return res;
  }
private:
  void dfs(std::vector<int> &nums, int start, int end, int target, std::vector<int> &res) {
    if (start > end) return;
    if (nums[start] > target || nums[end] < target) return;

    if (start == end) {
      if (nums[start] == target) {
        if (res[0] == -1 || res[0] > start) res[0] = start;
        if (res[1] == -1 || res[1] < start) res[1] = start;
      }
      return;
    }
    dfs(nums, start, (start + end) / 2, target, res);
    dfs(nums, (start + end) / 2 + 1, end, target, res);
  }
};

int main() {
  Solution s;
  // std::vector<int> nums = {5, 7, 7, 8, 8, 10};
  std::vector<int> nums = {};
  std::vector<int> res = s.searchRange(nums, 0);
  for (auto it = res.begin(); it != res.end(); it++) {
    std::cout << *it << std::endl;
  }
  return 0;
}
