#include "head.hpp"

class Solution {
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int len = nums1.size() + nums2.size();
    if (len == 1) {
      return nums1.size() ? nums1[0] : nums2[0];
    }
    int index = len / 2, j = 2, n1 = 0, n2 = 0;
    int arr[2] = {0, 0};
    for (int i = 0; i <= index; i++) {
      j = j % 2;
      if (n1 < (int)nums1.size() && n2 < (int)nums2.size()) {
        arr[j++] = nums1[n1] < nums2[n2] ? nums1[n1++] : nums2[n2++];
      } else if (n1 < (int)nums1.size()) {
        arr[j++] = nums1[n1++];
      } else if (n2 < (int)nums2.size()) {
        arr[j++] = nums2[n2++];
      }
    }
    return len % 2 ? (arr[0] > arr[1] ? arr[0] : arr[1]) : (arr[0] + arr[1]) / 2.0;
  }
};

int main() {
  Solution s;
  std::vector<int> v1, v2({1, 2, 3, 4, 5});
  std::cout << s.findMedianSortedArrays(v1, v2) << std::endl;
  return 0;
}
