use std::sync::mpsc::{self, Sender, Receiver};
use std::{thread, time};

fn main() {
    let two_sec = time::Duration::from_secs(2);
    let five_sec = time::Duration::from_secs(5);
    let ten_sec = time::Duration::from_secs(10);

    let (tx_int, rx_int): (Sender<i32>, Receiver<i32>) = mpsc::channel();
    let (tx_str, rx_str): (Sender<String>, Receiver<String>) = mpsc::channel();
    let child_int = thread::spawn(move || {
        thread::sleep(five_sec);
        tx_int.send(10).unwrap();
        println!("Child_int has finished!!!");
    });

    let tx_str_1 = tx_str.clone();
    let child_str_1 = thread::spawn(move || {
        tx_str_1.send(String::from("child str 1")).unwrap();
        thread::sleep(ten_sec);
        println!("Child_str_1 has finished!!!");
    });

    let child_str_2 = thread::spawn(move || {
        thread::sleep(two_sec);
        tx_str.send(String::from("child str 2")).unwrap();
        println!("Child_str_2 has finished!!!");
    });

    let mut count: u32 = 0;

    // TODO: write a micro to make match code block smaller
    while count < 3 {
        match rx_int.try_recv() {
            Ok(i) => {
                count += 1;
                println!("the recive int = {}", i);
            },
            Err(_) => {},
        };
        match rx_str.try_recv() {
            Ok(str) => {
                count += 1;
                println!("the recive str = {}", str);
            },
            Err(_) => {},
        };
    }



    child_int.join().unwrap();
    child_str_1.join().unwrap();
    child_str_2.join().unwrap();
}
