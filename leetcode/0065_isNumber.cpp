#include "head.hpp"

using std::string;

class Solution {
public:
  bool isNumber(string s) {
    int len = s.size();
    int i = 0;
    bool have_e = false, have_sign = false, have_dot = false, have_num = false;
    while (i < len) {
      if (s[i] >= '0' && s[i] <= '9') {
        have_sign = false;
        have_num = true;
      } else if (s[i] == '+' || s[i] == '-') {
        if (i > 0) {
          if (s[i - 1] != 'e' && s[i - 1] != 'E') return false;
        }
        if (have_sign) return false;
        have_sign = true;
        have_num = false;
      } else if (s[i] == '.') {
        if (have_e || have_dot) return false;
        have_dot = true;
      } else if (s[i] == 'e' || s[i] == 'E') {
        if (!have_num || have_e) return false;
        have_e = true;
        have_num = false;
      } else return false;
      i++;
    }
    bool res = true;
    if (have_e || have_dot || have_sign) res = have_num;
    return res;
  }
};

int main() {
  Solution s;
  std::vector<string> all_pass{
      "0",    "2",     "0089", "-0.1",  "+3.14",   "4.",          "-.9",
      "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
  std::vector<string> not_pass{"e",  ".",      "abc", "1a",  "1e",
                               "e3", "99e2.5", "--6", "-+3", "95a54e53"};
  for (auto i: not_pass) {
    std::cout << s.isNumber(i) << std::endl;
  }
  return 0;
}
