#include "head.hpp"

// TODO: 优化时间 29.41% 😭

class Solution {
public:
  int Pow10(int i) {
    int res = 1;
    while (i--) {
      res *= 10;
    }
    return res;
  }

  std::string intToRoman(int num) {
    std::string res;
    std::map<int, char> m;
    m.insert({1, 'I'});
    m.insert({5, 'V'});
    m.insert({10, 'X'});
    m.insert({50, 'L'});
    m.insert({100, 'C'});
    m.insert({500, 'D'});
    m.insert({1000, 'M'});
    int temp = num, digitCapacity = 0;
    while (temp) {
      digitCapacity++;
      temp /= 10;
    }
    temp = num;
    for (int i = 0; i < digitCapacity; i++) {
      int n = Pow10(digitCapacity - i - 1);
      int t = temp / n;
      temp %= n;
      if (t > 0 && t <= 3) {
        while(t--) res += m[n];
      } else if (t == 4 || t == 5) {
        if (t == 4) res += m[n];
        res += m[n * 5];
      } else if (t > 5 && t < 9) {
        res += m[n * 5];
        while(t-- > 5) res += m[n];
      } else if (t == 9) {
        res += m[n];
        res += m[n * 5 * 2];
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.intToRoman(3999) << std::endl;
  return 0;
}
