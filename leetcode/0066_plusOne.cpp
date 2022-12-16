#include "head.hpp"

using std::vector;

class Solution {
public:
  vector<int> plusOne(vector<int>& digits) {
    vector<int> res;
    int carry = 0;
    int index = digits.size() - 1;
    int temp = digits[index];
    digits[index] = (temp + 1) % 10;
    carry = (temp + 1) / 10;

    index--;

    for (; index >= 0; index--) {
      temp = digits[index];
      digits[index] = (temp + carry) % 10;
      carry = (temp + carry) / 10;
    }
    if (carry) res.push_back(carry);
    for (auto i: digits) {
      res.push_back(i);
    }
    return res;
  }
};

int main() {
  Solution s;
  vector<int> arr{4, 3, 2, 1};
  auto res = s.plusOne(arr);
  for (auto i: res) {
    std::cout << i << std::endl;
  }
  return 0;
}
