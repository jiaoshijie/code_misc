#include "head.hpp"

class Solution {
public:
  bool justice(char ch1, char ch2) {
    if (ch1 == '(' && ch2 == ')') return true;
    if (ch1 == '[' && ch2 == ']') return true;
    if (ch1 == '{' && ch2 == '}') return true;
    return false;
  }
  bool isValid(std::string s) {
    std::stack<char> Stack;
    for (auto ch : s) {
      if (ch == '(' || ch == '{' || ch == '[') {
        Stack.push(ch);
      } else {
        if (Stack.empty() || !justice(Stack.top(), ch)) return false;
        Stack.pop();
      }
    }
    if (!Stack.empty()) return false;
    return true;
  }
};

int main() {
  std::cout << std::boolalpha;
  Solution s;
  std::cout << s.isValid("{[]") << std::endl;
  return 0;
}
