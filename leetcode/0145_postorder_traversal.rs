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
    pub fn postorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut ret = Vec::new();
        let mut stack = Vec::new();
        let mut p = root;
        let mut q = None;

        while !stack.is_empty() || p != None {
            loop {
                match p {
                    Some(pp) => {
                        stack.push(pp.clone());
                        p = pp.borrow_mut().left.clone();
                    },
                    None => break,
                }
            }

            if !stack.is_empty() {
                let top = stack[stack.len() - 1].clone();
                if top.borrow().right == None || top.borrow().right == q {
                    ret.push(top.borrow().val);
                    q = Some(top.clone());
                    stack.pop();
                } else {
                    p = top.borrow().right.clone();
                }
            }
        }

        ret
    }
}

fn main() {
    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.borrow_mut().right.as_mut().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
    println!("{:?}", Solution::postorder_traversal(Some(root)));
}
