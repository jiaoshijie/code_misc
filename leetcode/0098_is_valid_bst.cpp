#include "head.hpp"

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

using std::vector;

// NOTE: both implementaion are Ok.
class Solution {
public:
  void dfs_lots_space(TreeNode *root, vector<int> &data) {
    if (root == nullptr)
      return;
    dfs_lots_space(root->left, data);
    data.push_back(root->val);
    dfs_lots_space(root->right, data);
  }
  bool isValidBST_lots_space(TreeNode *root) {
    vector<int> data;
    dfs_lots_space(root, data);
    for (size_t i = 1; i < data.size(); i++) {
      if (data[i] <= data[i - 1])
        return false;
    }
    return true;
  }

  bool dfs(TreeNode *root, long l, long r) {
    if (root == nullptr)
      return true;
    bool ret = true;
    if (root->val <= l || root->val >= r)
      return false;

    ret = ret && dfs(root->left, l, root->val);
    if (ret) {
      ret = ret && dfs(root->right, root->val, r);
    }
    return ret;
  }
  bool isValidBST(TreeNode *root) {
    bool ret = true;
    ret = ret && dfs(root->left, -2147483649, root->val);
    if (ret)
      ret = ret && dfs(root->right, root->val, 2147483648);
    return ret;
  }
};

int main(void) {
  Solution s;
  return 0;
}
