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
    #[allow(dead_code)]
    pub fn generate_trees_bak(n: i32) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
        let mut res = Vec::new();
        let mut flag = vec![false; n as usize];
        for i in 1..(n as usize + 1) {
            flag[i - 1] = true;
            let root = Rc::new(RefCell::new(TreeNode::new(i as i32)));
            Self::dfs(n as usize, root, &mut flag, &mut res);
            flag[i - 1] = false;
        }

        res
    }

    fn check(flag: &Vec<bool>) -> bool {
        for i in flag {
            if *i == false {
                return false;
            }
        }
        true
    }

    fn deepcopy(s: Rc<RefCell<TreeNode>>, t: Rc<RefCell<TreeNode>>) {
        if let Some(ref ss) = s.borrow().left {
            t.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(ss.borrow().val))));
            Self::deepcopy(ss.clone(), t.borrow_mut().left.as_mut().unwrap().clone());
        }
        if let Some(ref ss) = s.borrow().right {
            t.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(ss.borrow().val))));
            Self::deepcopy(ss.clone(), t.borrow_mut().right.as_mut().unwrap().clone());
        }
    }

    fn dfs(n: usize, r: Rc<RefCell<TreeNode>>, flag: &mut Vec<bool>, res: &mut Vec<Option<Rc<RefCell<TreeNode>>>>) {
        if Self::check(flag) && ! res.contains(&Some(r.clone())) {
            let t = Rc::new(RefCell::new(TreeNode::new(r.borrow().val)));
            Self::deepcopy(r.clone(), t.clone());
            res.push(Some(t));
            return;
        }

        for i in 1..(n + 1) {
            if flag[i - 1] == false {
                flag[i - 1] = true;
                let mut p = r.clone();
                loop {
                    if i < p.borrow().val as usize {  // left hand
                        if p.borrow().left == None {
                            p.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(i as i32))));
                            break;
                        }
                        p = p.clone().borrow_mut().left.clone().unwrap();
                    } else {  // right hand
                        if p.borrow().right == None {
                            p.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(i as i32))));
                            break;
                        }
                        p = p.clone().borrow_mut().right.clone().unwrap();
                    }
                }
                Self::dfs(n, r.clone(), flag, res);
                flag[i - 1] = false;

                if i < p.borrow().val as usize {
                    p.borrow_mut().left = None;
                } else {
                    p.borrow_mut().right = None;
                }
            }
        }
    }

    pub fn generate_trees(n: i32) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
        Solution::dd(1, n as usize + 1)
    }

    pub fn dd(left: usize, right: usize) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
        if left >= right {
            return vec![None];
        }
        let mut res = Vec::new();
        for i in left..right {
            let left = Solution::dd(left, i);
            let right = Solution::dd(i + 1, right);
            for l in &left {
                for r in &right {
                    let p = Rc::new(RefCell::new(TreeNode::new(i as i32)));
                    p.borrow_mut().left = l.clone();
                    p.borrow_mut().right = r.clone();
                    res.push(Some(p.clone()));
                }
            }
        }
        res
    }
}

fn main() {
    // Solution::generate_trees(3);
    let res = Solution::generate_trees(1);
    println!("{}", res.len());
    // for i in res {
    //     println!("{:?}", i);
    // }
}
