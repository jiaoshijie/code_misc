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
    pub fn is_balanced(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        let (ret, _) = Solution::dfs(root, 0);
        ret
    }

    fn dfs(root: Option<Rc<RefCell<TreeNode>>>, mut h: i32) -> (bool, i32) {
        if let Some(rt) = root {
            h += 1;
            let (lb, l) = Solution::dfs(rt.borrow().left.clone(), h);
            let (rb, r) = Solution::dfs(rt.borrow().right.clone(), h);
            if !lb || !rb || (l - r).abs() > 1 {
                return (false, 0);
            }
            h = std::cmp::max(l, r);
        }
        (true, h)
    }
}

fn main() {
}
