struct Solution;

// NOTE: 或者从大的元素开始放(从后往前放)
impl Solution {
    pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
        if n == 0 {
            return;
        }
        for i in 1..=(m as usize) {
            nums1[(m + n) as usize - i] = nums1[m as usize - i];
        }
        let (mut i, mut j, mut k) = (0usize, 0usize, 0usize);
        while i < (m as usize) && j < (n as usize) {
            if nums1[n as usize + i] <= nums2[j] {
                nums1[k] = nums1[n as usize + i];
                i += 1;
            } else {
                nums1[k] = nums2[j];
                j += 1;
            }
            k += 1;
        }
        while j < (n as usize) {
            nums1[k] = nums2[j];
            j += 1;
            k += 1;
        }
    }
}

fn main() {
    let mut nums1 = vec![1, 2, 3, 0, 0, 0];
    let mut nums2 = vec![2, 5, 6];
    let (m, n) = (3, 3);
    Solution::merge(&mut nums1, m, &mut nums2, n);
    println!("{:?}", nums1);
}
