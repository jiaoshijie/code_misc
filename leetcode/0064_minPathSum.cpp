#include "head.hpp"

// 动态规划

using std::vector;

class Solution {
public:
  void print(vector<vector<int>>& arr) {
    for (auto i: arr) {
      for (auto j: i) {
        std::cout << j << ' ';
      }
      std::cout << std::endl;
    }
  }

  int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int i = 1; i < n; i++) dp[0][i] = dp[0][i - 1] + grid[0][i];
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + grid[i][j];
      }
    }
    return dp[m - 1][n - 1];
  }
};

int main() {
  Solution s;
  // vector<vector<int>> arr = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  vector<vector<int>> arr = {{1, 2, 3}, {4, 5, 6}};
  std::cout << s.minPathSum(arr) << std::endl;
  return 0;
}
