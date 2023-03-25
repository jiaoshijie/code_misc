struct Solution;

impl Solution {
    /* NOTE: wrong
    pub fn subsets_with_dup(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut res = vec![vec![]];
        let mut last = -11;
        let mut nums = nums;
        nums.sort();
        for i in 0..nums.len() {
            if last != nums[i] {
                res.push(vec![nums[i]]);
            }
            let mut t = vec![nums[i]];
            for j in (i + 1)..nums.len() {
                t.push(nums[j]);
                if last != nums[j] {
                    res.push(t.clone());
                }
            }
            last = nums[i];
        }
        res
    }
    */
    pub fn subsets_with_dup(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut res = vec![];
        let mut nums = nums;
        let mut t = vec![];
        nums.sort();
        Solution::dfs(&nums, 0, &mut res, &mut t, true);
        res
    }

    fn dfs(nums: &Vec<i32>, index: usize, res: &mut Vec<Vec<i32>>, t: &mut Vec<i32>, flag: bool) {
        if index >= nums.len() {
            res.push(t.clone());
            return;
        }

        t.push(nums[index]);
        Solution::dfs(nums, index + 1, res, t, true);
        t.pop();
        if !(index > 0 && nums[index] == nums[index - 1] && flag) {
            Solution::dfs(nums, index + 1, res, t, false);
        }
    }
}

fn main() {
    println!("{:?}", Solution::subsets_with_dup(vec![1, 2, 3]));
}
