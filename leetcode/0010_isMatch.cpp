#include "head.hpp"

// TODO: 优化时间 14.98% 😭
// TODO: write a article

class Solution {
public:
  bool isMatch(std::string s, std::string p) {
    int i = 0, j = 0;
    while (i < (int)s.size() && j < (int)p.size()) {
      if (s[i] == p[j] || p[j] == '.') {
        if (j < (int)p.size() - 1 && p[j + 1] == '*') {  // 匹配0次或多次
          while (i < (int)s.size() && j < (int)p.size() && (s[i] == p[j] || p[j] == '.') && j + 2 < (int)p.size()) {
            if (isMatch(s.substr(i), p.substr(j + 2))) {
              return true;
            }
            i++;
          }
          if (j + 2 == (int)p.size()) {
            while((s[i] == p[j] || p[j] == '.') && i < (int)s.size()) i++;
          }
          j = j + 2;
        } else {  // 没有*只能匹配一次
          i++, j++;
        }
      } else {
        if (j < (int)p.size() - 1 && p[j + 1] == '*') {  // 有*但只能匹配0次
          j = j + 2;
        } else {  // 不匹配退出
          return false;
        }
      }
    }
    while (j < (int)p.size()) {  // s = "a", p = "ab*" 情况
      if (p[j + 1] == '*') j = j + 2;
      else break;
    }
    return i < (int)s.size() || j < (int)p.size() ? false : true;
  }
};

int main() {
  std::cout << std::boolalpha;
  Solution s;
  std::cout << s.isMatch("ab", ".*c") << std::endl;
  return 0;
}
