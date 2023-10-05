#include "head.hpp"

using std::vector;

// 0-1背包

class Solution {
public:
  bool dfs(vector<int>& nums, size_t i, int cur, int sum) {
    if (i >= nums.size()) return false;
    if (cur == sum) return true;
    bool ret = false;
    if (cur + nums[i] <= sum - nums[i]) {
      ret = dfs(nums, i + 1, cur + nums[i], sum - nums[i]);
    }
    if (!ret) {
      ret = dfs(nums, i + 1, cur, sum);
    }
    return ret;
  }
  bool canPartition_timeout(vector<int>& nums) {
    int sum = 0;
    for (auto i : nums) {
      sum += i;
    }
    return dfs(nums, 0, 0, sum);
  }

  bool canPartition_wrong(vector<int>& nums) {
    int sum = 0;
    for (auto i : nums) {
      sum += i;
    }
    std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
    int cur = 0;
    for (auto i : nums) {
      if (cur + i > sum - i) continue;
      cur += i;
      sum -= i;
      if (cur == sum) return true;
    }
    return false;
  }

  bool canPartition_passed(vector<int>& nums) {
    int sum = 0;
    for (auto i : nums) {
      sum += i;
    }
    if (sum % 2 != 0) return false;
    sum = sum / 2;

    vector<vector<int>> dp(nums.size(), vector<int>(sum + 1, 0));
    for (int i = 1; i <= sum; ++i) {
      dp[0][i] = i - nums[0];
    }

    for (size_t i = 1; i < nums.size(); ++i) {
      for (int j = 1; j <= sum; ++j) {
        int a = j - nums[i] > 0 ? dp[i - 1][j - nums[i]]: -1;
        int b = dp[i - 1][j];
        dp[i][j] = a < 0 || b < 0 ? std::max(a, b) : std::min(a, b);
        if (j == sum && dp[i][j] == 0) return true;
      }
    }
    return false;
  }

  bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (auto i : nums) {
      sum += i;
    }
    if (sum % 2 != 0) return false;
    sum = sum / 2;

    // vector<int> dp(sum + 1, 0);
    int *dp = new int[sum + 1]{0};
    for (int i = 1; i <= sum; ++i) {
      dp[i] = i - nums[0];
    }

    for (size_t i = 1; i < nums.size(); ++i) {
      for (int j = sum; j > 0; --j) {
        int a = j - nums[i] > 0 ? dp[j - nums[i]]: -1;
        int b = dp[j];
        dp[j] = a < 0 || b < 0 ? std::max(a, b) : std::min(a, b);
        if (j == sum && dp[j] == 0) return true;
      }
    }
    return false;
  }
};

int main() {
  Solution s;
  vector<int> v{1, 5, 11, 5};
  std::cout << s.canPartition(v) << std::endl;
  vector<int> v1{1, 2, 3, 5};
  std::cout << s.canPartition(v1) << std::endl;
  vector<int> v2{2, 2, 1, 1};
  std::cout << s.canPartition(v2) << std::endl;
  return 0;
}
