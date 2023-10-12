#include "head.hpp"

using std::vector;

class Solution {
public:
  int findLength(vector<int>& nums1, vector<int>& nums2) {
    vector<vector<int>> dp(nums1.size(), vector<int>(nums2.size(), 0));
    int ret = 0;
    for (size_t i = 0; i < nums1.size(); ++i) {
      if (nums1[i] == nums2[0]) {
        dp[i][0] = 1;
        ret = 1;
      }
    }
    for (size_t i = 0; i < nums2.size(); ++i) {
      if (nums2[i] == nums1[0]) {
        dp[0][i] = 1;
        ret = 1;
      }
    }

    for (size_t i = 1; i < nums1.size(); ++i) {
      for (size_t j = 1; j < nums2.size(); ++j) {
        if (nums1[i] == nums2[j]) {
          dp[i][j] = 1 + (nums1[i - 1] == nums2[j - 1] ? dp[i - 1][j - 1] : 0);
          ret = std::max(ret, dp[i][j]);
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution s;
  vector<int> v1{1, 1, 1, 1, 1}, v2{1, 1, 1, 1, 1};
  std::cout << s.findLength(v1, v2) << std::endl;
  return 0;
}
