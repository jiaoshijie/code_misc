struct Solution;

impl Solution {
    // overtime
    pub fn max_profit_1(prices: Vec<i32>) -> i32 {
        let mut ret = 0;
        for i in 0..prices.len() {
            for j in (i + 1)..prices.len() {
                ret = std::cmp::max(ret, prices[j] - prices[i]);
            }
        }
        ret
    }
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let (mut min, mut ret) = (prices[0], 0);
        for ele in prices {
            if min > ele {
                min = ele;
            }
            ret = std::cmp::max(ret, ele - min);
        }
        ret
    }
}

fn main() {
    println!("{}", Solution::max_profit(vec![1, 2]));
}
