struct Solution;

impl Solution {
    #[allow(dead_code)]
    pub fn max_vowels_directively(s: String, k: i32) -> i32 {
        let mut ret = 0;
        let mut temp = 0;
        let vowels = vec!['a', 'e', 'i', 'o', 'u'];
        for i in 0..s.len() - k as usize + 1 {
            for j in i..k as usize + i {
                if vowels.contains(&(s.as_bytes()[j] as char)) {
                    temp += 1;
                }
                if ret < temp {
                    ret = temp;
                }
            }
            if temp == k {
                break;
            }
            temp = 0;
        }
        ret
    }

    pub fn max_vowels(s: String, k: i32) -> i32 {
        let (mut ret, mut temp) = (0, 0);
        let vowels = vec!['a', 'e', 'i', 'o', 'u'];
        for i in 0..k as usize {
            if vowels.contains(&(s.as_bytes()[i] as char)) {
                temp += 1;
            }
        }
        ret = temp;
        for i in (k as usize)..s.len() {
            if vowels.contains(&(s.as_bytes()[i] as char)) {
                temp += 1;
            }

            if vowels.contains(&(s.as_bytes()[i - k as usize] as char)) {
                temp -= 1;
            }

            if ret < temp {
                ret = temp;
            }
        }
        ret
    }
}

fn main() {
    println!("{}", Solution::max_vowels(String::from("abciiidef"), 3));
}
