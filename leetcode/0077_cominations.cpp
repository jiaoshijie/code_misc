#include "head.hpp"

using std::vector;

class Solution {
public:
  void dfs(vector<vector<int>>& res, vector<int>& item, vector<bool>& flags, int n, int k) {
    if (int(item.size()) == k) {
      res.push_back(item);
      return;
    }
    int init = item.empty() ? 1 : item.back();
    for (int i = init; i <= n; i++) {
      if (!flags[i]) {
        item.push_back(i);
        flags[i] = true;
        dfs(res, item, flags, n, k);
        item.pop_back();
        flags[i] = false;
      }
    }
  }

  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ret;
    vector<int> item;
    vector<bool> flags(n, false);
    dfs(ret, item, flags, n, k);
    return ret;
  }
};

int main() {
  Solution s;
  vector<vector<int>> ret = s.combine(20, 10);
  for (auto item: ret) {
    for (auto i: item) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
