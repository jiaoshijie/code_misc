#include "head.hpp"

class Solution {
public:
  // 暴力求解: 超时
  std::vector<int> findSubsting(std::string s, std::vector<std::string>& words) {
    std::vector<int> res;
    if (words.empty()) return res;
    int alen = words.size() * words[0].size();
    for (int i = 0; i <= (int)s.size() - alen; i++) {
      if (justice(s.substr(i, alen), words)) {
        res.push_back(i);
      }
    }

    return res;
  }

  bool justice(std::string s, std::vector<std::string> &words) {
    bool *full = new bool[words.size()];
    memset(full, 0, sizeof(bool) * (int)words.size());
    for (int i = 0; i <= (int)s.size() - (int)words[0].size(); i += (int)words[0].size()) {
      for (int j = 0; j < (int)words.size(); j++) {
        if (!full[j] && s.substr(i, words[0].size()) == words[j]) {
          full[j] = true;
          break;
        }
        if (j == (int)words.size() - 1) return false;
      }
    }
    return true;
  }

  // TODO: 优化时间 42.96% 😭 write a article
  std::vector<int> findSubsting1(std::string s, std::vector<std::string> &words) {
    // 使用 Hash
    std::vector<int> res;
    if (words.empty()) return res;
    std::unordered_map<std::string, int> wCounts;
    for (auto i : words) {
      wCounts[i]++;
    }
    int wLen = words[0].size() * words.size();
    for (int i = 0; i <= (int)s.size() - wLen; i++) {
      std::unordered_map<std::string, int> seen;
      int j = 0;
      for (; j < wLen; j += words[0].size()){
        std::string temp = s.substr(i + j, words[0].size());
        if (wCounts.find(temp) != wCounts.end()) {
          seen[temp]++;
          if (seen[temp] > wCounts[temp]) break;
        } else {
          break;
        }
      }
      if (j == wLen) res.push_back(i);
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<std::string> words({"foo", "bar"});
  std::vector<int> res = s.findSubsting1("barfoothefoobarman", words);
  for (int i : res) {
    std::cout << i << std::endl;
  }
  return 0;
}
