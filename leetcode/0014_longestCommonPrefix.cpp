#include "head.hpp"

class Solution {
public:
  std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    std::string res;
    char temp;
    int minStr = INT32_MAX;
    for (int i = 0; i < (int)strs.size(); i++) {
      if (minStr > (int)strs[i].size()) minStr = (int)strs[i].size();
      if (strs[i].empty()) return res;
    }
    for (int i = 0; i < minStr; i++) {
      temp = strs[0][i];
      for (int j = 1; j < (int)strs.size(); j++) {
        if (temp != strs[j][i]) return res;
      }
      res += temp;
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<std::string> strs({"a"});
  std::cout << s.longestCommonPrefix(strs) << std::endl;
  return 0;
}
