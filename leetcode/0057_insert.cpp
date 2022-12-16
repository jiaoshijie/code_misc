#include "head.hpp"

using std::vector;

class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> output;
    int i = 0, intervals_size = (int)intervals.size();
    while(i < intervals_size) {
      if (intervals[i][1] < newInterval[0]) output.push_back(intervals[i]);
      else break;
      i++;
    }
    if (i < intervals_size && newInterval[0] > intervals[i][0]) newInterval[0] = intervals[i][0];
    while(i < intervals_size) {
      if (intervals[i][0] > newInterval[1]) break;
      i++;
    }
    if (i - 1 >= 0 && i - 1 < intervals_size && newInterval[1] < intervals[i - 1][1]) newInterval[1] = intervals[i - 1][1];
    output.push_back(newInterval);
    while(i < intervals_size) {
      output.push_back(intervals[i++]);
    }
    return output;
  }
};

int main() {
  vector<vector<int>> in;
  vector<int> newI = {0, 0};
  in.push_back(vector<int>{1, 5});
  Solution s;
  vector<vector<int>> out = s.insert(in, newI);
  return 0;
}
