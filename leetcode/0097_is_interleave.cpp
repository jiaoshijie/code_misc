#include "head.hpp"

using std::string;
using std::vector;

/*
 * `|n - m| <= 1`: this condition is not important, because if s3 can be formed
 * by an interleaving of s1 and s2. It must achieves this condition.
 * Such as: s1 = `aabcdd` s2 = `abc` s3 = `aaabcbcdd`
 */

class Solution {
public:
  bool isInterleave_double_pointer_wrong(string s1, string s2, string s3) {
    if (s1.empty() && s2.empty() && s3.empty())
      return true;
    if (s1.size() + s2.size() != s3.size())
      return false;
    bool flag = s1[0] == s3[0];
    size_t s1_i = 0, s2_i = 0, s3_i = 0;
    string *ss = flag ? &s1 : &s2;
    size_t *ss_i = flag ? &s1_i : &s2_i;
    while (s3_i < s3.size()) {
      if (*ss_i < ss->size() && (*ss)[*ss_i] == s3[s3_i]) {
        (*ss_i)++;
        s3_i++;
      } else {
        flag = !flag;
        ss = flag ? &s1 : &s2;
        ss_i = flag ? &s1_i : &s2_i;
        if (*ss_i >= ss->size() || (*ss)[*ss_i] != s3[s3_i])
          return false;
      }
    }
    return true;
  }

  bool isInterleave(string s1, string s2, string s3) {
    size_t n = s1.size(), m = s2.size(), p = s3.size();
    if (n + m != p)
      return false;
    vector<vector<bool>> f(n + 1, vector<bool>(m + 1, false));
    f[0][0] = true;
    for (size_t i = 0; i <= n; ++i) {
      for (size_t j = 0; j <= m; ++j) {
        if (i > 0) {
          // NOTE: s1[i - 1] is the i-th element in s1
          f[i][j] = f[i - 1][j] && s1[i - 1] == s3[i + j - 1];
        }
        if (j > 0) {
          f[i][j] = f[i][j] || (f[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
      }
    }
    return f[n][m];
  }

  bool isInterleave_less_space(string s1, string s2, string s3) {
    size_t n = s1.size(), m = s2.size(), p = s3.size();
    if (n + m != p)
      return false;
    vector<vector<bool>> f(2, vector<bool>(m + 1, false));
    f[0][0] = true;
    for (size_t i = 0; i <= n; ++i) {
      size_t index = i % 2;
      for (size_t j = 0; j <= m; ++j) {
        if (i > 0) {
          // NOTE: s1[i - 1] is the i-th element in s1
          f[index][j] = f[(i - 1) % 2][j] && s1[i - 1] == s3[i + j - 1];
        }
        if (j > 0) {
          f[index][j] =
              f[index][j] || (f[index][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
      }
    }
    return f[n % 2][m];
  }
};

int main() {
  Solution s;
  assert(s.isInterleave_less_space("aabcc", "dbbca", "aadbbcbcac") == true);
  assert(s.isInterleave_less_space("aabcc", "dbbca", "aadbbbaccc") == false);
  assert(s.isInterleave_less_space("", "", "") == true);
  assert(s.isInterleave_less_space("a", "b", "a") == false);
  assert(s.isInterleave_less_space("aabcc", "dbbca", "aadbcbbcac") == true);
  // assert(
  //     s.isInterleave("ababababababababababababababababababababababababababababa"
  //                    "bababababababababababababababababababababbb",
  //                    "babababababababababababababababababababababababababababab"
  //                    "abababababababababababababababababababaaaba",
  //                    "abababababababababababababababababababababababababababa"
  //                    "bababababababababababababababababababababababababababab"
  //                    "abababababababababababababababababababababababababababa"
  //                    "bababababababababababababababababbb") == true);
  return 0;
}
