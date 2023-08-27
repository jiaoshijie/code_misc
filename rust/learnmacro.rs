macro_rules! draw_box {
    ($symbol:expr, $($position:expr),+) => {
        println!("{}", $symbol);
        $(println!("({}, {})", $position.0, $position.1);)+
    }
}

fn main() {
    draw_box!('-');
}
