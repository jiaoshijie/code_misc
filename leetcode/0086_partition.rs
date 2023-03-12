// TODO: 解决方法异常垃圾，但其他人好像也没什么好的解法

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

struct Solution;

impl Solution {
    // pub fn partition(head: Option<Box<ListNode>>, x: i32) -> Option<Box<ListNode>> {
    //     let mut head = head;
    //     let mut p = head.as_mut().map(|node| &mut **node);
    //     while let Some(pp) = p {
    //         if pp.val >= x {
    //             break;
    //         }
    //         p = pp.next.as_mut().map(|node| &mut **node);
    //     }
    //     while p != None && q != None {
    //         while let Some(pp) = p {
    //             // if pp.val
    //         }
    //     }
    //     head
    // }
    pub fn partition(head: Option<Box<ListNode>>, x: i32) -> Option<Box<ListNode>> {
        if head == None {
            return None;
        }
        let (mut v1, mut v2) = (Vec::new(), Vec::new());
        let mut p = head;
        loop {
            match p {
                Some(pp) => {
                    if pp.val < x {
                        v1.push(pp.val);
                    } else {
                        v2.push(pp.val);
                    }
                    p = pp.next;
                },
                None => break,
            }
        }
        for i in v2 {
            v1.push(i);
        }
        let mut ret = Some(Box::new(ListNode::new(v1[0])));
        let mut p = ret.as_mut().map(|node| &mut **node);
        for i in 1..v1.len() {
            match p {
                Some(pp) => {
                    pp.next = Some(Box::new(ListNode::new(v1[i])));
                    p = pp.next.as_mut().map(|node| &mut **node);
                },
                None => break,
            }
        }
        ret
    }
}

fn main() {
    let mut my_box = Box::new(ListNode::new(20));
    (*my_box).next = Some(Box::new(ListNode::new(10)));
    (*(*my_box).next.as_mut().unwrap()).next = Some(Box::new(ListNode::new(30)));
    println!("{:?}", Solution::partition(Some(my_box), 20));
}
