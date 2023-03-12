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
    pub fn sorted_array_to_bst(nums: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut ret: Option<Rc<RefCell<TreeNode>>> = None;
        let len = nums.len();
        Solution::dfs(&nums, len, &mut ret);
        ret
    }

    // TODO: Vec<i32> to [i32]
    fn dfs(nums: &[i32], len: usize, root: &mut Option<Rc<RefCell<TreeNode>>>) {
        let index = len / 2;
        *root = Some(Rc::new(RefCell::new(TreeNode::new(nums[index]))));
        if index > 0 {
            Solution::dfs(&nums[0..index], index, &mut root.clone().unwrap().borrow_mut().left);
        }
        if index < len - 1 {
            Solution::dfs(&nums[index+1..], len - index - 1, &mut root.clone().unwrap().borrow_mut().right);
        }
    }
}

fn main() {
    let res = Solution::sorted_array_to_bst(vec![-10, -3, 0, 5, 9]);
    println!("{:?}", res);
}
