use std::{
    collections::HashMap,
    env,
    path::{Path, PathBuf},
};

#[allow(dead_code)]
#[derive(Debug)]
struct Dir {
    id: i32,
    files: Vec<i32>,
}

#[derive(Debug)]
struct Nav {
    cache: HashMap<PathBuf, Dir>,
}

impl Dir {
    fn new(index: i32) -> Self {
        let files = vec![index * 2, index * 3, index * 4];
        Self { id: index, files }
    }
}

impl Nav {
    fn new() -> Self {
        Self {
            cache: HashMap::new(),
        }
    }
}

fn main() {
    let mut index: i32 = 1;

    let mut n = Nav::new();

    let binding = env::current_dir().unwrap();
    let mut path = Path::new(binding.to_str().unwrap());
    n.cache.insert(path.to_path_buf(), Dir::new(index));
    loop {
        match path.parent() {
            Some(d) => {
                path = d;
                index += 1;
                n.cache.insert(path.to_path_buf(), Dir::new(index));
            }
            None => break,
        }
    }

    println!("{:?}", n.cache.get(Path::new("/")).unwrap());
}
