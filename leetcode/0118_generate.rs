struct Solution;

impl Solution {
    pub fn generate(num_rows: i32) -> Vec<Vec<i32>> {
        let mut ret = vec![vec![1i32]];
        for i in 1..(num_rows as usize) {
            let mut temp = vec![1];
            for j in 1..i {
                temp.push(ret[i - 1][j - 1] + ret[i - 1][j]);
            }
            temp.push(1);
            ret.push(temp);
        }
        ret
    }
}

fn main() {
    println!("{:?}", Solution::generate(30));
}
