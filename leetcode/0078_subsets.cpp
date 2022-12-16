#include "head.hpp"

using std::vector;

class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ret;
    ret.push_back(vector<int>{});
    for (auto i: nums) {
      int len = ret.size();
      for (int j = 0; j < len; j++) {
        vector<int> temp = ret[j];
        temp.push_back(i);
        ret.push_back(temp);
      }
    }
    return ret;
  }
};

int main() {
  Solution s;
  vector<int> nums = {1, 2, 3};
  auto ret = s.subsets(nums);
  for (auto item: ret) {
    for (auto i: item) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
