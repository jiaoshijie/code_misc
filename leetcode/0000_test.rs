// #[derive(PartialEq, Eq, Clone, Debug)]
// struct ListNode {
//     val: i32,
//     next: Option<Box<ListNode>>,
// }

// impl ListNode {
//     fn new(val: i32) -> Self {
//         Self {
//             val,
//             next: None,
//         }
//     }
// }

// fn print_type_of<T>(_: &T) {
//     println!("{}", std::any::type_name::<T>())
// }

fn main() {
    // let mut my_box = Box::new(ListNode::new(10));
    // println!("{}", (*my_box).val);
    // (*my_box).next = Some(Box::new(ListNode::new(20)));
    // (*(*my_box).next.as_mut().unwrap()).next = Some(Box::new(ListNode::new(30)));
    // println!("{:?}", my_box);

    // print_type_of(&my_box.next.as_mut());
    // let n = my_box.next.as_mut().map(|node| &mut **node);
    // print_type_of(&n);
    // println!("{:?}", n);
    // println!("{:?}", my_box);
    let mut head: Option<Box<i32>> = None;
    let mut p = head.as_mut().map(|node| &mut **node);
    let mut binding = 10;
    p = Some(&mut binding);
    println!("{:?}", head);
}
