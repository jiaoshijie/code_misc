#include "head.hpp"

// TODO: 25.58%

class Solution {
public:
  int search(std::vector<int>& nums, int target) {
    if (nums.empty()) return -1;
    if (nums.size() == 1 && nums[0] == target) return 0;
    else if (nums.size() == 1 && nums[0] != target) return -1;
    int res = -1, split = 0, start = 0, end = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
      if (nums[i] > nums[i + 1]) {
        split = i + 1;
        break;
      }
    }

    if (target >= nums[0]) {
      start = 0;
      end = split ? split : (int)nums.size();
    } else {
      start = split;
      end = (int)nums.size();
    }

    for (;start < end; start++) {
      if (nums[start] == target) {
        res = start;
        break;
      }
    }
    return res;
  }
};

int main() {
  std::vector<int> arr = {1, 3};
  Solution s;
  std::cout << s.search(arr, 1) << std::endl;
  return 0;
}
