#include "head.hpp"

// TODO: 优化时间 5.02% 😭

// abca
class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    if (s.size() == 0) return 0;
    if (s.size() == 1) return 1;
    int res = 0, l = 0, r = 1;
    std::unordered_map<char, int> us;
    us.insert({s[l], l});
    while (r < (int)s.size()) {
      if (us.find(s[r]) != us.end()) {
        if (res < r - l) res = r - l;
        l = us.find(s[r])->second + 1;
        us.clear();
        for (int i = l; i < r; i++) us.insert({s[i], i});
      }
      us.insert({s[r], r});
      r++;
    }
    return res < r - l ? r - l : res;
  }
};

int main() {
  Solution s;
  std::cout << s.lengthOfLongestSubstring("pwwkew") << std::endl;
  return 0;
}
