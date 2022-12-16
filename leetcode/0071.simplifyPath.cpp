#include "head.hpp"

using std::string;

class Solution {
public:
  string simplifyPath(string path) {
    string res;
    int i = 0, len = path.size();
    while (i < len) {
      if (path[i] == '/') {
        if (res.empty() || res.back() != '/')
          res.push_back('/');
        while(path[i] == '/') i++;
      } else if (path[i] == '.') {
        int j = i, count_dots = 0;
        while (j < len && path[j] == '.') {
          j++;
          count_dots++;
        }
        if (count_dots < 3 && path[i - 1] == '/' && (j == len || path[j] == '/')) {
          i = j;
          if (count_dots == 2) {
            res.pop_back();
            while (!res.empty() && res.back() != '/') res.pop_back();
          }
        } else {
          while (i < j) {
            res.push_back(path[i]);
            i++;
          }
        }
      } else {
        res.push_back(path[i]);
        i++;
      }
    }
    if (res.empty()) res = "/";
    if (res.back() == '/' && res.size() != 1) res.pop_back();
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.simplifyPath("/.") << std::endl;
  return 0;
}
