#include "head.hpp"

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

  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i == 0 && j == 0) continue;
        if (obstacleGrid[i][j] == 0)
          dp[i][j] = (i - 1 >= 0 ? dp[i - 1][j] : 0) + (j - 1 >= 0 ? dp[i][j - 1] : 0);
        else
          dp[i][j] = 0;
      }
    }
    return dp[m - 1][n - 1];
  }
};

int main() {
  Solution s;
  vector<vector<int>> arr(3, vector<int>(2, 0));
  arr[1][0] = 1;
  arr[1][1] = 1;
  std::cout << s.uniquePathsWithObstacles(arr) << std::endl;
  return 0;
}
