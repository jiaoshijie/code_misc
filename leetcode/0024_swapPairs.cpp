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
  ListNode* swapPairs(ListNode* head) {
    if (head == nullptr) return head;
    ListNode *p = head, *q = head->next, *temp;
    if (!q) return head;
    p->next = q->next;
    head = q;
    head->next = p;
    p = head->next;
    q = p->next;
    while (p->next && q->next) {
      temp = q->next->next;
      p->next = q->next;
      p->next->next = q;
      q->next = temp;
      p = p->next->next;
      q = p->next;
    }
    return head;
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
  ListNode *head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     4, new ListNode(5, new ListNode(6, new ListNode(7)))))));
  ListNode *res = s.swapPairs(head);
  s.PrintL(res);
  return 0;
}
