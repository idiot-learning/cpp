#ifndef __SORTTESTHELPER_HPP_
#define __SORTTESTHELPER_HPP_

#include <iostream>
#include <vector>
using namespace std;

namespace sorttesthelper {
// generate the random vector with n items, range is between [l, r]

int* GenerateRandomArray(int n, int l, int r) {
    int* res = new int[n];

    srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        int val = rand() % (r - l + 1) + l;
        res[i] = val;
    }
    return res;
}

int* CopyArray(int a[], int n) {
    int* arr = new int[n];
    copy(a, a + 1, arr);
    return arr;
}

template <typename T>
void PrintVector(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return;
}

template <typename T>
void TestSort(string sort_name, void (*sort)(T[], int), T arr[], int n) {
    clock_t start_time = clock();
    sort(arr, n);
    clock_t end_time = clock();
    cout << "Running time : " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
}
}  // namespace sorttesthelper

#endif