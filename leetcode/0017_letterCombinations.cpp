#include "head.hpp"

class Solution {
public:
  std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> res;
    if (digits.empty())
      return res;
    std::string index[10] = {"",    "",    "abc",  "def", "ghi",
                             "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::queue<std::string> m_queue;
    for (int i = 0; i < (int)index[digits[0] - '0'].size(); i++) {
      std::string temp;
      temp = temp + index[digits[0] - '0'][i];
      m_queue.push(temp);
    }
    for (int i = 1; i < (int)digits.size(); i++) {
      int len = m_queue.size();
      while (len--) {
        std::string top = m_queue.front();
        for (int j = 0; j < (int)index[digits[i] - '0'].size(); j++) {
          std::string temp = top + index[digits[i] - '0'][j];
          m_queue.push(temp);
        }
        m_queue.pop();
      }
    }
    while (!m_queue.empty()) {
      res.push_back(m_queue.front());
      m_queue.pop();
    }
    return res;
  }
};

int main() {
  Solution s;
  auto res = s.letterCombinations("7892");
  for (auto i : res) {
    std::cout << i << std::endl;
  }
  return 0;
}
