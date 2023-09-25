#include "head.hpp"

using std::vector;

class Solution {
public:
  void insert_item(vector<int>& heap, int item) {
    heap.push_back(item);
    size_t c = heap.size() - 1;
    size_t p = (c - 1) / 2;
    while (c != 0) {
      if (heap[c] > heap[p]) {
        std::swap(heap[c], heap[p]);
      }
      c = p;
      p = (c - 1) / 2;
    }
  }
  void delete_max_item(vector<int>& heap) {
    if (heap.size() > 1) {
      heap[0] = heap.back();
      heap.pop_back();
      size_t p = 0;
      size_t c1 = 1;
      size_t c2 = 2;
      while (c1 < heap.size()) {
        size_t i = c2 < heap.size() && heap[c1] < heap[c2] ? c2 : c1;
        if (heap[i] > heap[p]) {
          std::swap(heap[i], heap[p]);
          p = i;
          c1 = 2 * p + 1;
          c2 = 2 * p + 2;
        } else {
          break;
        }
      }
    }

  }


  int findKthLargest(vector<int>& nums, int k) {
    vector<int> heap;
    heap.reserve(nums.size());
    for (auto i : nums) {
      insert_item(heap, i);
    }
    for (int i = 0; i < k - 1; ++i) {
      delete_max_item(heap);
    }
    return heap.front();
  }
};

int main() {
  Solution s;
  vector<int> a{3,2,3,1,2,4,5,5,6};
  std::cout << s.findKthLargest(a, 4) << std::endl;
  return 0;
}
