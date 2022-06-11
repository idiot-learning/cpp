#ifndef _SOLUTION_H
#define _SOLUTION_H
// add more STL headers if needed
#include <omp.h>

#include <thread>
#include <vector>
namespace smartmore
{
class Solution
{
   public:
    template <typename T>
    inline float clacModule(std::vector<std::vector<T>>& A, std::vector<T>& x)
    {
        if (A.empty() || x.empty()) return 0;
        if (A.front().size() != x.size()) return 0;

        std::vector<T> res(A.size(), 0);
        T sum_2 = 0;

        for (int i = 0; i < A.size(); i++)
        {
            T sum = 0;
            for (int j = 0; j < A[i].size(); j++)
            {
                sum += A[i][j] * x[j];
            }
            res[i] = sum;
            sum_2 += pow(sum, 2);
        }

        if (sum_2 >= 0) return sqrt(sum_2);
        return 0;
    }

    template <typename T>
    inline float clacModule_thread(std::vector<std::vector<T>>& A, std::vector<T>& x)
    {
        if (A.empty() || x.empty()) return 0;
        if (A.front().size() != x.size()) return 0;

        const int THREADS_NUMBER = 16;

        std::thread threads[THREADS_NUMBER];
        std::vector<T> res(A.size(), 0);

        for (int i = 0; i < THREADS_NUMBER; ++i)
        {
            // std::cout << "Starting thread " << i << std::endl;
            threads[i] = std::thread(multiply_threading<T>, std::ref(res), i, std::ref(A), std::ref(x));
        }

        // std::cout << "Calculating...." << std::endl;

        for (int i = 0; i < THREADS_NUMBER; ++i)
        {
            // std::cout << "Joining thread " << i << std::endl;
            threads[i].join();
        }

        T sum_2 = 0;

        for (auto num : res)
        {
            sum_2 += pow(num, 2);
        }

        if (sum_2 >= 0) return sqrt(sum_2);

        return 0;
    }

    // sometimes it cannot give the right time
    template <typename T>
    inline float clacModule_omp(std::vector<std::vector<T>>& A, std::vector<T>& x)
    {
        if (A.empty() || x.empty()) return 0;
        if (A.front().size() != x.size()) return 0;

        std::vector<T> res;
        std::cout << "processors num : " << omp_get_num_procs() << std::endl;
#pragma omp parallel for shared(A, x, res)
        for (int i = 0; i < A.size(); i++)
        {
            T sum = 0;
            for (int j = 0; j < A[i].size(); j++)
            {
                sum += A[i][j] * x[j];
            }
            res.emplace_back(sum);
        }

        T sum_2 = 0;

        for (auto num : res)
        {
            sum_2 += pow(num, 2);
        }

        if (sum_2 >= 0) return sqrt(sum_2);

        return 0;
    }
};
}  // namespace smartmore

#endif /* _SOLUTION_H */
