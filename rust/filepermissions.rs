#[allow(unused_imports)]
use std::{os::unix::fs::MetadataExt, path::PathBuf};

fn main() {
    let path = PathBuf::from("/home/jsj/Downloads/sh_alias/alias");
    // let metadata = dir.metadata().unwrap();
    // println!("{:b}", metadata.mode());
    println!("{:?}", path.extension().unwrap());
}
