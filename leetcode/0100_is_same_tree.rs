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
    pub fn is_same_tree(p: Option<Rc<RefCell<TreeNode>>>, q: Option<Rc<RefCell<TreeNode>>>) -> bool {
        Self::dfs(p, q)
    }

    fn dfs(p: Option<Rc<RefCell<TreeNode>>>, q: Option<Rc<RefCell<TreeNode>>>) -> bool {
        match (p, q) {
            (Some(pp), Some(qq)) => {
                if pp.borrow().val == qq.borrow().val && Self::dfs(pp.borrow().left.clone(), qq.borrow().left.clone()) &&  Self::dfs(pp.borrow().right.clone(), qq.borrow().right.clone()) {
                    true
                } else {
                    false
                }
            },
            (None, None) => true,
            _ => false,
        }
    }
}

fn main() {
    println!("{}", Solution::is_same_tree(None, None));
}
