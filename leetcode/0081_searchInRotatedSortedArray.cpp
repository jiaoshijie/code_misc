#include "head.hpp"

using std::vector;

class Solution {
public:
  bool search_ver1(vector<int>& nums, int target) {
    bool found = false;
    for (auto i: nums) {
      if (i == target) {
        found = true;
        break;
      }
    }
    return found;
  }

  bool search(vector<int>& nums, int target) {
    bool found = false;
    int pivot = 0;
    for (int i = 0; i < int(nums.size()); i++) {
      if (nums[i] == target) {
        found = true;
        break;
      }
      if (i > 0 && nums[i] < nums[i - 1]) {
        pivot = i + 1;
        break;
      }
    }
    int l = 0, r = nums.size() - pivot;
    while (!found && l < r) {
      int mid = (l + r) / 2;
      if (nums[pivot + mid] == target) {
        found = true;
        break;
      } else if (nums[pivot + mid] > target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return found;
  }
};

int main() {
  Solution s;
  return 0;
}
