#include "head.hpp"

using std::vector;

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> output;
    bool *flag = new bool[20001]{0};
    for (size_t i = 0; i < intervals.size(); i++) {
      int offset = intervals[i][0] * 2 + 1, len;
      if (intervals[i][0] != intervals[i][1]) {
        len = intervals[i][1] * 2 - offset + 1;
      } else {
        len = 1;
      }
      memset(flag + offset, true,  len);
    }
    size_t index = 0;
    while(index < 20001) {
      vector<int> temp;
      while(index < 20001 && !flag[index]) index++;
      if (index < 20001) temp.push_back(index / 2);
      while(index < 20001 && flag[index]) index++;
      if (index < 20001) {
        temp.push_back((index - 1) / 2);
        output.push_back(temp);
      }
    }
    return output;
  }
};

int main() {
  vector<vector<int>> intervals = {{1,4},{0,0}};
  Solution s;
  vector<vector<int>> res = s.merge(intervals);
  return 0;
}
