#include "head.hpp"

// 回溯算法(trackback)

class Solution {
public:
  std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::string> res;
    std::string temp;
    trackback(res, temp, n, n);
    return res;
  }
  void trackback(std::vector<std::string>& res, std::string& str, int left, int right) {
    if (left > right) return;
    if (left < 0 || right < 0) return;
    if (left == 0 && right == 0) {
      res.push_back(str);
    }
    // 回溯
    str.push_back('(');
    trackback(res, str, left - 1, right);
    str.pop_back();

    str.push_back(')');
    trackback(res, str, left, right - 1);
    str.pop_back();
  }
};

int main() {
  Solution s;
  auto res = s.generateParenthesis(8);
  for (auto i : res) {
    std::cout << i << std::endl;
  }
  return 0;
}
