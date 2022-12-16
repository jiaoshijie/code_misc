#include "head.hpp"

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head) return nullptr;
    ListNode ret = ListNode();
    ListNode *p = head, *q = &ret;
    int last_num = 0;
    while(p) {
      last_num = p->val;
      while (p->next && p->next->val == last_num) p = p->next;
      q->next = new ListNode(last_num);
      q = q->next;
      p = p->next;
    }
    return ret.next;
  }
};

int main() {
  Solution s;
  return 0;
}
