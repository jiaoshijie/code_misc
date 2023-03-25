struct Solution;

/*
use std::collections::HashMap;
impl Solution {
    pub fn is_scramble(s1: String, s2: String) -> bool {
        if s1 == s2 {
            return true;
        }
        let mut hash = HashMap::new();
        for i in 1..s1.len() {
            let res = Solution::dfs(&s1[0..i], &s1[i..s1.len()], &mut hash);
            for i in res {
                if i == s2 {
                    return true;
                }
            }
        }
        false
    }

    fn dfs(p: &str, q: &str, hash: &mut HashMap<String, Vec<String>>) -> Vec<String> {
        let mut res = Vec::new();
        let (mut pp, mut qq) = (Vec::new(), Vec::new());
        match hash.get_key_value(p) {
            Some((_, v)) => {
                pp = v.to_vec();
            },
            None => {
                if p.len() == 1 {
                    pp.push(format!("{}", p));
                }
                for i in 1..p.len() {
                    let ppp = Solution::dfs(&p[0..i], &p[i..p.len()], hash);
                    for i in ppp {
                        pp.push(i);
                    }
                }
                hash.insert(p.to_string(), pp.clone());
            }
        }
        match hash.get_key_value(q) {
            Some((_, v)) => {
                qq = v.to_vec();
            },
            None => {
                if q.len() == 1 {
                    qq.push(format!("{}", q));
                }
                for i in 1..q.len() {
                    let qqq = Solution::dfs(&q[0..i], &q[i..q.len()], hash);
                    for i in qqq {
                        qq.push(i);
                    }
                }
                hash.insert(q.to_string(), qq.clone());
            }
        }
        for i in 0..pp.len() {
            for j in 0..qq.len() {
                res.push(format!("{}{}", pp[i], qq[j]));
                res.push(format!("{}{}", qq[j], pp[i]));
            }
        }
        // println!("p:{}, q:{}, res: {:?}", p, q, res);
        res
    }
}
*/

impl Solution {
    pub fn is_scramble(s1: String, s2: String) -> bool {
        let len = s1.len();
        let mut dp = vec![vec![vec![0; 31]; 30]; 30];
        Solution::dfs(&s1, &s2, &mut dp, 0, 0, len)
    }

    fn check(s1: &str, s2: &str, i1: usize, i2: usize, len: usize) -> bool {
        let mut flag = vec![0; 26];

        for i in i1..(i1 + len) {
            flag[(s1.as_bytes()[i] - 97) as usize] += 1;
        }

        for i in i2..(i2 + len) {
            flag[(s2.as_bytes()[i] - 97) as usize] -= 1;
        }

        for i in flag {
            if i != 0 {
                return false;
            }
        }
        true
    }

    fn dfs(s1: &str, s2: &str, dp: &mut Vec<Vec<Vec<i32>>>, i1: usize, i2: usize, len: usize) -> bool {
        // println!("{} {} {}", i1, i2, len);
        if dp[i1][i2][len] != 0 {
            return dp[i1][i2][len] == 1;
        }

        if s1[i1..(i1 + len)] == s2[i2..(i2 + len)] {
            dp[i1][i2][len] = 1;
            return true;
        }

        if !Solution::check(s1, s2, i1, i2, len) {
            dp[i1][i2][len] = -1;
            return false;
        }

        for i in 1..len {
            if Solution::dfs(s1, s2, dp, i1, i2, i) && Solution::dfs(s1, s2, dp, i1 + i, i2 + i, len - i) {
                dp[i1][i2][len] = 1;
                return true;
            }
            if Solution::dfs(s1, s2, dp, i1, i2 + len - i, i) && Solution::dfs(s1, s2, dp, i1 + i, i2, len - i) {
                dp[i1][i2][len] = 1;
                return true;
            }
        }
        dp[i1][i2][len] = -1;
        false
    }
}

fn main() {

    assert_eq!(Solution::is_scramble(String::from("great"), String::from("rgeat")), true);
    assert_eq!(Solution::is_scramble(String::from("abcde"), String::from("caebd")), false);
    assert_eq!(Solution::is_scramble(String::from("a"), String::from("a")), true);
    assert_eq!(Solution::is_scramble(String::from("abc"), String::from("acb")), true);
    assert_eq!(Solution::is_scramble(String::from("abcd"), String::from("acbd")), true);
    assert_eq!(Solution::is_scramble(String::from("abc"), String::from("cba")), true);
    assert_eq!(Solution::is_scramble(String::from("abcd"), String::from("badc")), true);
    assert_eq!(Solution::is_scramble(String::from("abcde"), String::from("caebd")), false);

    assert_eq!(Solution::is_scramble(String::from("abcdbdacbdac"), String::from("bdacabcdbdac")), true);
}
