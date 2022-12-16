#include "head.hpp"

class Solution {
public:
  void dfs(std::vector<int>& nums, std::vector<std::vector<int>> &res, std::vector<int> &t, bool *flag) {
    if (t.size() == nums.size()) {
      res.push_back(t);
      return;
    }
    int f = 11;
    for (size_t i = 0; i < nums.size(); i++) {
      if (flag[i] && f != nums[i]) {
        f = nums[i];
        flag[i] = false;
        t.push_back(nums[i]);
        dfs(nums, res, t, flag);
        t.pop_back();
        flag[i] = true;
      }
    }
  }
  std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    bool *flag = new bool[nums.size()];
    memset(flag, true, sizeof(bool) * nums.size());
    std::vector<int> t;
    int f = 11;
    for (size_t i = 0; i < nums.size(); i++) {
      if (f != nums[i]) {
        f = nums[i];
        t.push_back(nums[i]);
        flag[i] = false;
        dfs(nums, res, t, flag);
        t.pop_back();
        flag[i] = true;
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> v = {1, 2, 3};
  s.permuteUnique(v);
  return 0;
}
