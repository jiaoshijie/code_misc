use std::{os::unix::fs::MetadataExt, path::PathBuf, time::SystemTime};

fn main() {
    let dir_path = PathBuf::from("/home/jsj/Downloads/sourceCode/forlf/lfr/Cargo.toml");
    let current_time: SystemTime = SystemTime::now();
    println!("system time: {:?}", current_time);
    println!(
        "system time: {:?}",
        current_time
            .duration_since(SystemTime::UNIX_EPOCH)
            .unwrap()
            .as_secs()
    );
    let metadata = dir_path.metadata().unwrap();
    println!("access time: {:?}", metadata.atime());
    println!("modify time: {:?}", metadata.mtime());
    println!("file size: {}", size(metadata.size()));
    println!("file mode: {}", mode(metadata.mode()));
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

fn mode(m: u32) -> String {
    let mut ret = String::new();
    let mut mask = 0x100;
    while mask != 0 {
        if mask & m != 0 {
            ret += "r";
        } else {
            ret += "-"
        }
        mask >>= 1;
        if mask & m != 0 {
            ret += "w";
        } else {
            ret += "-"
        }
        mask >>= 1;
        if mask & m != 0 {
            ret += "x";
        } else {
            ret += "-"
        }
        mask >>= 1;
    }
    ret
}
