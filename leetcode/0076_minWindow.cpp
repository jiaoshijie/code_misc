#include "head.hpp"

using std::string;

class Solution {
public:
  bool is_ok(std::unordered_map<char, size_t>& s, std::unordered_map<char, size_t>& t) {
    for (auto i : t) {
      if (s.find(i.first) == s.end()) return false;
      if (s[i.first] < i.second) return false;
    }
    return true;
  }
  // TODO 5.23% It's so slow.
  string minWindow_slow(string s, string t) {
    bool found = false;
    std::unordered_map<char, size_t> t_c, s_c;
    for (auto i: t) {
      if (t_c.find(i) != t_c.end()) {
        t_c[i]++;
      } else {
        t_c[i] = 1;
      }
    }

    size_t begin = 0, end = 0, tb = 0, te = 0;
    while(tb < s.size() && t_c.find(s[tb]) == t_c.end()) tb++;
    while (tb < s.size() && te < s.size()) {
      if (t_c.find(s[te]) != t_c.end()) {
        if (s_c.find(s[te]) != s_c.end()) {
          s_c[s[te]]++;
        } else {
          s_c[s[te]] = 1;
        }
        while (is_ok(s_c, t_c)) {
          if (!end || end - begin > te - tb) {
            found = true;
            begin = tb;
            end = te;
          }
          s_c[s[tb]]--;
          tb++;
          while(tb < s.size() && t_c.find(s[tb]) == t_c.end()) tb++;
        }
      }
      te++;
    }
    string ret = found ? s.substr(begin, end - begin + 1) : "";
    return ret;
  }

  // -------------------------------------------------------------------------
  // slide window->NOTICE: also so slow 5.23%
  string minWindow(string s, string t) {
    bool found = false;
    std::unordered_map<char, size_t> t_c, s_c;
    for (auto i: t) {
      if (t_c.find(i) != t_c.end()) {
        t_c[i]++;
      } else {
        t_c[i] = 1;
        s_c[i] = 0;
      }
    }
    size_t begin = 0, end = 0, l = 0, r = 0;
    while(l < s.size() && t_c.find(s[l]) == t_c.end()) l++;
    r = l;
    while (r <= s.size() && l <= r) {
      if (r - l == t.size()) {
        if (is_ok(s_c, t_c)) {
          found = true;
          begin = l;
          end = r;
          break;
        } else {
          while(r < s.size() && t_c.find(s[r]) == t_c.end()) r++;
          s_c[s[r++]]++;
        }
      } else if (r - l < t.size()) {
        while(r < s.size() && t_c.find(s[r]) == t_c.end()) r++;
        s_c[s[r++]]++;
      } else { // r - l + 1 > t.size()
        if (is_ok(s_c, t_c)) {
          if (!end || end - begin > r - l) {
            found = true;
            begin = l;
            end = r;
          }
          s_c[s[l++]]--;
          while(l < s.size() && t_c.find(s[l]) == t_c.end()) l++;
        } else {
          while(r < s.size() && t_c.find(s[r]) == t_c.end()) r++;
          s_c[s[r++]]++;
        }
      }
    }

    string ret = found ? s.substr(begin, end - begin) : "";
    return ret;
  }
};

int main() {
  Solution s;
  std::vector<string> q = {"ADOBECODEBANC", "a", "a", "ab", "bba", "ab"};
  std::vector<string> a = {"ABC", "a", "aa", "b", "ab", "a"};
  std::vector<string> r = {"BANC", "a", "", "b", "ba", "a"};
  for (size_t i = 0; i < q.size(); i++) {
    std::cout << q[i] << ':' << a[i] << "-->" << r[i] << ':';
    std::cout << s.minWindow(q[i], a[i]) << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
  return 0;
}
