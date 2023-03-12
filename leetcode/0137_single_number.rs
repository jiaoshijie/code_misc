struct Solution;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut ret = 0;
        for i in 0..32 {
            let mut count = 0;
            for ele in &nums {
                if ele & (1 << i) != 0 {
                    count += 1;
                }
            }
            if count % 3 != 0 {
                ret |= 1 << i;
            }
        }
        ret
    }
}

fn main() {
    println!("{:?}", Solution::single_number(vec![2,2,3,2]));
}
