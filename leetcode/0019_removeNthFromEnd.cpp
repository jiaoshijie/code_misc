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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *p = head, *q = head, *pq = q;
    while (n--) {
      p = p->next;
    }
    if (p != nullptr) {
      while (p != nullptr) {
        p = p->next;
        pq = q;
        q = q->next;
      }
      pq->next = q->next;
      delete q;
      return head;
    } else {
      pq = head->next;
      delete head;
      return pq;
    }
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
  // ListNode *head = new ListNode(
  //     1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  ListNode *head = new ListNode(1, new ListNode(2));
  ListNode *res = s.removeNthFromEnd(head, 1);
  s.PrintL(res);
  return 0;
}
