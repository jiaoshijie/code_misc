// https://github.com/rust-lang/rust/issues/25860

fn main() {
    let a: &Vec<i32>;
    {
        let b = vec![3, 2, 1];
        a = extend(&b);
    }
    println!("{:?}", a);
}

fn weird<'a, 'b, T>(_: &'a &'b (), borrow: &'b T) -> &'a T {
    borrow
}

static FOREVER: &'static &'static () = &&();

fn extend<'a, 'b, T>(borrow: &'a T) -> &'b T {
    let local_weird: fn(&'static &'static (), &'a T) -> &'b T = weird;
    local_weird(FOREVER, borrow)
}
