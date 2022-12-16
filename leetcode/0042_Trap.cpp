#include "head.hpp"

class Solution {
public:
  int trap(std::vector<int>& height) {
    int out = 0, hi = 0;
    for (int i = 1; i < int(height.size()); i++) {
      if (height[i] != 0) {
        int th = 0;
        for (int j = i - 1; j >= hi; j--) {
          if (height[j] > th) {
            if (height[j] >= height[i]) {
              out += (i - j - 1) * (height[i] - th);
              break;
            } else {
              out += (i - j - 1) * (height[j] - th);
            }
            th = height[j];
          }
        }
        if (height[hi] <= height[i]) hi = i;
      }
    }
    return out;
  }
};

int main() {
  Solution s;
  std::vector<int> h = {3, 0, 1, 0, 4, 0, 1, 0, 3};
  std::cout << s.trap(h) << std::endl;
  return 0;
}
