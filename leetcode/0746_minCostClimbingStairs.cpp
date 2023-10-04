#include "head.hpp"

using std::vector;

class Solution {
public:
  int minCostClimbingStairs(const vector<int>& cost) {
    int arr[3] = {cost[0], cost[1], 0};
    size_t len = cost.size();
    for (size_t i = 2; i < len; ++i) {
      arr[i % 3] = std::min(arr[(i - 1) % 3], arr[(i - 2) % 3]);
      arr[i % 3] += cost[i];
    }
    return std::min(arr[(len - 1) % 3], arr[(len - 2) % 3]);
  }
};

int main() {
  Solution s;
  std::cout << s.minCostClimbingStairs(vector<int>{10, 15, 20}) << std::endl;
  std::cout << s.minCostClimbingStairs(vector<int>{1,100,1,1,1,100,1,1,100,1}) << std::endl;
  return 0;
}
