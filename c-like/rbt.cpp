#include <iostream>

// NOTE: https://zhuanlan.zhihu.com/p/370703859

/*
 * 1. 节点分为红色或者黑色
 * 2. 根节点必定为黑色
 * 3. 叶子节点都为黑色，且为null
 * 4. 连接红色节点的两个子节点都为黑色
 * 5. 从任意节点出发，到其每个叶子节点的路径中包含相同数量的黑色节点
 * 6. 新加入到红黑树的节点为红色节点
 * */
struct RBT {
  int val;
  bool is_black;
  RBT *left;
  RBT *right;

  RBT(int val) : val(val), is_black(true), left(nullptr), right(nullptr) {}
  RBT(int val, bool is_black) : val(val), is_black(is_black), left(nullptr), right(nullptr) {}
  ~RBT() {}

  bool insert(int new_val) {
    RBT* p = this;
    while(p) {
      if (p->val > new_val) {
        if (p->right != nullptr) {
          p = p->right;
        } else {
          p->right = new RBT(new_val, false);
          break;
        }
      } else if (p->val < new_val) {
        if (p->left != nullptr) {
          p = p->left;
        } else {
          p->left = new RBT(new_val, false);
          break;
        }
      } else { // p->val == new_val
        return false;
      }
    }

    // 如果新插入节点的父节点是黑色节点, 无需调整直接返回
    if (p->is_black) return true;
    // TODO: 1. 如果父节点为红色节点，则需要对父节点及相关节点进行变色.
    // TODO: 2. 如果单单变色已经无法满足红黑树的规则，则需要进行旋转操作
  }

  bool remove(int val) {
    RBT* p = this;
    while (p) {
      if (p->val == val) {
        // TODO: 删除操作
        // 1. 如果待删除节点为红色节点且其的子节点至少有一个为null节点，
        //    删除后直接将其有值的节点取代当前节点即可,
        //    若都为null，将当前节点设置为null
        // 2. 在1的基础上如果待删除节点为黑色节点，则可能需要调整节点颜色

        // 3. 子节点都是非null节点
        //   3.1 找到该节点的前驱或者后继
        //   3.2 将前驱或者后继的值复制到该节点中，然后删掉前驱或者后继
        //   3.3 以删除前驱节点来讨论
        //     3.3.1 前驱为黑色节点，并且有一个非 null 子节点
        //     3.3.2 前驱为黑色节点，同时子节点都为 null
        //     3.3.3 前驱为红色节点，同时子节点都为 null

        return true;
      } else if (p->val > val) {
        p = p->left;
      } else if (p->val < val) {
        p = p->right;
      }
    }
    return false;
  }

};

int main() {
  
  return 0;
}
