#include "head.hpp"

class Solution {
public:
  struct Uni {
    int num;
    int index;
    Uni(int i, int j) : num(i), index(j) {}
  };
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::vector<Uni> inums;
    for (int i = 0; i < (int)nums.size(); i++) {
      inums.push_back(Uni(nums[i], i));
    }
    std::sort(inums.begin(), inums.end(), [](const Uni& a, const Uni& b) {
          if (a.num > b.num) return false;
          return true;
        });
    int l = 0, r = inums.size() - 1;
    while (l < r) {
      if (inums[l].num + inums[r].num > target) {
       r--;
      } else if (inums[l].num + inums[r].num < target) {
       l++;
      } else if (inums[l].num + inums[r].num == target) {
       return std::vector<int>({inums[l].index, inums[r].index});
     }
    }
    return std::vector<int>({-1, -1});;
  }
};

int main() {
  Solution s;
  std::vector<int> arr({3, 2, 4});
  std::vector<int> res = s.twoSum(arr, 6);
  for (int i : res) {
    std::cout << i << std::endl;
  }
  return 0;
}
