use std::collections::HashMap;

#[allow(dead_code)]
fn print_type_name<T>(_: T) {
    println!("{}", std::any::type_name::<T>());
}

trait Expr {
    fn eval(&self);
}

struct Callexpr {
    name: String,
    count: Option<usize>,
}

impl Callexpr {
    fn new(name: &str, count: Option<usize>) -> Self {
        Self {
            name: String::from(name),
            count,
        }
    }
}

impl Expr for Callexpr {
    fn eval(&self) {
        if let Some(count) = self.count {
            println!("execute {} with {}", self.name, count);
        } else {
            println!("execute {}", self.name);
        }
    }
}

struct Cmdexpr {
    name: String,
}

impl Cmdexpr {
    fn new(name: &str) -> Self {
        Self { name: String::from(name) }
    }
}

impl Expr for Cmdexpr {
    fn eval(&self) {
        println!("execute {}", self.name);
    }
}

fn main() {
    let mut exe = HashMap::<&'static str, Box<dyn Expr>>::new();
    exe.insert("j", Box::new(Callexpr::new("down", Some(1))));
    exe.insert("k", Box::new(Callexpr::new("up", Some(1))));
    exe.insert("l", Box::new(Callexpr::new("open_dir", None)));
    exe.insert("h", Box::new(Callexpr::new("up_dir", None)));
    exe.insert(":pwd", Box::new(Cmdexpr::new("pwd")));
    let e = exe.get(":pwd").unwrap();
    e.eval();
}
