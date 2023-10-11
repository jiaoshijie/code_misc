#include "head.hpp"

using std::vector;

class Solution {
public:
  int findLengthOfLCIS(vector<int>& nums) {
    int ret = 1;
    int l = 0, r = 1;
    while (r < nums.size()) {
      if (nums[r] > nums[r - 1]) r++;
      else {
        ret = std::max(ret, r - l);
        l = r;
        r = l + 1;
      }
    }
    ret = std::max(ret, r - l);
    return ret;
  }
};

int main() {
  Solution s;
  return 0;
}
