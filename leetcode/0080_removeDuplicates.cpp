#include "head.hpp"

using std::vector;

class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    int k = 1, index = 1, last_num = nums[0], count = 1;
    while (index < int(nums.size())) {
      if (nums[index] != last_num) {
        last_num = nums[index];
        count = 1;
      } else {
        count++;
      }
      if (count <= 2) {
        nums[k++] = last_num;
      }
      index++;
    }
    return k;
  }
};

int main() {
  Solution s;
  vector<int> nums = {0,0,1,1,1,1,2,3,3};
  std::cout << s.removeDuplicates(nums) << std::endl;
  return 0;
}
