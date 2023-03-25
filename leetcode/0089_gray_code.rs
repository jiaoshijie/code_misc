struct Solution;

/*
impl Solution {
    pub fn gray_code(n: i32) -> Vec<i32> {
        let mut res = vec![0];
        Solution::dfs(n, &mut res);
        res
    }

    fn check(res: &Vec<i32>, n: i32) -> bool {
        for i in res {
            if *i == n {
                return false;
            }
        }
        true
    }

    fn dfs(n: i32, res: &mut Vec<i32>) -> bool {
        if res.len() >= 1 << n {
            return true;
        }
        let num = res[res.len() - 1];
        for i in 0..n {
            let item = num ^ (1 << i);
            if Solution::check(res, item) {
                res.push(item);
                if Solution::dfs(n, res) {
                    return true;
                }
                res.pop();
            }
        }
        false
    }
}
*/


impl Solution {
    pub fn gray_code(n: i32) -> Vec<i32> {
        let mut res = Vec::new();
        let mut j = 0;
        for i in 0..(1 << n)/2 {
            res.push(j ^ i);
            j += 1;
            res.push(j ^ i);
            j += 1;
        }
        res
    }
}

fn main() {
    println!("{:?}", Solution::gray_code(1));
}
