use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

#[allow(dead_code)]
fn print_type<T>(_: &T) {
    println!("INFO: type is `{}`", std::any::type_name::<T>());
}

#[derive(Default, Debug)]
struct Node {
    val: i32,
    left: Option<Rc<RefCell<Node>>>,
    right: Option<Rc<RefCell<Node>>>,
}

impl Node {
    pub fn new(val: i32) -> Self {
        Self {
            val,
            ..Default::default()
        }
    }
}

impl From<Node> for Option<Rc<RefCell<Node>>> {
    fn from(node: Node) -> Self {
        Some(Rc::new(RefCell::new(node)))
    }
}

#[derive(Debug)]
struct Tree {
    head: Option<Rc<RefCell<Node>>>,
    count: usize,
}

impl Tree {
    pub fn new() -> Self {
        Self {
            head: None,
            count: 0,
        }
    }

    fn check(_count: usize) -> bool {
        todo!()
    }

    pub fn build_from_slice(arr: &[i32]) -> Self {
        let mut iter = arr.iter();
        let mut queue = VecDeque::new();
        let mut ret = Tree::new();
        ret.count = arr.len();
        if let Some(&val) = iter.next() {
            let new_node = Rc::new(RefCell::new(Node::new(val)));
            queue.push_back(new_node.clone());
            ret.head = new_node.into();
            while let Some(&val) = iter.next() {
                let t = queue.pop_front().unwrap();
                let new_node = Rc::new(RefCell::new(Node::new(val)));
                queue.push_back(new_node.clone());
                t.borrow_mut().left = new_node.into();
                if let Some(&val) = iter.next() {
                    let new_node = Rc::new(RefCell::new(Node::new(val)));
                    queue.push_back(new_node.clone());
                    t.borrow_mut().right = new_node.into();
                }
            }
        }
        ret
    }

    pub fn pretty_print(&self) {
        let mut queue: VecDeque<(usize, Rc<RefCell<Node>>)> = VecDeque::new();
        // let row = (self.count + 1).ilog2();
        if let Some(ref root) = self.head {
            queue.push_back((0, root.clone()));
            let mut cur_seq = 0usize;
            while let Some((node_seq, root)) = queue.pop_front() {
                if node_seq > cur_seq {
                    println!();
                    cur_seq = node_seq;
                }
                print!("{} ", root.borrow().val);
                if let Some(ref left) = root.borrow().left {
                    queue.push_back((node_seq + 1, left.clone()));
                }
                if let Some(ref right) = root.borrow().right {
                    queue.push_back((node_seq + 1, right.clone()));
                }
            }
            println!();
        } else {
            println!("INFO: It's an empty tree!!!");
        }
    }

    fn recursive_reverse(root: Option<Rc<RefCell<Node>>>) {
        if let Some(r) = root {
            let left = r.clone();
            let right = r.clone();
            let left = &mut left.borrow().left;
            let right = &mut right.borrow().right;
            std::mem::swap(left, right);
        }
    }

    pub fn reverse(&self) {
        Self::recursive_reverse(self.head.clone());
    }
}

fn main() {
    let root = Tree::build_from_slice(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]);
    root.pretty_print();
    root.reverse();
    println!("\n");
    root.pretty_print();
}
