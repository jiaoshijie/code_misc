#include "head.hpp"

class Solution {
public:
  struct Node {
    char ch;
    Node *next;
    Node() : ch('\0'), next(nullptr) {}
    Node(char ch) : ch(ch), next(nullptr) {}
    void Insert(Node *n) {
      Node *p = this;
      while(p->next) p = p->next;
      p->next = n;
    }
  };

  std::string convert(std::string s, int numRows) {
    if (numRows == 1)
      return s;
    std::string res;
    Node *n = new Node[numRows];
    bool flag = true;
    int j = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      if (flag) {
        n[j++].Insert(new Node(s[i]));
        if (j >= numRows - 1) {
          flag = false;
        }
      } else {
        n[j--].Insert(new Node(s[i]));
        if (j <= 0) {
          flag = true;
        }
      }
    }
    for (int i = 0; i < numRows; i++) {
      Node *p = n[i].next;
      while (p) {
        res += p->ch;
        p = p->next;
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  std::cout << s.convert("PAYPALISHIRING", 4) << std::endl;
  return 0;
}
