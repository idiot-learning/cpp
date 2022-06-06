#ifndef __SELECTIONSORT_HPP__
#define __SELECTIONSORT_HPP__
#include <utility>
template <class T>
void SelectionSort(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[min_index]) min_index = j;
        }
        std::swap(arr[i], arr[min_index]);
    }
}

#endif