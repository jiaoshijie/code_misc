#include "head.hpp"

// https://zhuanlan.zhihu.com/p/41951874
// TODO: write a article

class Solution {
public:
  int longestValidParentheses(std::string s) {
    int res = 0, index = 0, start = 0;
    std::stack<int> st;
    while (index < (int)s.size()) {
      if (s[index] == '(') {
        st.push(index);
      } else {
        if (st.empty()) {
          start = index + 1;
        } else {
          st.pop();
          if (st.empty()) res = std::max(res, index - start + 1);
          else res = std::max(res, index - st.top());
        }
      }
      index++;
    }
    return res;
  }
};

int main() {
  Solution s;
  // "" "(()" ")()())" "(()(()()" "(())))(())()"
  std::cout << s.longestValidParentheses("(())))(())()") << std::endl;
  return 0;
}
