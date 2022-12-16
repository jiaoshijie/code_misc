#include "head.hpp"

class Solution {
public:
  bool isHereOK(std::vector<std::pair<int, int>> &tt, int x) {
    int y = int(tt.size());
    for (int i = 0; i < int(tt.size()); i++) {
      if (tt[i].second == x || abs(x - tt[i].second) == abs(y - tt[i].first)) return false;
    }
    return true;
  }
  void dfs(int &out, std::vector<std::pair<int, int>> &tt, int n) {
    if (int(tt.size()) == n) {
      out++;
      return;
    }
    for (int i = 0; i < n; i++) {
      if (isHereOK(tt, i)) {
        tt.push_back(std::make_pair(int(tt.size()), i));
        dfs(out, tt, n);
        tt.pop_back();
      }
    }
  }
  int totalNQueens(int n) {
    int out = 0;
    std::vector<std::pair<int, int>> tt;
    for (int i = 0; i < n; i++) {
      tt.push_back(std::make_pair(0, i));
      dfs(out, tt, n);
      tt.pop_back();
    }
    return out;
  }
};

int main() {
  Solution s;
  std::cout << s.totalNQueens(9) << std::endl;
  return 0;
}
