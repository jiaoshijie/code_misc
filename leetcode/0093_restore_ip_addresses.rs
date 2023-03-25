struct Solution;

impl Solution {
    pub fn restore_ip_addresses(s: String) -> Vec<String> {
        let mut res = Vec::new();
        let mut ip = Vec::new();
        Solution::dfs(&s, 0, &mut ip, &mut res);
        res
    }

    fn dfs(s: &str, index: usize, ip: &mut Vec<String>, res: &mut Vec<String>) {
        if index >= s.len() && ip.len() >= 4 {
            res.push(ip.join("."));
            return;
        }

        if ip.len() >= 4 {
            return;
        }

        let mut num = String::new();
        for i in index..(index + 3) {
            if i < s.len() {
                num.push(s.as_bytes()[i] as char);
                if num.parse::<i32>().unwrap() > 255 {
                    break;
                }
                ip.push(num.clone());
                Solution::dfs(s, i + 1, ip, res);
                ip.pop();
                if num.as_bytes()[0] == 48u8 {
                    break;
                }
            }
        }
    }
}

fn main() {
    println!("{:?}", Solution::restore_ip_addresses(String::from("0000")))
}
