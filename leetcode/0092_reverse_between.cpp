#include "./head.hpp"


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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
      ListNode* q1 = nullptr;
      int i = 1;
      while (i < left) {
        if (q1) {
          // not null
          q1 = q1->next;
        } else {
          // null
          q1 = head;
        }
        i++;
      }

      ListNode* p1 = nullptr;

      if (q1) {
        p1 = q1->next;
      } else {
        // null
        p1 = head;
      }

      ListNode* p2 = p1->next;
      while (i < right) {
        ListNode* t = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = t;
        i++;
      }

      if (q1) {
        ListNode* t = q1->next;
        q1->next = p1;
        t->next = p2;
        return head;
      } else {
        // null
        head->next = p2;
        return p1;
      }
    }
};

int main() {
  Solution s;
  ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  // ListNode* head = new ListNode(5);
  ListNode* p = s.reverseBetween(head, 5, 5);
  while (p) {
    std::cout << p->val << std::endl;
    p = p->next;
  }
  return 0;
}
