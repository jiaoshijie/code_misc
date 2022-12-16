#include "head.hpp"

// TODO: 优化时间 53.97% 😭

class Solution {
public:
  int romanToInt(std::string s) {
    int res = 0;
    std::map<char, int> m;
    m.insert({'I', 1});
    m.insert({'V', 5});
    m.insert({'X', 10});
    m.insert({'L', 50});
    m.insert({'C', 100});
    m.insert({'D', 500});
    m.insert({'M', 1000});
    for (int i = 0; i < (int)s.size(); i++) {
      if ((s[i] == 'C' || s[i] == 'X' || s[i] == 'I') && (i + 1) < (int)s.size() && m[s[i]] < m[s[i + 1]]) {
        res += (m[s[i + 1]] - m[s[i]]);
        i++;
        continue;
      }
      res += m[s[i]];
    }
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.romanToInt("MCMXCIV") << std::endl;
  return 0;
}
