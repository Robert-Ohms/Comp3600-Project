// u6669461

#include <cmath>
#include "heap.h"
using namespace std;

template <class V>
Heap<V>::Heap() {
    vector<pair<int, V>> v{};
    set_heap(v);
}

template <class V>
Heap<V>::Heap(vector<pair<int, V>> h) {
    set_heap(h);
}

// Heapify node up heap when inserting
template <class V>
void Heap<V>::heapify_up(int index) {   
    if (index > 0) {
        int par_index = floor((index - 1)/2);
        pair<int, V> ind_pair = the_heap[index];
        pair<int, V> par_pair = the_heap[par_index];
        while ((index > 0) && (ind_pair.first > par_pair.first))
        {
            the_heap[index] = par_pair;
            the_heap[par_index] = ind_pair;
            index = par_index;
            ind_pair = the_heap[index];

            par_index = floor((index - 1)/2);
            par_pair = the_heap[par_index];
        }
    }
}

// Heapify node down heap when extracting
template <class V>
void Heap<V>::heapify_down(int index) {
    if (index < size) {
        while ((index * 2 < size))
        {
            int l_index = index * 2 + 1;
            int r_index = (index + 1) * 2;
            pair<int, V> ind_pair = the_heap[index];
            pair<int, V> l_pair = the_heap[l_index];
            // Cases to consider
            // If only one child, it must be a left child
            // and there cannot be any further nodes beyond that child
            if (size == r_index) {
                if (ind_pair.first < l_pair.first) {
                    the_heap[index] = l_pair;
                    the_heap[l_index] = ind_pair;
                }
                break;
            // If two children, need to select which child to swap with, if any
            } else if (size > r_index) {
                // Both children greater than parent
                // Swap with maximum child
                pair<int, V> r_pair = the_heap[r_index];
                if (ind_pair.first < l_pair.first && ind_pair.first < r_pair.first) {
                    // Swap with left
                    if (l_pair.first > r_pair.first) {
                        the_heap[index] = l_pair;
                        the_heap[l_index] = ind_pair;
                        index = l_index;
                    // Swap with right
                    } else {
                        the_heap[index] = r_pair;
                        the_heap[r_index] = ind_pair;
                        index = r_index;                        
                    }
                // Only less than left child
                } else if (ind_pair.first < l_pair.first) {
                    the_heap[index] = l_pair;
                    the_heap[l_index] = ind_pair;
                    index = l_index;
                // Only less than right child
                } else if (ind_pair.first < r_pair.first) {
                    the_heap[index] = r_pair;
                    the_heap[r_index] = ind_pair;
                    index = r_index;
                // Less than neither child
                } else {
                    break;
                }
            // No children, should be caught as part of while statement
            // Keep for insurance
            } else {
                break;
            }         
        }       
    }
}


template <class V>
void Heap<V>::insert(int i, V v) {
    the_heap.push_back(make_pair(i, v));
    size += 1;
    heapify_up(size - 1);
}

template <class V>
void Heap<V>::build(vector<pair<int, V>> v) {
    size = v.size();
    the_heap = v;
    for (int i = floor(size/2) - 1; i >= 0; i--)
    {
        heapify_down(i);
    }
}

template <class V>
pair<int, V> Heap<V>::extract_max() {
    pair<int, V> ret = the_heap[0];
    size -= 1;
    the_heap[0] = the_heap[size];
    the_heap.pop_back();
    heapify_down(0);
    return ret;
}

template <class V>
int Heap<V>::get_size() {
    return size;
}

template <class V>
vector<pair<int, V>> Heap<V>::get_heap() {
    return the_heap;
}

template class Heap<string>;
template class Heap<Info>;