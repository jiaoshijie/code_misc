#include "head.hpp"

class Solution {
public:
  int absValue(int i) {
    return i > 0 ? i : i * -1;
  }

  int threeSumClosest(std::vector<int>& nums, int target) {
    /**
     * 暴力枚举法
     * NOTICE TIME: 5.09%
     * */
    int res = 99999;
    for (int i = 0; i < (int)nums.size() - 2; i++) {
      for (int j = i + 1; j < (int)nums.size() - 1; j++) {
        for (int k = j + 1; k < (int)nums.size(); k++) {
          int temp = nums[i] + nums[j] + nums[k];
          if (absValue(temp - target) < absValue(res - target)) res = temp;
        }
      }
    }
    return res;
  }


  int threeSumClosest01(std::vector<int>& nums, int target) {
    /**
     * TODO: write a article
     * */
  }
};

int main() {
  Solution s;
  std::vector<int> v({0, 1, 2});
  std::cout << s.threeSumClosest(v, 0) << std::endl;
  return 0;
}
