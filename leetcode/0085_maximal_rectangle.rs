struct Solution;

impl Solution {
    pub fn maximal_rectangle(matrix: Vec<Vec<char>>) -> i32 {
        let mut ret = 0i32;
        let mut matrix_i32 = Vec::new();
        for i in 0..matrix.len() {
            let mut temp = Vec::new();
            for j in 0..matrix[0].len() {
                temp.push(matrix[i][j].to_digit(10).unwrap());
            }
            matrix_i32.push(temp);
        }

        let mut row = vec![0; matrix[0].len() + 1];
        for i in 0..matrix_i32.len() {
            for j in 0..row.len() - 1 {
                row[j] = matrix_i32[i][j];
                if row[j] != 0 {
                    for x in (0..i).rev() {
                        if matrix_i32[x][j] == 0 {
                            break;
                        }
                        row[j] += matrix_i32[x][j];
                    }
                }
            }
            println!("{:?}", row);
            let mut stack = Vec::new();
            let mut t = 0i32;
            for j in 0..row.len() {
                if stack.is_empty() || row[j] > row[stack[stack.len() - 1]] {
                    stack.push(j);
                } else {
                    while !stack.is_empty() && row[stack[stack.len() - 1]] > row[j] {
                        let last = stack.pop().unwrap();
                        if !stack.is_empty() {
                            t = std::cmp::max(t, (row[last] * (j - stack[stack.len() - 1] - 1) as u32) as i32);
                        } else {
                            t = std::cmp::max(t, (row[last] * j as u32) as i32);
                        }
                    }
                    stack.push(j);
                }
            }
            if ret < t {
                ret = t;
            }
        }
        ret
    }
}

fn main() {
    let matrix = vec![
        vec!['1','0','0','0','1'],
        vec!['1','1','0','1','1'],
        vec!['1','1','1','1','1'],
    ];
    println!("{}", Solution::maximal_rectangle(matrix));
}
