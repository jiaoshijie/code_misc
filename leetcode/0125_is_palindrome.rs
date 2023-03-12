struct Solution;

impl Solution {
    pub fn is_palindrome(s: String) -> bool {
        let (mut l, mut r) = (0, s.len());
        while l < r {
            r -= 1;
            while l < s.len() && !Solution::check(s.as_bytes()[l]) {
                l += 1;
            }
            while l < r && !Solution::check(s.as_bytes()[r]) {
                r -= 1;
            }
            if l < r && s.as_bytes()[l].to_ascii_lowercase() != s.as_bytes()[r].to_ascii_lowercase() {
                return false;
            }
            l += 1;
        }
        true
    }

    fn check(b: u8) -> bool {
        if (b >= 48 && b <= 57) || (b >= 65 && b <= 90) || (b >= 97 && b <= 122) {
            true
        } else {
            false
        }
    }
}

fn main() {
    println!("{}", Solution::is_palindrome(String::from("a.b")));
}
