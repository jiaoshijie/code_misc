#[allow(unused_imports)]
use std::{fs::read_link, os::unix::fs::MetadataExt, path::PathBuf};

fn main() {
    let path = PathBuf::from("/home/jsj/file");
    let metadata = path.symlink_metadata().unwrap();
    println!("{}", size(metadata.size()));
    // if metadata.is_symlink() {
    //     println!("{}", size(metadata.size()));
    // }
    // let metadata = path.metadata().unwrap();
    // if let Ok(matadata) = path.metadata() {
    //     println!("{}", size(metadata.size()));
    // } else {
    //     println!("target file has not existed.")
    // }
    // println!("{:?}", read_link(path).unwrap());
}

fn carry(dividend: u64, divisor: u64) -> f64 {
    if dividend % divisor != 0 {
        0.1
    } else {
        0.0
    }
}

fn size(s: u64) -> String {
    if s < 1024 {
        format!("{}B", s)
    } else if s < 1024 * 1024 {
        format!("{:.1}K", s as f64 / 1024.0 + carry(s, 1024))
    } else if s < 1024 * 1024 * 1024 {
        let divisor = 1024 * 1024;
        format!("{:.1}M", s as f64 / divisor as f64 + carry(s, divisor))
    } else {
        let divisor = 1024 * 1024 * 1024;
        format!("{:.1}G", s as f64 / divisor as f64 + carry(s, divisor))
    }
}
