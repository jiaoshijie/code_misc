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
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head) return head;
    size_t len = 0;
    ListNode* p = head, *q;
    while(p) {
      len++;
      p = p->next;
    }
    if (len == 1) return head;
    k = k % len;
    while(k) {
      k--;
      p = head;
      while(p->next) {
        q = p;
        p = p->next;
      }
      p->next = head;
      q->next = nullptr;
      head = p;
    }
    return head;
  }

  // NOTICE: this takes more time.
  ListNode* rotateRight2(ListNode* head, int k) {
    if (!head) return head;
    size_t len = 0;
    ListNode* p = head;
    while(p) {
      len++;
      p = p->next;
    }
    if (len == 1) return head;
    k = k % len;
    while(k) {
      k--;
      p = head;
      while(p->next->next) {
        p = p->next;
      }
      p->next->next = head;
      head = p->next;
      p->next = nullptr;
    }
    return head;
  }
};

int main() {
  Solution s;
  // ListNode t2(2);
  ListNode t1(1);
  ListNode head(0, &t1);
  ListNode *q = &head;
  // while(q) {
  //   std::cout << q->val << std::endl;
  //   q = q->next;
  // }
  ListNode *res = s.rotateRight(nullptr, 3);
  ListNode* p = res;
  while(p) {
    std::cout << p->val << std::endl;
    p = p->next;
  }
  return 0;
}
