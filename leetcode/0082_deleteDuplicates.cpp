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
  ListNode *deleteDuplicates(ListNode *head) {
    if (!head)
      return nullptr;
    ListNode ret;
    ListNode *p = head, *q = &ret;
    int last_num = 0;
    while (p) {
      last_num = p->val;
      if (!p->next || p->next->val != last_num) {
        q->next = new ListNode(last_num);
        q = q->next;
        p = p->next;
      } else {
        while (p && p->val == last_num)
          p = p->next;
      }
    }
    return ret.next;
  }
};

int main() {
  Solution s;
  ListNode head(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     3, new ListNode(4, new ListNode(4, new ListNode(5)))))));
  ListNode *ret = s.deleteDuplicates(&head);
  while(ret) {
    std::cout << ret->val << ' ';
    ret = ret->next;
  }
  std::cout << std::endl;
  return 0;
}
