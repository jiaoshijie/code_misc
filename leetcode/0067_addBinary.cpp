#include "head.hpp"

using std::string;

class Solution {
public:
  string addBinary(string a, string b) {
    string res, t_res;
    int a_i = a.size() - 1, b_i = b.size() - 1;
    int carry = 0;
    while(a_i >= 0 && b_i >= 0) {
      int r = ((a[a_i] - '0') + (b[b_i] - '0') + carry) % 2;
      carry = ((a[a_i] - '0') + (b[b_i] - '0') + carry) / 2;
      t_res.push_back(r + '0');
      a_i--;
      b_i--;
    }
    for (; a_i >= 0; a_i--) {
      int r = ((a[a_i] - '0') + carry) % 2;
      carry = ((a[a_i] - '0') + carry) / 2;
      t_res.push_back(r + '0');
    }
    for (; b_i >= 0; b_i--) {
      int r = ((b[b_i] - '0') + carry) % 2;
      carry = ((b[b_i] - '0') + carry) / 2;
      t_res.push_back(r + '0');
    }
    if (carry) t_res.push_back(carry + '0');
    for (auto it = t_res.rbegin(); it != t_res.rend(); it++) {
      res.push_back(*it);
    }
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.addBinary("1010", "1011") << std::endl;
  return 0;
}
