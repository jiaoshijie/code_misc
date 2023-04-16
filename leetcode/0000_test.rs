#[allow(dead_code)]
fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn main() {
    let a = Some(1);
    let b = Some(2);

    match (a, b) {
        (aa, bb) => {
            print_type_of(&aa);
            print_type_of(&bb);
        },
        (_, _) => {}
    }
}
