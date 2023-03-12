// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

use std::rc::Rc;
use std::cell::RefCell;

struct Solution;

impl Solution {
    pub fn has_path_sum(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32) -> bool {
        Solution::dfs(root, target_sum, 0)
    }

    fn dfs(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32, c_sum: i32) -> bool {
        match root {
            Some(r) => {
                let rb = r.borrow();
                if target_sum == c_sum + rb.val && rb.left == None && rb.right == None {
                    true
                } else {
                    let l = Solution::dfs(rb.left.clone(), target_sum, c_sum + rb.val);
                    let r = Solution::dfs(rb.right.clone(), target_sum, c_sum + rb.val);
                    if l || r {
                        true
                    } else {
                        false
                    }
                }
            },
            None => false,
        }
    }
}

fn main() {
}
