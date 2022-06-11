#ifndef _UTILITY_H
#define _UTILITY_H

#include <assert.h>

#include <random>
#include <vector>
// generate random matrix with given size M X N
template <typename T>
std::vector<std::vector<T>> GenerateMatrixMN(const int M, const int N)
{
    assert(M > 0 && N > 0);
    std::srand(time(nullptr));
    std::vector<std::vector<T>> res(M, std::vector<T>(N, 0));
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            float val = rand() % 200 + rand() / double(RAND_MAX);
            res[i][j] = val - 100;
        }
    }
    return res;
}

// generate random matrix with given size N X 1
template <typename T>
std::vector<T> GenerateMatrixN1(const int N)
{
    assert(N > 0);
    std::srand(time(nullptr));
    std::vector<T> res(N, 0);

    for (int j = 0; j < N; j++)
    {
        float val = rand() % 200 + rand() / double(RAND_MAX);
        res[j] = val - 100;
    }

    return res;
}

template <typename T>
void multiply_threading(std::vector<T>& result, const int thread_number, std::vector<std::vector<T>>& A, std::vector<T>& x)
{
    // Calculate workload
    const int THREADS_NUMBER = 16;

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

#endif