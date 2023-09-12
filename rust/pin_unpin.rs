// https://www.reddit.com/r/rust/comments/159akpu/ive_spent_time_to_actually_understand_pin_and/
// https://cryptical.xyz/rust/pin-unpin
use std::pin::Pin;
use std::marker::PhantomPinned;  // this helps us to make our data `!Unpin`

#[derive(Debug)]
struct Test {
    string: String,
    ref_string: *const String,
    _marker: PhantomPinned, // we need this to make our type `!Unpin`
}

impl Test {
    fn new(txt: &str) -> Self {
        Test {
            string: String::from(txt),
            ref_string: std::ptr::null(),
            _marker: PhantomPinned, // This makes our type `!Unpin`
        }
    }

    fn init(&mut self) {
        self.ref_string = &self.string;
    }
}

fn print_test_struct(test: &Test, label: &str) {
    println!(
        "{label}.string = value: {},            --- address:{:p}",
        test.string, &test.string
    );
    unsafe {
        println!(
            "{label}.ref_string = value: {:?},  --- address:{:p}, --- deref to: {}",
            test.ref_string,
            &test.ref_string,
            *test.ref_string
        );
    }
}

fn main() {
/* "Self-referential - SWAP PROBLEM - values will be inconsistent" */

    let mut a = Test::new("a");
    a.init();
    let mut b = Test::new("b");
    b.init();

    println!("# initial values:");
    println!();
    print_test_struct(&a, "a");
    println!();
    print_test_struct(&b, "b");

    println!("\n-----------------------\n");

   // CHECKPOINT START
    let mut a = unsafe { Pin::new_unchecked(&mut a) };
    let mut b = unsafe { Pin::new_unchecked(&mut b) };

		/* Let's swap */
    std::mem::swap(&mut a, &mut b);
    // CHECKPOINT END

    println!("# values after swap:\n");

    print_test_struct(&a, "a");
    println!();
    print_test_struct(&b, "b");
}

