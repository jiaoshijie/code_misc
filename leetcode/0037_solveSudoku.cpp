#include "head.hpp"

class Solution {
private:
  void dfs(std::vector<std::vector<char>> &board,
           std::vector<std::pair<int, int>> &em, int index, bool &done) {
    // ending condition
    if (index == int(em.size())) {
      done = true;
      return;
    }
    bool nums[9];
    memset(nums, true, sizeof(bool) * 9);
    for (int i = 0; i < 9; i++) {
      if (board[em[index].first][i] != '.')
        nums[board[em[index].first][i] - '0' - 1] = false;
      if (board[i][em[index].second] != '.')
        nums[board[i][em[index].second] - '0' - 1] = false;
      if (board[em[index].first / 3 * 3 + i / 3][em[index].second / 3 * 3 + i % 3] !=
          '.')
        nums[board[em[index].first / 3 * 3 + i / 3][em[index].second / 3 * 3 + i % 3] -
             '0' - 1] = false;
    }
    for (int i = 0; i < 9; i++) {
      if (nums[i]) {
        board[em[index].first][em[index].second] = i + '0' + 1;
        dfs(board, em, index + 1, done);
        if (done) return;
        board[em[index].first][em[index].second] = '.';
      }
    }
  }

public:
  void print(std::vector<std::vector<char>> &board) {
    std::cout << '[';
    for (int i = 0; i < 9; i++) {
      std::cout << '[';
      for (int j = 0; j < 9; j++) {
        std::cout << '"' << board[i][j] << '"';
        if (j != 8)
          std::cout << ',';
      }
      std::cout << ']';
      if (i != 8)
        std::cout << ",\n";
    }
    std::cout << "]\n";
  }
  void solveSudoku(std::vector<std::vector<char>> &board) {
    bool done = false;
    std::vector<std::pair<int, int>> em;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          em.push_back(std::make_pair(i, j));
        }
      }
    }
    dfs(board, em, 0, done);
  }
};

int main() {
  Solution s;
  std::vector<std::vector<char>> board = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  s.solveSudoku(board);
  s.print(board);

  return 0;
}
