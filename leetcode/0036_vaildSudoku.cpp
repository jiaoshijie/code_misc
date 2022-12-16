#include "head.hpp"

// NOTE: 52.54%

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>> &board) {
    bool h[9], v[9], hv[9];
    for (int i = 0; i < 9; i++) {
      memset(h, false, sizeof(bool) * 9);
      memset(v, false, sizeof(bool) * 9);
      for (int j = 0; j < 9; j++) {
        if (board[i][j] != '.') {
          if (h[board[i][j] - '0' - 1] == true)
            return false;
          h[board[i][j] - '0' - 1] = true;
        }
        if (board[j][i] != '.') {
          if (v[board[j][i] - '0' - 1] == true)
            return false;
          v[board[j][i] - '0' - 1] = true;
        }
      }
    }
    for (int i = 0; i < 9; i += 3) {
      for (int j = 0; j < 9; j += 3) {
        memset(hv, false, sizeof(bool) * 9);
        for (int k = 0; k < 9; k++) {
          if (board[i + k / 3][j + k % 3] != '.') {
            if (hv[board[i + k / 3][j + k % 3] - '0' - 1] == true)
              return false;
            hv[board[i + k / 3][j + k % 3] - '0' - 1] = true;
          }
        }
      }
    }
    return true;
  }
};

int main() {
  Solution s;
  // std::vector<std::vector<char>> board = {
  //     {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
  //     {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
  //     {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
  //     {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
  //     {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
  //     {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
  //     {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
  //     {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
  //     {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  std::vector<std::vector<char>> board = {
      {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  std::cout << s.isValidSudoku(board) << std::endl;
  return 0;
}
