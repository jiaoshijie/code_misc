#include "head.hpp"

class Solution {
public:
  std::string setQ(int i, int n) {
    std::string st = "";
    for (int j = 0; j < n; j++) {
      if (j == i) st+= 'Q';
      else st += '.';
    }
    return st;
  }
  bool isHereOK(std::vector<std::string> &tt, int x, int n) {
    int y = int(tt.size());
    for (int i = 0; i < int(tt.size()); i++) {
      for (int j = 0; j < n; j++) {
        if (tt[i][j] == 'Q' && (j == x || abs(x - j) == abs(y - i))) return false;
      }
    }
    return true;
  }
  void dfs(std::vector<std::vector<std::string>> &out, std::vector<std::string> &tt, int n) {
    if (int(tt.size()) == n) {
      out.push_back(tt);
      return;
    }
    for (int i = 0; i < n; i++) {
      if (isHereOK(tt, i, n)) {
        tt.push_back(setQ(i, n));
        dfs(out, tt, n);
        tt.pop_back();
      }
    }
  }
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> out;
    std::vector<std::string> tt;
    for (int i = 0; i < n; i++) {
      tt.push_back(setQ(i, n));
      dfs(out, tt, n);
      tt.pop_back();
    }
    return out;
  }
};

int main() {
  Solution s;
  auto out = s.solveNQueens(9);
  return 0;
}
