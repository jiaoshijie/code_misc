struct Solution;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut mask = 0i32;
        for i in nums {
            mask ^= i;
        }
        mask
    }
}

fn main() {
    println!("{}", Solution::single_number(vec![2,2,1]));
}
