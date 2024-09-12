#include "PriorityQueue.h"
#include <iostream>

PriorityQueue::PriorityQueue(int capacity) : currentSize { 0 } {
    array.assign(capacity+1, 0);
}

bool PriorityQueue::empty() const {
    return currentSize == 0;
}

int PriorityQueue::top() const {
    return array[1];
}

void PriorityQueue::print() const {
    for (size_t i { 1 }; i <= currentSize; i++)
        std::cout << array[i] << " ";
    std::cout << "\n";
}

void PriorityQueue::push(int x) {
    int hole { ++currentSize };
    if (hole > array.size())
        array.resize(2*currentSize);
    // Percolate up
    while (hole > 1 && x < array[hole/2]) {
        array[hole] = std::move(array[hole/2]);
        hole = hole >> 1;
    }
    array[hole] = x;
}

void PriorityQueue::pop() {
    array[1] = std::move(array[currentSize--]);
    int tmp { array[1] };
    int hole { 1 }, inext { 0 };
    for (; currentSize >= (hole << 1); hole = inext) {
        inext = hole << 1;
        if (currentSize >= inext + 1) inext = array[inext] < array[inext+1] ? inext : inext + 1;
        if (tmp < array[inext]) break;
        array[hole] = std::move(array[inext]);
    }
    array[hole] = std::move(tmp);
}