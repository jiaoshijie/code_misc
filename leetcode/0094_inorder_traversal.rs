use std::rc::Rc;
use std::cell::RefCell;

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

struct Solution;

impl Solution {
    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut ret = vec![];
        let mut stack = vec![];
        let mut left = root.clone();
        while left != None || !stack.is_empty() {
            if left != None {
                loop {
                    match left {
                        Some(l) => {
                            stack.push(l.clone());
                            left = l.borrow().left.clone();
                        },
                        None => break,
                    }
                }
            }

            if let Some(top) = stack.pop() {
                ret.push(top.borrow().val);
                left = top.borrow().right.clone();
            }
        }
        ret
    }
}

fn main() {
    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    // root.borrow_mut().right.as_ref().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
    let res = Solution::inorder_traversal(Some(root));
    println!("{:?}", res);
}
