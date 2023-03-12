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
    pub fn path_sum(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32) -> Vec<Vec<i32>> {
        let mut ret: Vec<Vec<i32>> = Vec::new();
        let mut c_arr: Vec<i32> = Vec::new();
        Solution::dfs(root, target_sum, &mut ret, 0, &mut c_arr);
        ret
    }

    fn dfs(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32, ret: &mut Vec<Vec<i32>>, c_sum: i32, c_arr: &mut Vec<i32>) {
        match root {
            Some(r) => {
                let rb = r.borrow();
                c_arr.push(rb.val);
                if c_sum + rb.val == target_sum  && rb.left == None && rb.right == None {
                    ret.push(c_arr.clone());
                    c_arr.pop();
                    return;
                }
                Solution::dfs(rb.left.clone(), target_sum, ret, c_sum + rb.val, c_arr);
                Solution::dfs(rb.right.clone(), target_sum, ret, c_sum + rb.val, c_arr);
                c_arr.pop();
            },
            None => {},
        };
    }
}

fn main() {
}
