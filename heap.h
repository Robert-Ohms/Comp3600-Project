// u6669461

#pragma once
#include <vector>
#include <string>
#include "info.h"


using namespace std;
template <class V>
class Heap {
    public:
        Heap();

        Heap(vector<pair<int, V>> h);

        void set_heap(vector<pair<int, V>> h) {
            the_heap = h;
            size = h.size();
        }

        // Move element up heap
        virtual void heapify_up(int index);

        // Move element down heap
        virtual void heapify_down(int index);

        // Insert element into heap, then heapify
        virtual void insert(int i, V v);

        // Build a heap given an input list
        virtual void build(vector<pair<int, V>> v);

        // Take maximum element, then fix
        virtual pair<int, V> extract_max();

        virtual int get_size();

        virtual vector<pair<int, V>> get_heap();

    protected:
        int size;
        vector<pair<int, V>> the_heap;
};

extern template class Heap<string>;
extern template class Heap<Info>;