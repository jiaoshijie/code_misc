#[allow(dead_code)]
fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution;

impl Solution {
    #[allow(unused_variables)]
    pub fn reverse_between(
        head: Option<Box<ListNode>>,
        left: i32,
        right: i32,
    ) -> Option<Box<ListNode>> {
        let mut head = head;
        let mut q1: &mut Option<Box<ListNode>> = &mut None;
        let mut i = 1i32;
        while i < left {
            match q1 {
                Some(qq1) => {
                    q1 = &mut qq1.next;
                }
                None => {
                    q1 = &mut head;
                }
            }
            i += 1;
        }
        let mut p1 = &mut None;
        if *q1 == None {
            p1 = &mut head;
        } else {
            p1 = &mut (*q1).as_mut().unwrap().next;
        }
        let mut p2 = &mut (*p1).as_mut().unwrap().next;
        while i < right {
            let t = &mut (*p2).as_mut().unwrap().next;
            (*p2).as_mut().unwrap().next = (*p1).clone();
            i += 1;
        }

        None
    }
}

fn main() {
    let mut head = Some(Box::new(ListNode::new(1)));
    head.as_mut().unwrap().next = Some(Box::new(ListNode::new(2)));
    head.as_mut().unwrap().next.as_mut().unwrap().next = Some(Box::new(ListNode::new(3)));
    head.as_mut()
        .unwrap()
        .next
        .as_mut()
        .unwrap()
        .next
        .as_mut()
        .unwrap()
        .next = Some(Box::new(ListNode::new(4)));
    println!("{:?}", Solution::reverse_between(head, 2, 3));
}
