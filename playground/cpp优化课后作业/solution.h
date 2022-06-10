#ifndef _SOLUTION_H
#define _SOLUTION_H
// add more STL headers if needed
#include <vector>

namespace smartmore {
class Solution {
 public:
  template <typename T>
  float clacModule(std::vector<std::vector<T>>& A, std::vector<T>& x) {
    if (A.empty() || x.empty()) return 0;
    if (A.front().size() != x.size()) return 0;

    std::vector<T> res;

    for (int i = 0; i < A.size(); i++) {
      T sum = 0;
      for (int j = 0; j < A[i].size(); j++) {
        sum += A[i][j] * x[j];
      }
      res.emplace_back(sum);
    }

    T sum_2 = 0;
    for (auto num : res) {
      sum_2 += pow(num, 2);
    }
    if (sum_2 >= 0) return sqrt(sum_2);
    return 0;
  }
};
}  // namespace smartmore

#endif /* _SOLUTION_H */
