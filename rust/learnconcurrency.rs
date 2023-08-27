use std::{
    sync::{Arc, Mutex},
    thread,
};

#[allow(dead_code)]
#[derive(Debug)]
struct Dir {
    id: i32,
    files: Vec<i32>,
    loaded: bool,
}

impl Dir {
    fn new(id: i32) -> Self {
        Self {
            id,
            files: vec![id * 2, id * 3, id * 4],
            loaded: false,
        }
    }
}

#[allow(dead_code)]
#[derive(Debug)]
struct Nav {
    dir: Arc<Mutex<Dir>>,
}

impl Nav {
    fn new() -> Self {
        Self {
            dir: Arc::new(Mutex::new(Dir::new(0))),
        }
    }
}

fn main() {
    let nav = Nav::new();
    let counter = Arc::clone(&nav.dir);
    let th = thread::spawn(move || {
        if let Ok(mut lock) = counter.lock() {
            lock.loaded = true;
        }
    });
    th.join();
    loop {
        if let lock = nav.dir.lock().unwrap() {
            println!("{:?}", lock);
            break;
        }
    }
}
