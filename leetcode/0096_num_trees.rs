struct Solution;

impl Solution {
    pub fn num_trees(n: i32) -> i32 {
        let mut mem = vec![vec![-1; n as usize + 1]; n as usize + 1];
        Solution::dfs(1, n as usize + 1, &mut mem)
    }

    pub fn dfs(left: usize, right: usize, m: &mut Vec<Vec<i32>>) -> i32 {
        if left >= right {
            return 1;
        }
        if m[left][right - 1] == -1 {
            let mut n: i32 = 0;
            for i in left..right {
                let l = Solution::dfs(left, i, m);
                let r = Solution::dfs(i + 1, right, m);
                n += l * r;
            }
            m[left][right - 1] = n;
        }
        m[left][right - 1]
    }
}

fn main() {
    println!("{}", Solution::num_trees(19));
}
