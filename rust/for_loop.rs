fn main() {
    let mut update: Vec<(usize, usize, char)> = vec![];
    update.push((1, 1, 'a'));
    update.push((2, 2, 'b'));

    for t in update {
        println!("({}, {}): {}", t.0, t.1, t.2);
    }
}
