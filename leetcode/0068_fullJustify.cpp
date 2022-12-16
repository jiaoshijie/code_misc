#include "head.hpp"

using std::vector;
using std::string;

class Solution {
public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> res;
    int len = words.size();
    int i = 0, p = 0, word_len = 0;
    while (i < len) {
      if (word_len + (i - p - 1) + int(words[i].size()) < maxWidth) {
        word_len += words[i].size();
        i++;
      } else {
        int will_i = i - p - 1;  // will insert
        int left = maxWidth - word_len - will_i;
        string t = "";
        if (will_i) {
          int alway_i = left / will_i;  // always added spaces
          int ii = left % will_i;  // added spaces but not always
          for (int j = 0; j < will_i; j++) {
            t += words[p + j] + " ";
            for (int w = 0; w < alway_i; w++) t += " ";
            if (ii) {
              t += " ";
              ii--;
            }
          }
        }
        t += words[i - 1];
        if (!will_i) {
          for (int j = 0; j < left; j++) t += " ";
        }
        res.push_back(t);
        p = i;
        word_len = 0;
      }
    }
    int left = maxWidth - word_len - (i - p - 1);
    string t = "";
    for (; p < len; p++) {
      t += words[p];
      if (p != len - 1) t += " ";
    }
    for (int j = 0; j < left; j++) t += " ";
    res.push_back(t);
    return res;
  }
};

int main() {
  Solution s;
  vector<string> arr = {"This", "is", "an", "example", "of", "text", "justification."};
  // vector<string> arr = {"What","must","be","acknowledgment","shall","be"};
  // vector<string> arr = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
  // vector<string> arr = {"ask","not","what","your","country","can","do","for","you","ask","what","you","can","do","for","your","country"};

  auto res = s.fullJustify(arr, 16);
  for (auto i: res) {
    std::cout << "'" << i << "'" << std::endl;
  }
  return 0;
}
