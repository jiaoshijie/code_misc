use std::collections::VecDeque;

#[allow(dead_code)]
fn print_type<T>(_: &T) {
    println!("{}", std::any::type_name::<T>());
}

#[derive(Debug)]
struct Node {
    val: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    pub fn new(val: i32) -> Self {
        Self {
            val,
            left: None,
            right: None,
        }
    }
}

#[derive(Debug)]
struct Tree {
    pub head: Option<Box<Node>>,
}

impl Tree {
    pub fn new() -> Self {
        Self { head: None }
    }

    pub fn build_from_slice(array: &[i32]) -> Self {
        let mut iter = array.iter();
        let mut queue = VecDeque::new();
        let mut ret = Tree::new();

        if let Some(&v) = iter.next() {
            ret.head = Node::new(v).into();
            queue.push_back(ret.head.as_mut().unwrap());
            while let Some(&v) = iter.next() {
                let t: &mut Box<Node> = queue.pop_front().unwrap();
                t.left = Node::new(v).into();
                queue.push_back(t.left.as_mut().unwrap());
                if let Some(&v) = iter.next() {
                    t.right = Node::new(v).into();
                    queue.push_back(t.right.as_mut().unwrap());
                }
            }
        }

        ret
    }

    #[allow(dead_code)]
    pub fn print(&self) {
        let mut queue: VecDeque<(usize, &Box<Node>)> = VecDeque::new();
        if let Some(ref head) = self.head {
            queue.push_back((0, head));
            let mut cur_seq = 0;
            while let Some((node_seq, node)) = queue.pop_front() {
                if node_seq > cur_seq {
                    println!();
                    cur_seq = node_seq;
                }
                print!("{} ", node.val);
                if let Some(ref left) = node.left {
                    queue.push_back((node_seq + 1, left));
                }
                if let Some(ref right) = node.right {
                    queue.push_back((node_seq + 1, right));
                }
            }
            println!();
        } else {
            eprintln!("INFO: It's an empty tree!!!");
        }
    }

    #[allow(dead_code)]
    pub fn pretty_print(&self) {
        let mut stack: Vec<(usize, &Box<Node>)> = Vec::new();
        if let Some(ref head) = self.head {
            stack.push((0, head));
            let mut l = &head.left;
            let mut level = 0;
            while !stack.is_empty() {
                while let Some(ref left) = l {
                    level += 1;
                    stack.push((level, left));
                    l = &left.left;
                }
                if let Some((lev, root)) = stack.pop() {
                    println!("{}{}", " ".repeat((lev * 3).saturating_sub(1)), root.val);
                    if let Some(ref right) = root.right {
                        level = lev + 1;
                        stack.push((level, right));
                        l = &right.left;
                    }
                }
            }
        }
    }

    #[allow(dead_code)]
    fn reverse_recursive(root: &mut Option<Box<Node>>) {
        if let Some(root) = root {
            // TODO: why it works?
            // print_type(&root);
            std::mem::swap(&mut root.left, &mut root.right);
            Self::reverse_recursive(&mut root.left);
            Self::reverse_recursive(&mut root.right);
        }
    }

    #[allow(dead_code)]
    fn reverse_non_recursive(root: &mut Option<Box<Node>>) {
        if let Some(root) = root {
            let mut stack: Vec<&mut Box<Node>> = Vec::new();
            stack.push(root);
            while let Some(root) = stack.pop() {
                std::mem::swap(&mut root.left, &mut root.right);
                if let Some(ref mut left) = root.left {
                    stack.push(left);
                }
                if let Some(ref mut right) = root.right {
                    stack.push(right);
                }
            }
        }
    }

    pub fn reverse(&mut self) {
        // Self::reverse_recursive(&mut self.head);
        Self::reverse_non_recursive(&mut self.head);
    }
}

impl From<Node> for Option<Box<Node>> {
    fn from(node: Node) -> Self {
        Some(Box::new(node))
    }
}

fn main() {
    // let mut tree = Tree::build_from_slice(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]);
    let mut tree = Tree::build_from_slice(&[1, 2, 3, 4, 5, 6, 7]);
    tree.pretty_print();
    tree.reverse();
    println!("----------------------");
    tree.pretty_print();
}
