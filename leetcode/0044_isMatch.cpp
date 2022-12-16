#include "head.hpp"

// https://leetcode.ca/2016-01-13-44-Wildcard-Matching/
// TODO: write a article

class Solution {
public:
  bool isMatch_timeout(std::string s, std::string p) {
    // NOTICE: over time:
    // s: "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb"
    // p: "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb"
    if (s.size() == 0 && p.size() == 0)
      return true;
    // if (s.size() == 0 || p.size() == 0) return false;
    if (p.size() == 1 && p[0] == '*')
      return true;
    if (s.size() == 1 && p.size() == 1 && p[0] == '?')
      return true;
    size_t i = 0, j = 0;
    while (i < s.size() && j < p.size()) {
      if (p[j] == '*') {
        while (j < p.size() && p[j] == '*')
          j++;
        while (i < s.size()) {
          if (p[j] == '?') {
            if (isMatch(s.substr(i + 1, s.size() - i - 1),
                        p.substr(j + 1, p.size() - j - 1)))
              return true;
          } else if (s[i] == p[j]) {
            if (isMatch(s.substr(i, s.size() - i), p.substr(j, p.size() - j)))
              return true;
          }
          i++;
        }
      } else if (p[j] == '?' || p[j] == s[i]) {
        i++;
        j++;
      } else {
        return false;
      }
    }

    while (j < p.size() && p[j] == '*')
      j++;
    if (i == s.size() && j == p.size())
      return true;
    return false;
  }
  bool isMatch(std::string s, std::string p) {
    size_t i = 0, j = 0;
    int iStar = -1, jStar = -1;

    while (i < s.size()) {
      if (s[i] == p[j] || p[j] == '?') {
        i++;
        j++;
      } else if (p[j] == '*') {
        jStar = j;
        iStar = i;
        j++;
      } else if (jStar != -1) {
        iStar++;
        j = jStar + 1;
        i = iStar;
      } else return false;
    }

    while (j < p.size() && p[j] == '*') j++;
    if (j == p.size()) return true;
    return false;
  }
};

int main() {
  Solution s;
  std::cout << s.isMatch("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabab"
                         "abaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaab"
                         "baababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaab"
                         "bababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
                         "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*"
                         "b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb")
            << std::endl;
  std::cout << s.isMatch("aa", "a") << std::endl;
  std::cout << s.isMatch("aa", "*") << std::endl;
  std::cout << s.isMatch("cb", "?a") << std::endl;
  std::cout << s.isMatch("abcdefghigk", "**ab*fg*k**") << std::endl;
  std::cout << s.isMatch("abcdefghigk", "**?b*fg*k**") << std::endl;
  return 0;
}
