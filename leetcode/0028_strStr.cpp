#include "head.hpp"

// TODO: 优化时间 5.07% 😭 write a article

class Solution {
public:
  int strStr(std::string haystack, std::string needle) {
    if (needle == "") return 0;
    int i = 0;
    while (i < (int)haystack.size()) {
      if (haystack[i] == needle[0]) {
        for (int j = 1; j < (int)needle.size(); j++) {
          if (needle[j] != haystack[i + j]) goto label;
        }
        return i;
      }
label:
      i++;
    }
    return -1;
  }
};

int main() {
  Solution s;
  std::cout << s.strStr("aaaaaa", "") << std::endl;
  return 0;
}
