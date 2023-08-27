fn shijie() -> &'static str {
    "shijie"
}

fn main() {
    let mut s = String::from("jiao");
    s += shijie();
    println!("{}", s);
}
