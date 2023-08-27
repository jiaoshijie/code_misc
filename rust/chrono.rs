use std::{os::unix::fs::MetadataExt, path::PathBuf, time::{Duration, UNIX_EPOCH}};
use chrono::{prelude::DateTime, Local};

fn main() {
    let file = PathBuf::from("/home/jsj/main.txt");
    let access_time = UNIX_EPOCH + Duration::from_secs(file.metadata().unwrap().atime() as u64);
    let datetime = DateTime::<Local>::from(access_time);
    println!("{}", datetime.format("%a %d/%m/%Y %X"))
}
