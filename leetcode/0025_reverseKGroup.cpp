#include "head.hpp"

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// TODO: 92.57% "代码写的有点乱有时间整理整理" write a article

class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1)
      return head;
    ListNode* p = head, *q = head, *lend, *nbegin = head, *temp = nullptr;
    for (int i = 1; i < k; i++) {
      if (q == nullptr || q->next == nullptr) return head;
      q = q->next;
    }
    nbegin = q->next;
    temp = reverseList(p, q);
    ListNode *res = temp;
    lend = p;
    p = nbegin;
    q = nbegin;

    while (p && q) {
      for (int i = 1; i < k; i++) {
        if (q == nullptr || q->next == nullptr) {
          lend->next = nbegin;
          return res;
        }
        q = q->next;
      }
      nbegin = q->next;
      temp = reverseList(p, q);
      lend->next = temp;
      lend = p;
      p = nbegin;
      q = nbegin;
    }
    return res;
  }

  ListNode *reverseList(ListNode *begin, ListNode *end) {
    ListNode *head = begin, *cur = begin->next, *temp = cur->next;
    while (head != end) {
      temp = cur->next;
      cur->next = head;
      head = cur;
      cur = temp;
    }
    begin->next = nullptr;
    return end;
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
  //     1,
  //     new ListNode(
  //         2, new ListNode(
  //                3, new ListNode(
  //                       4, new ListNode(
  //                              5, new ListNode(
  //                                     6, new ListNode(
  //                                            7, new ListNode(
  //                                                   8, new ListNode(9)))))))));
  ListNode *head = new ListNode(1);
  ListNode* res = s.reverseKGroup(head, 1);
  // ListNode *res = s.reverseList(head, head->next->next->next);
  s.PrintL(res);
  return 0;
}
