#include "head.hpp"

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// NOTE(make it to be linux kernal style): Using merge sort idea.
class Solution {
public:
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head;
    ListNode** indirect = &head;
    while (list1 && list2) {
      if (list1->val < list2->val) {
        *indirect = list1;
        list1 = list1->next;
      } else {
        *indirect = list2;
        list2 = list2->next;
      }
      indirect = &(*indirect)->next;
    }
    *indirect = (ListNode*)((long long)list1 | (long long)list2);

    return head;
  }

  // TODO: Why recursive version much faster then iteration version?
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.size() == 0) return nullptr;
    return merge(lists, 0, lists.size());
  }

  ListNode* merge(std::vector<ListNode*>& lists, int begin, int end) {
    int len = end - begin;
    if (len < 0) return nullptr;
    if (len == 1) return lists[begin];
    int mid = begin + end >> 1;
    ListNode *left = merge(lists, begin, mid);
    ListNode *right = merge(lists, mid, end);
    return mergeTwoLists(left, right);
  }

  // ListNode* mergeKLists(std::vector<ListNode*>& lists) {
  //   if (lists.size() == 0) return nullptr;

  //   for (int interval = 1; interval < lists.size(); interval *= 2) {
  //     for (int i = 0; i + interval < lists.size(); i += interval * 2) {
  //       lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
  //     }
  //   }
  //   return lists[0];
  // }

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

/*
class Solution {
public:
  // 超时
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
*/

int main() {
  ListNode *l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
  ListNode *l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
  ListNode *l3 = new ListNode(2, new ListNode(6));
  std::vector<ListNode*> lists({l1, l2, l3});
  Solution s;
  ListNode *res = s.mergeKLists(lists);
  s.PrintL(res);
  return 0;
}
