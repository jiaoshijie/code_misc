#include "head.hpp"

class Solution {
public:
  void rotate(std::vector<std::vector<int>>& matrix) {
    int temp;
    size_t len = matrix.size();
    for (size_t i = 0; i < matrix.size() / 2; i++) {
      for (size_t j = i; j < matrix.size() - i - 1; j++) {
        temp = matrix[i][j];
        matrix[i][j] = matrix[len - j - 1][i];
        matrix[len - j - 1][i] = matrix[len - i - 1][len - j - 1];
        matrix[len - i - 1][len - j - 1] = matrix[j][len - i - 1];
        matrix[j][len - i - 1] = temp;
      }
    }
  }
};

int main() {
  Solution s;
  std::vector<std::vector<int>> matrix = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
  s.rotate(matrix);
  int j = 0;
  return 0;
}
