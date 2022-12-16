#include "head.hpp"

class Solution {
public:
  int lengthOfLastWord(std::string s) {
    int len = 0;
    int i = (int)s.size() - 1;
    while(i >= 0) {
      if (s[i] != ' ') break;
      i--;
    }
    while(i >= 0) {
      if (s[i] == ' ') break;
      i--;
      len++;
    }
    return len;
  }
};

int main() {
  Solution s;
  std::cout << s.lengthOfLastWord("luffy is still joyboy") << std::endl;
  return 0;
}
