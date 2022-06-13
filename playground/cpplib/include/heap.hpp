#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <vector>

template <class Item>
class Heap {
   public:
    Heap(int capacity) : data(std::vector<Item>(1)) {  // data vector starts from 1 , 0 index is not used
    }

    void Insert(const Item& item) {
        data.push_back(item);
        ShiftUp(data.size() - 1);
    }
    Item ExtractMax() {
        static_assert(data.size() > 1);
        Item ret = data[1];
        data[1] = data.back();
        data.pop_back();
        ShiftDown(1);
    }

   private:
    void ShiftUp(int index) {
        while (index > 0 && data[index / 2] < data[index]) {
            std::swap(data[index / 2], data[index]);
            index = index / 2;
        }
    }

    void ShiftDown(int index) {
        while (2 * index < data.size()) {
            int j = 2 * index;
            if (j + 1 < data.size() && data[j + 1] > data[j]) {
                j = j + 1;
            }

            if (data[j] > data[index]) {
                swap(data[index], data[j]);
            }
            index = j;
        }
    }

   private:
    std::vector<Item> data;
};

#endif