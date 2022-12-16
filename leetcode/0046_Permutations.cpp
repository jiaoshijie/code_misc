#include "head.hpp"

class Solution {
public:
  void dfs(std::vector<int>& nums, std::vector<std::vector<int>> &res, std::vector<int> &t, bool *flag) {
    if (t.size() == nums.size()) {
      res.push_back(t);
      return;
    }
    for (size_t i = 0; i < nums.size(); i++) {
      if (flag[i]) {
        flag[i] = false;
        t.push_back(nums[i]);
        dfs(nums, res, t, flag);
        t.pop_back();
        flag[i] = true;
      }
    }
  }
  std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    bool *flag = new bool[nums.size()];
    memset(flag, true, sizeof(bool) * nums.size());
    std::vector<int> t;
    for (size_t i = 0; i < nums.size(); i++) {
      t.push_back(nums[i]);
      flag[i] = false;
      dfs(nums, res, t, flag);
      t.pop_back();
      flag[i] = true;
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> v = {1};
  s.permute(v);
  return 0;
}
