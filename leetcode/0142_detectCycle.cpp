#include "head.hpp"

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    if (!head) return NULL;
    ListNode *slow = head, *fast = head, *third = head;
    do {
      slow = slow->next;
      if (!fast || !fast->next) return NULL;
      fast = fast->next->next;
    }while(slow != fast);
    while (third != slow) {
      third = third->next;
      slow = slow->next;
    }
    return third;
  }
};

int main() {
  Solution s;
  return 0;
}
