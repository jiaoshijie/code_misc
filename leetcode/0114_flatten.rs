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
    pub fn flatten(root: &mut Option<Rc<RefCell<TreeNode>>>) {
        let mut ret: Option<Rc<RefCell<TreeNode>>> = None;
        // Solution::dfs((*root).clone(), &mut ret.clone());
        Solution::dfs((*root).clone(), &mut ret);
        *root = ret;
    }

    fn dfs(root: Option<Rc<RefCell<TreeNode>>>, ret: &mut Option<Rc<RefCell<TreeNode>>>) {
        match root {
            Some(r) => {
                if *ret == None {
                    *ret = Some(Rc::new(RefCell::new(TreeNode::new(r.borrow().val))));
                    println!("{:?}", ret);
                } else {
                    let mut p = (*ret).clone();
                    loop {
                        match p.clone() {
                            Some(pp) => {
                                if pp.borrow().right == None {
                                    break;
                                }
                                p = pp.borrow().right.clone();
                            },
                            None => break,
                        }
                    }
                    p.unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(r.borrow().val))));
                }
                Solution::dfs(r.borrow().left.clone(), ret);
                Solution::dfs(r.borrow().right.clone(), ret);
            },
            None => {},
        }
    }
}

fn main() {
    let mut root = Some(Rc::new(RefCell::new(TreeNode::new(1))));
    Solution::flatten(&mut root);

    println!("{:?}", root);
}
