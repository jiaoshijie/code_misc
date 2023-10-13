#include "head.hpp"

using std::string;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
  string serialize(TreeNode *root) {
    if (!root) return "[]";
    string ret = "[";
    std::vector<TreeNode*> v;
    v.push_back(root);
    size_t index = 0;
    while (index < v.size()) {
      auto p = v[index++];
      if (p) {
        v.push_back(p->left);
        v.push_back(p->right);
      }
    }

    while (!v.back()) v.pop_back();

    for (auto& n : v) {
      if (n) {
        ret += std::to_string(n->val) + ",";
      } else {
        ret += "null,";
      }
    }

    ret[ret.size() - 1] = ']';
    return ret;
  }

  TreeNode* deserialize(string data) {
    if (data.size() == 2) return nullptr;
    size_t pos = data.find(',');
    if (pos == std::string::npos) {
      return new TreeNode(std::stoi(data.substr(1, data.size() - 2)));
    }
    size_t index = 1;
    TreeNode *root = new TreeNode(std::stoi(data.substr(index, pos - index)));
    index = pos + 1;
    std::queue<TreeNode*> q;
    q.push(root);
    for (;;) {
      TreeNode *p = q.front();
      q.pop();
      pos = data.find(',', index);
      if (pos == std::string::npos) {
        p->left = new TreeNode(std::stoi(data.substr(index, data.size() - index - 1)));
        break;
      } else {
        if (data.substr(index, pos - index) != "null") {
          p->left = new TreeNode(std::stoi(data.substr(index, pos - index)));
          q.push(p->left);
        }
        index = pos + 1;
      }

      pos = data.find(',', index);
      if (pos == std::string::npos) {
        p->right = new TreeNode(std::stoi(data.substr(index, data.size() - index - 1)));
        break;
      } else {
        if (data.substr(index, pos - index) != "null") {
          p->right = new TreeNode(std::stoi(data.substr(index, pos - index)));
          q.push(p->right);
        }
        index = pos + 1;
      }
    }
    return root;
  }
};

int main() {
  TreeNode *head = new TreeNode(1);
  head->left = new TreeNode(2);
  head->right = new TreeNode(3);
  head->right->left = new TreeNode(4);
  head->right->right = new TreeNode(5);
  head->right->left->left = new TreeNode(6);
  head->right->left->right = new TreeNode(7);
  Codec s;
  std::cout << s.serialize(head) << std::endl;
  std::cout << s.serialize(s.deserialize(s.serialize(head))) << std::endl;
  return 0;
}
