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
use std::collections::VecDeque;

struct Solution;

impl Solution {
    // recursively
    // pub fn is_symmetric_recursively(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
    //     match root {
    //         Some(r) => Solution::dfs(r.borrow().left.clone(), r.borrow().right.clone()),
    //         None => true,
    //     }
    // }

    // fn dfs(p: Option<Rc<RefCell<TreeNode>>>, q: Option<Rc<RefCell<TreeNode>>>) -> bool {
    //     match (p, q) {
    //         (Some(pp), Some(qq)) => {
    //             if pp.borrow().val == qq.borrow().val &&
    //                 Solution::dfs(pp.borrow().left.clone(), qq.borrow().right.clone()) &&
    //                     Solution::dfs(pp.borrow().right.clone(), qq.borrow().left.clone()) {
    //                         true
    //                     } else {
    //                         false
    //                     }
    //         },
    //         (None, None) => true,
    //         _ => false,
    //     }
    // }

    // iteratively
    pub fn is_symmetric(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        let mut queue = VecDeque::new();
        queue.push_back(root.clone());
        let mut prev = 1usize;
        let mut next: usize;
        while prev != 0 {
            next = 0;
            for i in 0..prev {
                if let Some(q) = queue[i].clone() {
                    next += 2;
                    queue.push_back(q.borrow().left.clone());
                    queue.push_back(q.borrow().right.clone());
                }
            }

            for i in 0..(prev / 2) {
                match (queue[i].clone(), queue[prev - i - 1].clone()) {
                    (Some(l), Some(r)) => {
                        if l.borrow().val != r.borrow().val {
                            return false;
                        }
                    },
                    (None, None) => {},
                    _ => return false,
                }
            }

            for _ in 0..prev {
                queue.pop_front();
            }
            prev = next;
        }
        true
    }
}

fn main() {
    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    println!("{}", Solution::is_symmetric(Some(root)));
}
