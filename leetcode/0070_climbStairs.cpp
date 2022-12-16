#include "head.hpp"

class Solution {
public:
  // timeout
  void dfs(int n, int c, int& res) {
    if (c == n) {
      res++;
      return;
    }
    if (c + 1 <= n) dfs(n, c + 1, res);
    if (c + 2 <= n) dfs(n, c + 2, res);
  }

  // OK: 100%
  int climbStairs1(int n) {
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }

  int climbStairs(int n) {
    if (n == 1) return 1;
    int dp[3] = {1, 1, 0};
    int i = 2;
    while(i <= n) {
      dp[i % 3] = dp[(i - 1) % 3] + dp[(i - 2) % 3];
      i++;
    }

    return dp[(i - 1) % 3];
  }
};

int main() {
  Solution s;
  std::cout << s.climbStairs(20) << std::endl;
  return 0;
}
