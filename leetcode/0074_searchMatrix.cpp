#include "head.hpp"

using std::vector;

class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    size_t f = 0, e = matrix.size(), l = 0, r = matrix[0].size();
    size_t line = (f + e) / 2, col = 0;
    while (f < e && line) {
      line = (f + e) / 2;
      if (matrix[line][0] == target)
        return true;
      else if (matrix[line][0] > target) {
        e = line;
      } else { // matrix[line][0] < target
        f = line + 1;
      }
    }
    if (!line && matrix[line][0] > target)
      return false;
    else if (matrix[line][0] > target)
      line--;
    while (l < r) {
      col = (l + r) / 2;
      if (matrix[line][col] == target)
        return true;
      else if (matrix[line][col] > target) {
        r = col;
      } else {
        l = col + 1;
      }
    }
    return false;
  }
};

int main() {
  Solution s;
  vector<vector<int>> matrix = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  std::cout << s.searchMatrix(matrix, 61) << std::endl;
  return 0;
}
