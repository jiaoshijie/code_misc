#include "head.hpp"

class Solution {
public:
  int myAtoi(std::string s) {
    int res = 0, sign = 1, i = 0;
    while(s[i] == ' ' && i < (int)s.size()) i++;
    if (i < (int)s.size() && s[i] == '-') {
      sign = -1;
      i++;
    } else if (i < (int)s.size() && s[i] == '+') {
      i++;
    } else if (i < (int)s.size() && (s[i] < '0' || s[i] > '9')) {
      return 0;
    }
    for (; i < (int)s.size() && (s[i] >= '0' && s[i] <= '9'); i++) {
      if (res < INT32_MAX / 10)
        res = res * 10 + (s[i] - '0');
      else if (res == INT32_MAX / 10) {
        if (sign == -1 && s[i] >= '8') return INT32_MIN;
        else if (sign == 1 && s[i] >= '7') return INT32_MAX;
        else {
          res = res * 10 + (s[i] - '0');
          if ((i + 1) < (int)s.size() && (s[i + 1] >= '0' && s[i + 1] <= '9')) {
            return sign == 1 ? INT32_MAX : INT32_MIN;
          }
        }
      } else {
        return sign == 1 ? INT32_MAX : INT32_MIN;
      }
    }
    return sign * res;
  }
};

int main() {
  std::string str("-91283472332");
  Solution s;
  std::cout << s.myAtoi(str) << std::endl;
  return 0;
}
