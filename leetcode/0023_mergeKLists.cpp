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
  /*
   * 超时
   * **/
  ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
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

  ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    if (lists.empty()) return nullptr;
    if (lists.size() == 1)return lists.front();

    ListNode *res;
    res = mergeTwoLists(lists[0], lists[1]);
    for (int i = 2; i < (int)lists.size(); i++) {
      res = mergeTwoLists(res, lists[i]);
    }
    return res;
  }
  // *********************************************************
  // TODO: 53.22% write a article
  // 1. 使用vector将数存起来，然后排序，再将结果放到一个新的链表中
  ListNode *mergeKLists1(std::vector<ListNode *> &lists) {
    if (lists.empty()) return nullptr;
    if (lists.size() == 1)return lists.front();
    ListNode res, *t = &res;
    std::vector<int> temp;
    for (int i = 0; i < (int)lists.size(); i++) {
      ListNode *p = lists[i];
      while (p) {
        temp.push_back(p->val);
        p = p->next;
      }
    }
    std::sort(temp.begin(), temp.end());
    for (int i : temp) {
      t->next = new ListNode(i);
      t = t->next;
    }
    return res.next;
  }

  // TODO: 考虑一些 "哈夫曼树" 是否可行
  // ...

  // 打印ListNode
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
  ListNode *l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
  ListNode *l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
  ListNode *l3 = new ListNode(2, new ListNode(6));
  std::vector<ListNode*> lists({l1, l2, l3});
  Solution s;
  ListNode *res = s.mergeKLists1(lists);
  s.PrintL(res);
  return 0;
}
