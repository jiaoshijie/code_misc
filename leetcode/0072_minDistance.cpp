#include "head.hpp"

// 动态规划

using std::string;

class Solution {
public:
  int minDistance(string word1, string word2) {
    int len1 = word1.size(), len2 = word2.size();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int i = 0; i <= len2; i++) dp[0][i] = i;
    for (int i = 1; i <= len1; i++) {
      for (int j = 1; j <= len2; j++) {
        if (word1[i - 1] == word2[j - 1])
          dp[i][j] = dp[i - 1][j - 1];
        else
          // i-1, j-1 for replace
          // i, j-1 for delete
          // i-1, j for insert
          dp[i][j] = 1 + std::min(std::min(dp[i - 1][j - 1], dp[i][j - 1]), dp[i - 1][j]);
      }
    }

    return dp[len1][len2];
  }
};

int main() {
  Solution s;
  std::cout << s.minDistance("horse", "ros") << std::endl;
  return 0;
}
