// An implementation of Binary Heap.
#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__
#include <vector>

class PriorityQueue {
public:
    PriorityQueue(int capacity = 100);

    bool empty() const;
    int top() const;

    void push(int x);
    void pop();
    void makeEmpty();

    void print() const;

private:
    int currentSize;
    std::vector<int> array;
};

#endif