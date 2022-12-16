#include "head.hpp"

class Solution {
  public:
    std::string multiply(std::string num1, std::string num2) {
      if (num1.size() == 1 && num1[0] == '0') return "0";
      if (num2.size() == 1 && num2[0] == '0') return "0";
      std::string out, temp;
      for (size_t i = 0; i < num2.size(); i++) {
        std::string t;
        for (int j = 0; j < int(num2.size() - i - 1); j++) {
          t += '0';
        }
        int it = 0;
        for (int j = num1.size() - 1; j >= 0; j--) {
          int res = (num1[j] - '0') * (num2[i] - '0') + it;
          t += res % 10 + '0';
          it = res / 10;
        }
        if (it) t += it + '0';
        it = 0;
        if (out.empty()) out = t;
        else {
          int j = 0;
          for (; j < int(t.size()); j++) {
            int res = (out[j] - '0') + (t[j] - '0') + it;
            out[j] = res % 10 + '0';
            it = res / 10;
          }
          while (it) {
            if (j >= int(out.size())) {
              out += it + '0';
              it = 0;
            } else {
              int res = (out[j] - '0') + it;
              out[j] = res % 10 + '0';
              it = res / 10;
              j++;
            }
          }
        }
      }
      reverse(out.begin(), out.end());
      return out;
    }
};

int main() {
  Solution s;
  std::cout << s.multiply("140", "721") << std::endl;
  return 0;
}
