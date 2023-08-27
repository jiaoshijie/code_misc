#[allow(dead_code)]
struct Dir {
    fs: usize,
    all_files: Vec<String>,
}

#[allow(dead_code)]
impl Dir {
    fn new() -> Self {
        let mut ret = Dir {
            fs: 3,
            all_files: Vec::with_capacity(4),
        };

        ret.all_files.push(String::from("jiao"));
        ret.all_files.push(String::from("shi"));
        ret.all_files.push(String::from("jie"));

        ret
    }

    fn files(&self) -> Option<&[String]> {
        if self.fs < self.all_files.len() {
            Some(&self.all_files[self.fs..])
        } else {
            None
        }
    }

    fn push(&mut self, name: &str) {
        self.all_files.push(String::from(name));
    }
}

fn main() {
    let mut new_dir = Dir::new();
    new_dir.push("new_element");
    if let Some(files) = new_dir.files() {
        println!("{:?}", files)
    }
}
