#[derive(Debug)]
struct MyS {
    pub f: usize,
}

#[derive(Debug)]
struct MyBox {
    pub b: Box<MyS>,
}

fn main() {
    let s: Box<MyS>;
    {
        let mut x = MyBox { b: Box::new(MyS { f: 12usize }) };
        println!("x = {x:?}");
        let ptr = Box::into_raw(x.b);
        println!("{ptr:?}");
        x.b = unsafe { Box::from_raw(ptr) };
        s = x.b;
    }
    println!("s = {s:?}");
    let ptr = Box::into_raw(s);
    println!("{ptr:?}");
}
