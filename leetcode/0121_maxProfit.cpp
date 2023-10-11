#include "head.hpp"

using std::vector;

class Solution {
public:
  int maxProfit_timeout(vector<int>& prices) {
    int *dp = new int[prices.size()]{0};
    int max = 0;

    for (int i = 1; i < prices.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (prices[i] > prices[j]) {
          dp[i] = std::max(dp[i], dp[j] + prices[i] - prices[j]);
          max = std::max(max, dp[i]);
        }
      }
    }
    return max;
  }

  int maxProfix(vector<int>& prices) {
    // see ./0121_max_profit.rs
  }
};

int main() {
  Solution s;
  vector<int> v1{7, 1, 5, 3, 6, 4};
  std::cout << s.maxProfit(v1) << std::endl;
  vector<int> v2{7, 6, 4, 3, 1};
  std::cout << s.maxProfit(v2) << std::endl;
  return 0;
}
