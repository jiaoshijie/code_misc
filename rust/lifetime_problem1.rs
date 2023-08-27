struct Dir<'a> {
    files: Option<&'a [String]>,
    all_files: Vec<String>,
}

#[allow(dead_code)]
impl<'a> Dir<'a> {
    fn new() -> Self {
        let mut ret = Dir {
            files: None,
            all_files: Vec::new(),
        };

        ret.all_files.push(String::from("jiao"));
        ret.all_files.push(String::from("shi"));
        ret.all_files.push(String::from("jie"));

        ret
    }

    fn sort(&'a mut self) -> &Dir<'a> {
        let target_index = 2;
        if target_index < self.all_files.len() {
            self.files = Some(&self.all_files[target_index..]);
        }
        self
    }

    fn push(&mut self, name: &str) {
        self.all_files.push(String::from(name));
    }
}

fn main() {
    let mut new_dir: Dir = Dir::new();
    let dir = new_dir.sort();
    if let Some(i) = dir.files {
        println!("{:?}", i);
    }
}
