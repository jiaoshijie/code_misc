#include "head.hpp"

// TODO: 优化时间 14.98% 😭
// TODO: write a article

using std::string;
using std::vector;

class Solution {
public:
  bool isMatch_(std::string s, std::string p) {
    int i = 0, j = 0;
    while (i < (int)s.size() && j < (int)p.size()) {
      if (s[i] == p[j] || p[j] == '.') {
        if (j < (int)p.size() - 1 && p[j + 1] == '*') { // 匹配0次或多次
          while (i < (int)s.size() && j < (int)p.size() &&
                 (s[i] == p[j] || p[j] == '.') && j + 2 < (int)p.size()) {
            if (isMatch(s.substr(i), p.substr(j + 2))) {
              return true;
            }
            i++;
          }
          if (j + 2 == (int)p.size()) {
            while ((s[i] == p[j] || p[j] == '.') && i < (int)s.size())
              i++;
          }
          j = j + 2;
        } else { // 没有*只能匹配一次
          i++, j++;
        }
      } else {
        if (j < (int)p.size() - 1 && p[j + 1] == '*') { // 有*但只能匹配0次
          j = j + 2;
        } else { // 不匹配退出
          return false;
        }
      }
    }
    while (j < (int)p.size()) { // s = "a", p = "ab*" 情况
      if (p[j + 1] == '*')
        j = j + 2;
      else
        break;
    }
    return i < (int)s.size() || j < (int)p.size() ? false : true;
  }

  // input: s 'aa' p 'a*'
  // dp array:
  //      a a
  //    a
  //    *
  bool isMatch(string s, string p) {
    // dp[i][j] 意思是 前i 前j 是否匹配
    vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1, false));
    dp[0][0] = true;
    for (size_t i = 0; i < s.size() + 1; i++) {  // 从0开始 这一行有非零的可能性
      for (size_t j = 1; j < p.size() + 1; j++) {
        if (p[j - 1] == '*') {
          dp[i][j] |= dp[i][j - 2]; // * 匹配0次的情况
          if (i != 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
            dp[i][j] |= dp[i - 1][j];  // * 其它次数的匹配
          }
        } else {
          if (i != 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
            dp[i][j] |= dp[i - 1][j - 1];
          }
        }
      }
    }
    return dp[s.size()][p.size()];
  }
};

int main() {
  std::cout << std::boolalpha;
  Solution s;
  assert(s.isMatch("aab", "c*a*b"));
  assert(s.isMatch("aaa", "ab*ac*a"));
  assert(s.isMatch("aaa", "ab*a*c*a"));
  assert(s.isMatch("aaa", ".*"));
  return 0;
}
