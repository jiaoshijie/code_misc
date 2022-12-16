#include "head.hpp"

class Solution {
public:
  bool dfs(std::string& src, std::vector<bool>& flag, int k, int& count, std::string& res, int d) {
    if (d == int(src.size())) {
      count++;
      if (k == count) return true;
      else return false;
    }
    for (int i = 0; i < int(src.size()); i++) {
      if (!flag[i]) {
        flag[i] = true;
        res.push_back(src[i]);
        if (dfs(src, flag, k, count, res, d + 1)) return true;
        flag[i] = false;
        res.pop_back();
      }
    }
    return false;
  }

  std::string getPermutation(int n, int k) {
    std::string res, src;
    std::vector<bool> flag(n, false);
    int count = 0;
    for (int i = 1; i <= n; i++) {
      src.push_back(i + 48);
    }
    dfs(src, flag, k, count, res, 0);
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.getPermutation(3, 1) << std::endl;
  return 0;
}
