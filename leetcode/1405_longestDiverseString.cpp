#include "head.hpp"

using std::string;
using std::pair;
using std::vector;

class Solution {
public:
  string longestDiverseString(int a, int b, int c) {
    string res;
    vector<pair<int, char>> arr = {{a, 'a'}, {b, 'b'}, {c, 'c'}};

    while (true) {
      std::sort(arr.begin(), arr.end(), [](const pair<int, char> & p1, const pair<int, char> & p2) {
          return p1.first > p2.first;
          });
      bool hasNext = false;
      for (auto & [freq, ch] : arr) {
        int m = res.size();
        if (freq <= 0) {
          break;
        }
        if (m >= 2 && res[m - 2] == ch && res[m - 1] == ch) {
          continue;
        }
        hasNext = true;
        res.push_back(ch);
        freq--;
        break;
      }
      if (!hasNext) {
        break;
      }
    }

    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.longestDiverseString(1, 1, 7) << std::endl;
  std::cout << s.longestDiverseString(7, 1, 0) << std::endl;
  std::cout << s.longestDiverseString(4, 4, 3) << std::endl;
  std::cout << s.longestDiverseString(1, 3, 5) << std::endl;
  std::cout << s.longestDiverseString(2, 2, 1) << std::endl;
  std::cout << s.longestDiverseString(1, 4, 5) << std::endl;
  std::cout << s.longestDiverseString(3, 0, 4) << std::endl;
  std::cout << s.longestDiverseString(0, 8, 11) << std::endl;
  return 0;
}
