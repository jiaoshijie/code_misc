#include "head.hpp"

using std::vector;

class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    int *dp = new int[nums.size()];
    for (size_t i = 0; i < nums.size(); ++i) {
      int j = i - 1;
      dp[i] = 1;
      for (; j >= 0; --j) {
        if (nums[i] > nums[j]) {
          dp[i] = std::max(dp[i], dp[j] + 1);
        }
      }
    }

    return *std::max_element(dp, dp + nums.size());
  }
};

int main() {
  Solution s;
  vector<int> v1{10, 9, 2, 5, 3, 7, 101, 18};
  std::cout << s.lengthOfLIS(v1) << std::endl;
  vector<int> v2{0, 1, 0, 3, 2, 3};
  std::cout << s.lengthOfLIS(v2) << std::endl;
  vector<int> v3{7, 7, 7, 7};
  std::cout << s.lengthOfLIS(v3) << std::endl;
  return 0;
}
