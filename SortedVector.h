#ifndef __CS235_SORTED_VECTOR_H_
#define __CS235_SORTED_VECTOR_H_

#include <iostream>
#include "Tasks.h"

class Comparator
{
public:
    //compares the numbers representing deadlines
    bool operator()(GenericTask*first, GenericTask*second)
    {
        return (first->getDeadline() < second->getDeadline());
    }
};

template<class T, class Comparator = std::less<T>>
class SortedVector {
public:

    SortedVector() { vec.reserve(50); }

    // O(1) operations
    unsigned int capacity() const { return (unsigned int) vec.capacity(); }
    unsigned int size() const { return (unsigned int) vec.size(); }
    bool empty() const { return vec.empty(); }

    T& at(unsigned int pos) { return vec.at(pos); }
    T& front() { return vec.front(); }
    T& back() { return vec.back(); }
    const T& at(unsigned int pos) const { return vec.at(pos); }
    const T& front() const { return vec.front(); }
    const T& back() const { return vec.back(); }

    T& pop_back() { T& data = back(); vec.pop_back(); return data; }

    // O(n) operations
    void clear() { vec.clear(); }
    void display() const;

    void insert(const T& data);
    T& remove(unsigned int pos) { auto it = vec.begin(); std::advance(it,pos); T& data = *it; vec.erase(it); return data; }

    std::vector<T> toVector() const;

private:

    std::vector<T> vec;

};

#include "SortedVector.cpp"

#endif
