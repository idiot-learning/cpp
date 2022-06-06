#include <selectionsort.hpp>
#include "sorttesthelper.hpp"
#include "student.hpp"

int main() {
    int N = 10;
    int* arr = sorttesthelper::GenerateRandomArray(N, 0, 100);
    float arr_2[5] = {1.2, 1.1, 2.1, 2.3, 4.2};
    Student arr_student[4] = {{"wangchao", 100}, {"jiangmin", 100}, {"xxx", 60}};

    SelectionSort(arr_student, 3);
    sorttesthelper::TestSort("Selection sort", SelectionSort, arr_student, 4);
    sorttesthelper::PrintVector(arr_student, 4);
    return 0;
}