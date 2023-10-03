struct Solution;

impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        if s1.len() + s2.len() != s3.len() {
            return false;
        }
        if s1.is_empty() && s2.is_empty() && s3.is_empty() {
            return true;
        }
        if !s1.is_empty()
            && s1.as_bytes()[0] == s3.as_bytes()[0]
            && Solution::dfs(&s1, &s2, &s3, 0, 0, 0)
        {
            return true;
        }
        if !s2.is_empty()
            && s2.as_bytes()[0] == s3.as_bytes()[0]
            && Solution::dfs(&s2, &s1, &s3, 0, 0, 0)
        {
            return true;
        }
        false
    }

    fn dfs(s1: &str, s2: &str, s3: &str, s1i: usize, s2i: usize, s3i: usize) -> bool {
        if s3i >= s3.len() {
            if s1i >= s1.len() && s2i >= s2.len() {
                return true;
            } else {
                return false;
            }
        }
        if s1i >= s1.len() || s1.as_bytes()[s1i] != s3.as_bytes()[s3i] {
            return false;
        }
        let mut s1_i = s1i;
        let mut s3_i = s3i;
        while s1_i < s1.len() && s3_i < s3.len() && s1.as_bytes()[s1_i] == s3.as_bytes()[s3_i] {
            s1_i += 1;
            s3_i += 1;
            // if (s2i >= s2.len() && s3_i >= s3.len()) || (s2i < s2.len() && s3_i < s3.len() && s2.as_bytes()[s2i] == s3.as_bytes()[s3_i]) {
            //     if Solution::dfs(s2, s1, s3, s2i, s1_i, s3_i) {
            //         return true;
            //     }
            // }
        }
        while s1_i > s1i && s3_i > s3i {
            println!("{}", s1_i);
            if Solution::dfs(s2, s1, s3, s2i, s1_i, s3_i) {
                return true;
            }
            s1_i -= 1;
            s3_i -= 1;
        }
        false
    }
}

fn main() {
    assert_eq!(
        Solution::is_interleave(
            String::from("aabcc"),
            String::from("dbbca"),
            String::from("aadbbcbcac")
        ),
        true
    );
    assert_eq!(
        Solution::is_interleave(
            String::from("aabcc"),
            String::from("dbbca"),
            String::from("aadbbbaccc")
        ),
        false
    );
    assert_eq!(
        Solution::is_interleave(String::from(""), String::from(""), String::from("")),
        true
    );
    assert_eq!(
        Solution::is_interleave(String::from("a"), String::from("b"), String::from("a")),
        false
    );
    assert_eq!(
        Solution::is_interleave(
            String::from("aabcc"),
            String::from("dbbca"),
            String::from("aadbcbbcac")
        ),
        true
    );
    assert_eq!(Solution::is_interleave(String::from("abababababababababababababababababababababababababababababababababababababababababababababababababbb"), String::from("babababababababababababababababababababababababababababababababababababababababababababababababaaaba"), String::from("abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababbb")), true);
}
