#include "head.hpp"

using std::vector;

class Solution {
public:
  int change_2dim_array(int amount, vector<int>& coins) {
    vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, 0));

    for (size_t i = 0; i < coins.size(); ++i) {
      dp[i][0] = 1;
    }

    for (size_t i = 0; i < coins.size(); ++i) {
      for (int j = 1; j < amount + 1; ++j) {
        if (coins[i] <= j) {
          dp[i][j] = dp[i][j - coins[i]];
        }
        if (i > 0) {
          dp[i][j] += dp[i - 1][j];
        }
      }
    }
    return dp[coins.size() - 1][amount];
  }
  int change(int amount, vector<int>& coins) {
    // vector<int> dp(amount + 1, 0);
    int *dp = new int[amount + 1]{0};
    dp[0] = 1;
    for (size_t i = 0; i < coins.size(); ++i) {
      for (int j = 1; j < amount + 1; ++j) {
        if (coins[i] <= j) {
          dp[j] += dp[j - coins[i]];
        }
      }
    }
    return dp[amount];
  }
};

int main() {
  Solution s;
  vector<int> v1{1, 2, 5};
  std::cout << s.change(5, v1) << std::endl;
  vector<int> v2{2};
  std::cout << s.change(3, v2) << std::endl;
  vector<int> v3{10};
  std::cout << s.change(10, v3) << std::endl;
  return 0;
}
