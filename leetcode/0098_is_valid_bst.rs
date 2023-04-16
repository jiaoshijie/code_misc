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
    pub fn is_valid_bst(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        let mut stack = std::collections::VecDeque::new();

        let mut p = root;

        while !stack.is_empty() || p != None {
            let pp = p.unwrap().clone();
            match (pp.clone().borrow().left.clone(), pp.clone().borrow().right.clone()) {
                (Some(l), Some(r)) => {
                    if r.borrow().val <= pp.borrow().val || pp.borrow().val <= l.borrow().val {
                        return false;
                    }
                    stack.push_back(l.clone());
                    stack.push_back(r.clone());
                },
                (None, Some(r)) => {
                    if r.borrow().val <= pp.borrow().val {
                        return false;
                    }
                    stack.push_back(r.clone());
                },
                (Some(l), None) => {
                    if l.borrow().val >= pp.borrow().val {
                        return false;
                    }
                    stack.push_back(l.clone());
                },
                (None, None) => {}
            }
            p = stack.pop_front();
        }
        true
    }
}

fn main() {
}
