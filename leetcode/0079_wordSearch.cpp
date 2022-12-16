#include "head.hpp"

using std::vector;
using std::string;

class Solution {
public:
  bool find_char(vector<vector<char>>& board, string& word, int index, vector<vector<bool>>& used, int row, int col) {
    if (int(word.size()) == index) {
      return true;
    }
    bool found = false;
    if (!found && row > 0 && !used[row - 1][col] && board[row - 1][col] == word[index]) {
      used[row - 1][col] = true;
      found = find_char(board, word, index + 1, used, row - 1, col);
      used[row - 1][col] = false;
    }
    if (!found && row < int(board.size() - 1) && !used[row + 1][col] && board[row + 1][col] == word[index]) {
      used[row + 1][col] = true;
      found = find_char(board, word, index + 1, used, row + 1, col);
      used[row + 1][col] = false;
    }
    if (!found && col > 0 && !used[row][col - 1] && board[row][col - 1] == word[index]) {
      used[row][col - 1] = true;
      found = find_char(board, word, index + 1, used, row, col - 1);
      used[row][col - 1] = false;
    }
    if (!found && col < int(board[0].size() - 1) && !used[row][col + 1] && board[row][col + 1] == word[index]) {
      used[row][col + 1] = true;
      found = find_char(board, word, index + 1, used, row, col + 1);
      used[row][col + 1] = false;
    }
    return found;
  }

  bool exist(vector<vector<char>>& board, string word) {
    vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));
    bool found = false;
    for (int i = 0; !found && i < int(board.size()); i++) {
      for (int j = 0; !found && j < int(board[0].size()); j++) {
        if (board[i][j] == word[0]) {
          used[i][j] = true;
          found = find_char(board, word, 1, used, i, j);
          used[i][j] = false;
        }
      }
    }
    return found;
  }
};

int main() {
  Solution s;
  vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
  std::cout << s.exist(board, "ABCB") << std::endl;
  return 0;
}
