#ifndef _SOLUTION_H
#define _SOLUTION_H
// add more STL headers if needed
#include <cmath>
#include <thread>
#include <vector>
#include <algorithm>
#include<functional>
namespace smartmore
{

template <typename T>
void multiply_threading(std::vector<T>& result, const int thread_number, std::vector<std::vector<T>>& A, std::vector<T>& x)
{
    // Calculate workload
    const int THREADS_NUMBER = std::thread::hardware_concurrency();

    const int n_elements = (A.size() * A[0].size());
    const int n_operations = n_elements / THREADS_NUMBER;
    const int rest_operations = n_elements % THREADS_NUMBER;

    int start_op, end_op;

    if (thread_number == 0)
    {
        // First thread does more job
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else
    {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op)
    {
        int row = op % A.size();
        int col = op / A[0].size();
        float r = 0.0f;
        for (int i = 0; i < A[0].size(); ++i)
        {
            const float e1 = A[row][i];
            const float e2 = x[i];
            r += e1 * e2;
        }
        result[row] = r;
    }
}

class Solution
{
   public:

    template <typename T>
    inline float clacModule(std::vector<std::vector<T>>& A, std::vector<T>& x)
    {
        if (A.empty() || x.empty()) return 0;
        if (A.front().size() != x.size()) return 0;

        const int THREADS_NUMBER = std::thread::hardware_concurrency();

        std::vector<std::thread> threads(THREADS_NUMBER);
        std::vector<T> res(A.size(), 0);

        for (int i = 0; i < THREADS_NUMBER; ++i)
        {
            threads[i] = std::thread(multiply_threading<T>, std::ref(res), i, std::ref(A), std::ref(x));
        }


        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join)); 

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
