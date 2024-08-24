#![no_std]

// extern crate alloc;
// extern crate dlmalloc;

use core::panic::PanicInfo;
// use alloc::string::String;
// use dlmalloc::GlobalDlmalloc;

// #[global_allocator]
// static ALLOCATOR: GlobalDlmalloc = GlobalDlmalloc;

#[panic_handler]
fn panic(_panic: &PanicInfo<'_>) -> ! {
    core::arch::wasm32::unreachable()
}

mod math {
    mod math_js {
        #[link(wasm_import_module = "Math")]
        extern "C" {
            pub fn random() -> f64;
        }
    }

    pub fn random() -> f64 {
        unsafe { math_js::random() }
    }
}

#[allow(non_snake_case)]
mod IO {
    mod IO_js {
        #[link(wasm_import_module = "IO")]
        extern "C" {
            pub fn print(msg: *const u8, len: u32);
        }
    }

    pub fn print(s: &str) {
        unsafe {
            IO_js::print(s.as_ptr(), s.len() as u32);
        }
    }
}


// #[no_mangle]
#[export_name = "add_one_random"]
pub extern "C" fn add_one_random(x: f64) -> f64 {
    x + 1f64 + math::random()
}

#[export_name = "greeting"]
pub extern "C" fn greeting() {
    // let s = String::from("hello wasm!!!");
    // IO::print(&s);
    IO::print("hello wasm!!!");
}
