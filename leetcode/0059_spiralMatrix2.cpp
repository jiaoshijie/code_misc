#include "head.hpp"

using std::vector;

class Solution {
public:
  void print(const vector<vector<int>>& m) {
    for (auto i: m) {
      for (auto j: i) {
        std::cout << j << ' ';
      }
      std::cout << std::endl;
    }
  }

  void update_step(size_t& step, size_t& stepped) {
    if (stepped == 2) {
      step--;
      stepped = 0;
    }
  }

  void get_direciton(size_t d, int* arr) {
    memset(arr, 0, sizeof(int) * 2);
    if (d == 0) arr[0] = 1;  // down
    else if (d == 1) arr[1] = -1;  // left
    else if (d == 2) arr[0] = -1;  // up
    else arr[1] = 1;  // right
  }

  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    size_t last_number = 0, step = n - 1, stepped = 0, d = 0;
    int d_arr[2] = {0, 0};
    // skip first line
    for (auto it = res[0].begin(); it != res[0].end(); it++) {
      *it = ++last_number;
    }
    size_t l = 0, c = n - 1;
    // rest lines
    while (step != 0) {
      get_direciton(d, d_arr);
      for (size_t i = 0; i < step; i++) {
        l += d_arr[0];
        c += d_arr[1];
        res[l][c] = ++last_number;
      }
      update_step(step, ++stepped);
      d = (d + 1) % 4;
    }
    return res;
  }
};

int main() {
  Solution s;
  s.generateMatrix(5);
  return 0;
}
