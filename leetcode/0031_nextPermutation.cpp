#include "head.hpp"

class Solution {
public:
  void nextPermutation(std::vector<int>& nums) {
    if (nums.size() == 1) return;
    int tail = nums.size() - 1;
    while (tail > 0) {
      if (nums[tail] > nums[tail - 1]) {
        int i = tail;
        while(i + 1 < (int)nums.size() && nums[i + 1] > nums[tail - 1]) i++;
        int temp = nums[i];
        nums[i] = nums[tail];
        nums[tail] = nums[tail - 1];
        nums[tail - 1] = temp;
        break;
      }
      tail--;
    }
    std::sort(&nums[tail], &nums[nums.size()]);
  }
};

int main() {
  Solution s;
  std::vector<int> v({3, 2, 1});
  s.nextPermutation(v);
  for (auto i : v) {
    std::cout << i << std::endl;
  }
  return 0;
}
