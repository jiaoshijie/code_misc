#include "head.hpp"

// TODO: 优化时间 6.71% 😭
// write a article

class Solution {
public:
  int maxArea(std::vector<int>& height) {
    int res = 0, l = 0, r = height.size() - 1, width, cur;
    while (l < r) {
      width = r - l;
      // cur = width * std::min(height[l], height[r]);
      cur = width * (height[l] > height[r] ? height[r] : height[l]);
      if (cur > res) {
        res = cur;
      }
      if (height[l] < height[r]) {
        while(l < r && height[l + 1] < height[l]) l++;
        l++;
      } else {  // height[l] >= height[r]
        while(l < r && height[r - 1] < height[r]) r--;
        r--;
      }
    }
    return res;
  }
};

int main() {
  std::vector<int> v({1, 2, 1});
  Solution s;
  std::cout << s.maxArea(v) << std::endl;
  return 0;
}
