#include "head.hpp"

/**
 * 解法: 枚举所有情况
 * TODO: write a article
 * */

class Solution {
public:
  // 寻找以i为中心的最大回文串
  std::string m_find(const std::string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
      l--, r++;
    }
    // mbabac
    return s.substr(l + 1, r - l - 1);
  }

  std::string logestPalindrome(std::string s) {
    std::string res, temp;
    for (int i = 0; i < s.size(); i++) {
      temp = m_find(s, i, i);
      if (temp.size() > res.size()) res = temp;
      temp = m_find(s, i, i + 1);
      if (temp.size() > res.size()) res = temp;
    }
    return res;
  }
};

int main() {
  Solution func;
  std::string s("cbba");
  std::cout << func.logestPalindrome(s) << std::endl;
  return 0;
}
