#include "head.hpp"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  bool hasCycle(ListNode *head) {
    ListNode *p = head, *pp = head;
    while (pp && pp->next) {
      p = p->next;
      pp = pp->next->next;
      if (p == pp) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  Solution s;
  return 0;
}
