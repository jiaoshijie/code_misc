#include "head.hpp"

using std::vector;

class Solution {
public:
  // NOTICE: timeout
  void min(vector<int>& heights, int l, int r, int& max) {
    if (l >= r) return;
    int min_i = l, min_v = heights[l];
    for (int i = l; i < r; i++) {
      if (heights[i] < min_v) {
        min_v = heights[i];
        min_i = i;
      }
    }
    max = std::max(max, (r - l) * min_v);
    min(heights, l, min_i, max);
    min(heights, min_i + 1, r, max);
  }

  int largestRectangleArea_ver1(vector<int>& heights) {
    int ret = 0;
    min(heights, 0, heights.size(), ret);
    return ret;
  }

  // -------------------------------------------------------------------------
  // NOTICE: timeout
  int largestRectangleArea_ver2(vector<int>& heights) {
    int ret = 0;
    for (int i = 0; i < int(heights.size()); i++) {
      int j = i, w = 0;
      while (j >= 0 && heights[j] < heights[i]) {
        w++;
        j--;
      }
      j = i + 1;
      while (j < int(heights.size()) && heights[j] < heights[i]) {
        w++;
        j++;
      }
      ret = std::max(ret, w * heights[i]);
    }
    return ret;
  }

  // -------------------------------------------------------------------------
  // 单调栈
  int largestRectangleArea(vector<int>& heights) {
    int ret = 0;
    vector<int> stack;
    heights.push_back(0);
    int len = heights.size();
    for (int i = 0; i < len; i++) {
      while (!stack.empty() && heights[i] < heights[stack.back()]) {
        int h = heights[stack.back()];
        stack.pop_back();
        ret = std::max(ret, (stack.empty() ? i : (i - stack.back() - 1)) * h);
      }
      stack.push_back(i);
    }
    return ret;
  }
};

int main() {
  Solution s;
  // vector<int> heights = {2, 1, 5, 6, 2, 3};  // 10
  // vector<int> heights = {5,5,1,7,1,1,5,2,7,6};  // 12
  vector<int> heights = {2, 4};  // 4
  std::cout << s.largestRectangleArea(heights) << std::endl;
  return 0;
}
