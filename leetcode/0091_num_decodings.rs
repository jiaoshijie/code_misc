struct Solution;

impl Solution {
    pub fn num_decodings(s: String) -> i32 {
        let mut dp = vec![-1; s.len()];
        Solution::dfs(&s, 0, &mut dp)
    }

    fn dfs(s: &str, index: usize, dp: &mut Vec<i32>) -> i32 {
        if index >= s.len() {
            return 1;
        }

        if dp[index] != -1 {
            return dp[index];
        }

        let first = s.as_bytes()[index] - 48;
        if first == 0 {
            dp[index] = 0;
            return dp[index];
        }
        dp[index] = Solution::dfs(s, index + 1, dp);

        if index < s.len() - 1 {
            let second = s.as_bytes()[index + 1] - 48;
            if first * 10 + second <= 26 {
                dp[index] += Solution::dfs(s, index + 2, dp);
            }
        }
        dp[index]
    }
}

fn main() {
    println!("{}", Solution::num_decodings(String::from("111111111111111111111111111111111111111111111")));
}
