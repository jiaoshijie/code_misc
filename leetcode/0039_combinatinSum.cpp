#include "head.hpp"

class Solution {
public:
  void dfs(size_t index, std::vector<int> &c, int target, std::vector<std::vector<int>> &out, std::vector<int> t, int sum) {
    if (sum == target) {
      out.push_back(t);
    }
    if (index == c.size()) return;
    for (int i = index; i < c.size(); i++) {
      if (t.empty() || sum + c[i] <= target) {
        t.push_back(c[i]);
        dfs(i, c, target, out, t, sum + c[i]);
        t.pop_back();
      }
    }
  }

  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
    std::vector<std::vector<int>> out;
    std::vector<int> t;
    std::sort(candidates.begin(), candidates.end(), [](int a, int b){
          return a > b;
        });
    dfs(0, candidates, target, out, t, 0);
    return out;
  }
};

int main() {
  Solution s;
  std::vector<int> candidates = {2};
  auto res = s.combinationSum(candidates, 7);
  int i = 1;
  return 0;
}
