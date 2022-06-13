#include <heap.hpp>
#include <random>
int main() {
    Heap<int> heap(5);
    for (int i = 0; i < 5; i++) {
        srand(time(nullptr));
        int val = rand() % 100;

        heap.Insert(val);
    }

    return 0;
}