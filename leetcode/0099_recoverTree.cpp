#include "head.hpp"

using std::stack;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  void recoverTree_stack(TreeNode *root) {
    stack<TreeNode *> s;
    TreeNode *cur = root, *last = nullptr, *awful1 = nullptr, *awful2 = nullptr;
    while (cur || !s.empty()) {
      while (cur) {
        s.push(cur);
        cur = cur->left;
      }
      cur = s.top();
      s.pop();
      if (last && last->val > cur->val) {
        if (!awful1) {
          awful1 = last;
          awful2 = cur;
        } else {
          awful2 = cur;
        }
      }
      last = cur;
      cur = cur->right;
    }
    std::swap(awful1->val, awful2->val);
  }

  void dfs(TreeNode *root, TreeNode **last, TreeNode **awful1,
           TreeNode **awful2) {
    if (!root)
      return;
    dfs(root->left, last, awful1, awful2);
    if (*last && (*last)->val > root->val) {
      if (!*awful1) {
        *awful1 = *last;
        *awful2 = root;
      } else {
        *awful2 = root;
      }
    }
    *last = root;
    dfs(root->right, last, awful1, awful2);
  }
  void recoverTree(TreeNode *root) {
    TreeNode *last = nullptr, *awful1 = nullptr, *awful2 = nullptr;
    dfs(root, &last, &awful1, &awful2);
    std::swap(awful1->val, awful2->val);
  }
};
