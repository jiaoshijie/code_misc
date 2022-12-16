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
  ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode res, *temp = &res;
    int carry = 0, sum = 0;
    while (l1 || l2) {
      sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
      carry = sum / 10;
      sum %= 10;
      l1 = l1 ? l1->next : nullptr;
      l2 = l2 ? l2->next : nullptr;
      temp->next = new ListNode(sum);
      temp = temp->next;
    }
    if (carry) temp->next = new ListNode(carry);
    return res.next;
  }
};

int main() {
  Solution s;
  ListNode *l1 = new ListNode(2);
  ListNode *l2 = new ListNode(5);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(3);
  l2->next = new ListNode(6);
  l2->next->next = new ListNode(4);
  ListNode *res = s.addTwoNumbers(l1, l2);
  while (res) {
    std::cout << res->val << ' ';
    res = res->next;
  }
  std::cout << std::endl;
  return 0;
}
