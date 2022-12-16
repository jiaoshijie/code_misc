#include "head.hpp"

// TODO: Maybe the implementation is awful, but who care 😂.

class Solution {
public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    std::vector<int> out;
    int m = int(matrix.size()), n = int(matrix[0].size());
    int ii = m % 2 ? m / 2 + 1 : m / 2;
    bool flag = true;
    for (int i = 0; i < ii; i++) {
      for (int j = i; j < n - i; j++) {
        flag = false;
        out.push_back(matrix[i][j]);
      }
      if (flag) break;
      flag = true;
      for (int j = i + 1; j < m - i; j++) {
        flag = false;
        out.push_back(matrix[j][n - 1 - i]);
      }
      if (flag) break;
      flag = true;
      for (int j = n - 1 - i - 1; j >= i; j--) {
        flag = false;
        out.push_back(matrix[m - 1 - i][j]);
      }
      if (flag) break;
      flag = true;
      for (int j = m - 1 - i - 1; j > i; j--) {
        flag = false;
        out.push_back(matrix[j][i]);
      }
      if (flag) break;
      flag = true;
    }
    return out;
  }
};

int main() {
  Solution s;
  // std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
  // std::vector<std::vector<int>> matrix = {{2,5,8},{4,0,-1}};
  // std::vector<std::vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
  auto out = s.spiralOrder(matrix);
  int i = 0;
  return 0;
}
