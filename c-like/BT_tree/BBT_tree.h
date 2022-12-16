#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class BBT_tree {
private:
  struct BBT_node {
    int key;
    BBT_node *lchild, *rchild;
    int height;
    BBT_node(int i) : key(i), height(1), lchild(nullptr), rchild(nullptr) {}
  };
  BBT_node *root;

  // 左旋
  void LL(BBT_node **root) {
    BBT_node *lchild = (*root)->lchild;
    (*root)->lchild = lchild->rchild;
    lchild->rchild = (*root);
    (*root) = lchild;
    /****调整后要更新一下树的高度****/
    lchild->rchild->height = std::max(get_height(lchild->rchild->lchild),
                                      get_height(lchild->rchild->rchild)) +
                             1; // 原先的root
    (*root)->height = std::max(get_height((*root)->lchild),
                               get_height((*root)->rchild)) +
                      1; // 原先的root的左孩子
  }
  // 右旋
  void RR(BBT_node **root) {
    BBT_node *rchild = (*root)->rchild;
    (*root)->rchild = rchild->lchild;
    rchild->lchild = (*root);
    (*root) = rchild;
    /****调整后要更新一下树的高度****/
    rchild->lchild->height = std::max(get_height(rchild->lchild->lchild),
                                      get_height(rchild->lchild->rchild)) +
                             1; // 原先的root
    (*root)->height = std::max(get_height((*root)->lchild),
                               get_height((*root)->rchild)) +
                      1; // 原先root的右孩子
  }

  // 获取树的高度
  int get_height(const BBT_node *root) {
    if (root == nullptr)
      return 0;
    else
      return root->height;
  }

  //插入节点
  void insert_node(BBT_node **root, const int value) {
    if ((*root) == nullptr) {
      (*root) = new BBT_node(value);
    } else if (value < (*root)->key) {
      insert_node(&(*root)->lchild, value); // 进行递归插入数据
      // 计算平衡因子, 判断是否需要旋转
      if (get_height((*root)->lchild) - get_height((*root)->rchild) > 1) {
        if (value < (*root)->lchild->key) LL(root); // 进行左旋
        else {
          RR(&(*root)->lchild); // 先对节点的左孩子进行右旋
          LL(root);             // 然后进行左旋
        }
      }
    } else if (value > (*root)->key) {
      insert_node(&(*root)->rchild, value);
      // 计算平衡因子, 判断是否需要旋转
      if (get_height((*root)->lchild) - get_height((*root)->rchild) < -1) {
        if (value > (*root)->rchild->key)
          RR(root);
        else {
          LL(&(*root)->rchild);
          RR(root);
        }
      }
    } else // 如果数据已经存在则直接退出
    {
      std::cout << "data is existed!" << std::endl;
    }
    // 更新树的高度
    (*root)->height =
        std::max(get_height((*root)->lchild), get_height((*root)->rchild)) + 1;
  }

  // 删除数据
  bool delete_node(BBT_node **root, int value) {
    if ((*root) == nullptr)
      return false;
    else if (value == (*root)->key) // 如果相等, 删除节点
    {
      BBT_node *old = nullptr;
      if (!(*root)->lchild && !(*root)->rchild) // 左右孩子都为空
      {
        old = *root;
        *root = nullptr;
        delete old;
      } else if (!(*root)->lchild && (*root)->rchild) // 左孩子为空右孩子不为空
      {
        old = *root;
        *root = (*root)->rchild;
        delete old;
      } else if ((*root)->lchild && !(*root)->rchild) // 左孩子不为空右孩子为空
      {
        old = *root;
        *root = (*root)->lchild;
        delete old;
      } else // 左右孩子都不为空
      {
        old = *root;
        BBT_node *place = get_prev_min((*root)->rchild);
        *root = place->lchild;
        (*root)->rchild = old->rchild;
        (*root)->lchild = old->lchild;
        place->lchild = nullptr;
      }
    } else if (value > (*root)->key) // 如果大于节点数据则向右子树遍历删除
    {
      if (this->delete_node(&(*root)->rchild, value)) // 删除右节点需要进行左旋
      {
        if (get_height((*root)->lchild) - get_height((*root)->rchild) > 1) {
          if (get_height((*root)->lchild->lchild) <
              get_height((*root)->lchild->rchild)) {
            // 如果左子树的高度比右子树低则进行右左旋
            RR(&(*root)->lchild);
            LL(root);
          } else
            LL(root);
        }
      }
    } else // 遍历左子树删除
    {
      if (this->delete_node(&(*root)->lchild, value)) {
        if (get_height((*root)->lchild) - get_height((*root)->rchild) < -1) {
          if (get_height((*root)->lchild->lchild) >
              get_height((*root)->lchild->rchild)) {
            LL(&(*root)->rchild);
            RR(root);
          } else
            RR(root);
        }
      }
    }
    if (*root)
      (*root)->height =
          std::max(get_height((*root)->lchild), get_height((*root)->rchild)) +
          1;
    return true;
  }

  // 中序遍历
  void inorder(BBT_node *root) {
    if (root) {
      inorder(root->lchild);
      std::cout << root->key << ' ';
      inorder(root->rchild);
    }
  }

  // 获取最小节点的前一个节点
  BBT_node *get_prev_min(BBT_node *root) {
    if (!root || !root->lchild)
      return nullptr;
    while (root->lchild->lchild)
      root = root->lchild;
    return root;
  }
  // 获取最大节点(目前好像没用)
  BBT_node *get_prev_max(BBT_node *root) {
    if (!root || !root->rchild)
      return nullptr;
    while (root->rchild->rchild)
      root = root->rchild;
    return root;
  }

public:
  BBT_tree() { this->root = nullptr; }
  ~BBT_tree() {}

  // 插入数据，接口函数
  void insert(const int value) {
    // BBT_node* root_fun = this->root;
    this->insert_node(&this->root, value);
  }
  // 以vector形式插入数据，接口函数
  void insert_array(const std::vector<int> Array) {
    for (auto data = Array.begin(); data != Array.end(); data++) {
      insert(*data);
    }
  }
  // 中序遍历，接口函数
  void inorder_tree() { inorder(root); }
  // 删除数据，接口函数
  void del(int value) { this->delete_node(&root, value); }
};
