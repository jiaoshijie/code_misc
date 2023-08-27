use std::{
    cell::RefCell,
    collections::HashMap,
    path::{Path, PathBuf},
    rc::Rc,
};

#[allow(dead_code)]
#[derive(Debug)]
struct Dir {
    id: i32,
    files: Vec<i32>,
}

#[allow(dead_code)]
#[derive(Debug)]
struct Nav {
    dirs: Vec<Rc<RefCell<Dir>>>,
    cache: HashMap<PathBuf, Rc<RefCell<Dir>>>,
}

impl Dir {
    fn new(id: i32) -> Self {
        Self {
            id,
            files: vec![id * 2, id * 3, id * 4],
        }
    }
}

impl Nav {
    fn new() -> Self {
        Self {
            dirs: Vec::new(),
            cache: HashMap::new(),
        }
    }

    fn get_dir(&mut self, path: &Path, id: i32) {
        if !self.cache.contains_key(path) {
            self.cache
                .insert(path.to_path_buf(), Rc::new(RefCell::new(Dir::new(id))));
        }
        self.dirs.push(self.cache.get(path).unwrap().clone());
    }
}

fn main() {
    let mut nav = Nav::new();
    nav.get_dir(&Path::new("/home/red/"), 1);
    nav.dirs[0].borrow_mut().id = 10;
    println!("{:?}", nav.dirs);
}
