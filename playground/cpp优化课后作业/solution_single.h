#ifndef _SOLUTION_SINGLE_H
#define _SOLUTION_SINGLE_H
// add more STL headers if needed
#include <omp.h>

#include <cmath>
#include <thread>
#include <vector>
namespace smartmore_single
{
class Solution
{
   public:
    template <typename T>
    inline float clacModule(std::vector<std::vector<T>>& A, std::vector<T>& x)
    {
        if (A.empty() || x.empty()) return 0;
        if (A.front().size() != x.size()) return 0;

        // std::vector<T> res(A.size(), 0);
        T sum_2 = 0;

        for (int i = 0; i < A.size(); i++)
        {
            T sum = 0;
            for (int j = 0; j < A[i].size(); j++)
            {
                sum += A[i][j] * x[j];
            }
            sum_2 += pow(sum, 2);
        }

        if (sum_2 >= 0) return sqrt(sum_2);
        return 0;
    }

};
}  // namespace smartmore

#endif /* _SOLUTION_H */
