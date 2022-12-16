#include "head.hpp"

// NOTE: 77.78%

class Solution {
public:
  int searchInsert(std::vector<int>& nums, int target) {
    int s = 0, e = nums.size() - 1;
    while(s <= e) {
      if (s == e) {
        if (nums[s] < target) return s + 1;
        else return s;
      }
      int mid = (s + e) / 2;
      if (nums[mid] == target) return mid;
      else if (nums[mid] < target) s = mid + 1;
      else e = mid - 1;
    }
    return s;
  }
};

int main() {
  Solution s;
  std::vector<int> nums = {1};
  std::cout << s.searchInsert(nums, 0) << std::endl;
  return 0;
}
