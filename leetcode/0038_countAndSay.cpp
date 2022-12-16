#include "head.hpp"

class Solution {
public:
  std::string countAndSay(int n) {
    if (n == 1) return "1";
    std::string out = "", temp;
    temp = countAndSay(n - 1);
    char ch = temp[0];
    int count = 1;
    for (size_t i = 1; i < temp.size(); i++) {
      if (ch == temp[i]) count++;
      else {
        out += count + '0';
        out += ch;
        ch = temp[i];
        count = 1;
      }
    }
    out += count + '0';
    out += ch;

    return out;
  }
};

int main() {
  Solution s;
  std::cout << s.countAndSay(30) << std::endl;
  return 0;
}
