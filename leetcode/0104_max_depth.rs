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
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut max_d = 0i32;
        Solution::dfs(root, &mut max_d, 0);
        max_d
    }

    fn dfs(root: Option<Rc<RefCell<TreeNode>>>, max_d: &mut i32, cur_d: i32) {
        match root {
            Some(r) => {
                Solution::dfs(r.borrow().left.clone(), max_d, cur_d + 1);
                Solution::dfs(r.borrow().right.clone(), max_d, cur_d + 1);
            },
            None => {
                *max_d = std::cmp::max(*max_d, cur_d);
            },
        }
    }
}

fn main() {
    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    println!("{}", Solution::max_depth(Some(root)));
}
