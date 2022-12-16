#include "head.hpp"

// TODO: 5.12%---write a article

class Solution {
public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> com;
    for (size_t i = 0; i < strs.size(); i++) {
      std::string temp = strs[i];
      std::sort(temp.begin(), temp.end());
      bool f = true;
      for (size_t j = 0; j < com.size(); j++) {
        if (com[j] == temp) {
          res[j].push_back(strs[i]);
          f = false;
          break;
        }
      }
      if (f) {
        res.push_back(std::vector<std::string>({strs[i]}));
        com.push_back(temp);
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  // std::vector<std::string> strs = {"eat","tea","tan","ate","nat","bat"};
  std::vector<std::string> strs = {"a"};
  s.groupAnagrams(strs);
  return 0;
}
