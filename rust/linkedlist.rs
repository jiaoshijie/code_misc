#[allow(dead_code)]
fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

#[derive(Debug, PartialEq, Clone)] // TODO: Clone is awful code
struct Node {
    value: i32,
    next: Option<Box<Node>>,
}

impl Node {
    pub fn new(value: i32) -> Self {
        Self { value, next: None }
    }
}

#[derive(Debug)]
struct LinkedList(Option<Box<Node>>);

impl LinkedList {
    pub fn new() -> Self {
        Self(None)
    }

    pub fn push_front(&mut self, value: i32) {
        match &mut self.0 {
            Some(p) => {
                let mut new_p = Box::new(Node::new(value));
                // TODO: awful code
                (*new_p).next = Some((*p).clone());
                self.0 = Some(new_p);
            }
            None => {
                self.0 = Some(Box::new(Node::new(value)));
            }
        }
    }

    pub fn push_back(&mut self, value: i32) {
        match &mut self.0 {
            Some(p) => {
                let mut p = p;
                while let Some(ref mut pp) = p.next {
                    p = pp;
                }
                p.next = Some(Box::new(Node::new(value)));
            }
            None => {
                self.0 = Some(Box::new(Node::new(value)));
            }
        }
    }

    // https://stackoverflow.com/questions/36878044/what-is-the-idiomatic-way-to-return-an-error-from-a-function-with-no-result-if-s
    // Usage: insert a new node at pos, `pos` is started from 0.
    pub fn insert(&mut self, pos: usize, value: i32) {
        if self.0 == None {
            self.push_front(value);
            return;
        }
        let mut i = 1usize;
        // TODO: think about this line below
        let mut p = &mut self.0;
        while i < pos && *p != None {
            p = &mut p.as_mut().unwrap().next;
            i += 1;
        }
        if pos == 0 {
            self.push_front(value);
        } else if i != pos {
            self.push_back(value);
        } else {
            let mut new_p = Box::new(Node::new(value));
            new_p.next = p.as_ref().unwrap().next.clone();
            p.as_mut().unwrap().next = Some(new_p);
        }
    }

    #[allow(dead_code)]
    pub fn pop_front(&mut self) -> Option<Box<Node>> {
        if self.0 == None {
            return None;
        }

        let mut p = self.0.clone();
        self.0 = p.as_ref().unwrap().next.clone();
        p.as_mut().unwrap().next = None;
        p
        // TODO: it's awful using `if let` keyword
        // if let Some(mut p) = self.0.clone() {
        //     self.0 = p.next.clone();
        //     p.next = None;
        //     Some(p.clone())
        // } else {
        //     None
        // }
    }

    #[allow(dead_code)]
    pub fn pop_back(&mut self) -> Option<Box<Node>> {
        if self.0 == None {
            return None;
        }

        if self.0.as_ref().unwrap().next == None {
            let p = self.0.clone();
            self.0 = None;
            return p;
        }

        let p = &mut self.0.as_mut().unwrap();
        while p.next.as_mut().unwrap().next != None {
            *p = p.next.as_mut().unwrap();
        }

        let pp = p.next.clone();
        p.next = None;

        pp
    }

    // Usage: `pos` is started from 0.
    #[allow(dead_code)]
    pub fn remove(&mut self, pos: usize) -> Option<Box<Node>> {
        if self.0 == None {
            return None;
        }
        let mut i = 1usize;
        let mut p = &mut self.0;

        while i < pos && p.as_ref().unwrap().next.as_ref().unwrap().next != None {
            p = &mut p.as_mut().unwrap().next;
            i += 1;
        }

        if pos == 0 {
            self.pop_front()
        } else if i != pos {
            self.pop_back()
        } else {
            let pp = p.as_ref().unwrap().next.clone();
            p.as_mut().unwrap().next = pp.as_ref().unwrap().next.clone();
            pp
        }
    }

    // Usage: remove all nodes in the linkedlist
    pub fn erase(&mut self) {
        self.0 = None;
    }
}

impl std::fmt::Display for LinkedList {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut p = &self.0;
        let mut res = String::new();
        while let Some(pp) = p {
            if pp.next != None {
                res = format!("{}{}->", res, pp.value);
            } else {
                res = format!("{}{}", res, pp.value);
            }
            p = &pp.next;
        }
        write!(f, "{}", res)
    }
}

fn main() {
    let mut head = LinkedList::new();
    head.push_front(1);
    head.push_front(0);

    head.push_back(2);
    head.push_back(3);

    head.insert(4, 5);
    head.insert(4, 4);

    println!("{}", head);
    // head.pop_front();
    // println!("{}", head);
    // head.pop_back();
    // println!("{}", head);
    // head.remove(4);
    // println!("{}", head);
    // head.remove(2);
    // println!("{}", head);
    // head.remove(1);
    // println!("{}", head);
    // head.remove(0);
    // println!("{}", head);

    head.erase();
    println!("{}", head);
}
