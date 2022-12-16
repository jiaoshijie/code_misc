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
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode res, *temp = &res, *p = l1, *q = l2;
    while (p && q) {
      if (p->val < q->val) {
        temp->next = new ListNode(p->val);
        p = p->next;
      } else {
        temp->next = new ListNode(q->val);
        q = q->next;
      }
      temp = temp->next;
    }
    while (p) {
      temp->next = new ListNode(p->val);
      p = p->next;
      temp = temp->next;
    }
    while (q) {
      temp->next = new ListNode(q->val);
      q = q->next;
      temp = temp->next;
    }
    return res.next;
  }

  void PrintL(ListNode *head) {
    ListNode *p = head;
    while (p != nullptr) {
      std::cout << p->val << ' ';
      p = p->next;
    }
    std::cout << std::endl;
  }
};

int main() {
  Solution s;
  // ListNode *l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
  // ListNode *l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
  ListNode *l1 = nullptr;
  ListNode *l2 = new ListNode(0);
  ListNode* res = s.mergeTwoLists(l1, l2);
  s.PrintL(res);
  return 0;
}
