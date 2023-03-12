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
    pub fn min_depth_bak(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if root == None {
            return 0;
        }
        let mut queue = VecDeque::new();
        queue.push_back(root.clone());
        let (mut prev, mut next) = (1usize, 0usize);
        let mut flag = false;
        let mut ret = 0;
        'outer: while prev != 0 {
            for i in 0..prev {
                let top = queue.pop_front().unwrap();
                if let Some(t) = top {
                    next += 2;
                    queue.push_back(t.borrow().left.clone());
                    queue.push_back(t.borrow().right.clone());
                    if flag {
                        flag = false;
                    }
                } else {
                    if flag {
                        break 'outer;
                    } else if i % 2 == 0 {
                        flag = true;
                    }
                }
            }
            ret += 1;
            prev = next;
            next = 0;
        }
        ret
    }

    pub fn min_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        match root {
            Some(r) => {
                let mut queue = VecDeque::new();
                queue.push_back(Some(r));
                let (mut prev, mut next) = (1usize, 0usize);
                let mut ret = 0i32;
                'outer: while prev != 0 {
                    for i in 0..prev {
                        if let Some(Some(t)) = queue.pop_front() {
                            next += 2;
                            queue.push_back(t.borrow().left.clone());
                            queue.push_back(t.borrow().right.clone());
                        } else {
                            if i % 2 == 0 && !queue.is_empty() && queue[0] == None {
                                break 'outer;
                            }
                        }
                    }
                    ret += 1;
                    prev = next;
                    next = 0;
                }
                ret
            },
            None => 0,
        }
    }
}

fn main() {
}
