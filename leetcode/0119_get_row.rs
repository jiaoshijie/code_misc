struct Solution;

impl Solution {
    pub fn get_row(row_index: i32) -> Vec<i32> {
        let mut ret = vec![1; (row_index + 1) as usize];
        let mut end = row_index / 2;
        if row_index % 2 != 0 {
            end += 1;
        }
        for i in 1..end {
            let com = Solution::combination(i, row_index);
            ret[i as usize] = com;
            ret[(row_index - i) as usize] = com;
        }

        if row_index % 2 == 0 {
            ret[(row_index / 2) as usize] = Solution::combination(row_index / 2, row_index);
        }
        ret
    }

    // TODO: how to use i32 implement this function
    fn combination(ele: i32, com: i32) -> i32 {
        let (mut t1, mut t2) = (1u64, 1u64);
        let mut j = com as u64;
        for i in 1..(ele + 1) as u64 {
            if t2 % i == 0 {
                t2 /= i;
                t2 *= j;
            } else if j % i == 0 {
                let t = j / i;
                t2 *= t;
            } else {
                t2 *= j;
                t1 *= i;
            }
            j -= 1;
        }
        (t2 / t1) as i32
    }
}

fn main() {
    println!("{:?}", Solution::get_row(33));
}
