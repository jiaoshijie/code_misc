#include "head.hpp"

class Solution {
public:
  void dfs(int m, int n, int& res, int x, int y) {
    if (x == m - 1 && y == n - 1) {
      res++;
      return;
    }
    if (x + 1 <= m - 1) {
      dfs(m, n, res, x + 1, y);
    }
    if (y + 1 <= n - 1) {
      dfs(m, n, res, x, y + 1);
    }
  }

  int uniquePaths(int m, int n) {
    // 排列组合解法
    int res = 1;
    // dfs(m, n, res, 0, 0);
    // https://zhidao.baidu.com/question/119384779.html
    // https://jl.huatu.com/2014/0114/862088.html
    int d = n + m - 2, u = m - 1;
    unsigned long long uu = 1, dd = 1;
    if (u == 0 || d == u) return 1;
    if (u > d - u) u = d - u;
    for (int i = 1; i <= u; i++) {
      uu *= i;
      dd *= d--;
      if (dd % uu == 0) {
        res = (res * dd) / uu;
        dd = 1;
        uu = 1;
      }
    }
    res = (res * dd) / uu;
    return res;
  }

  // TODO: 动态规划解法
};

int main() {
  Solution s;
  std::cout << s.uniquePaths(3, 3) << std::endl;
  return 0;
}
