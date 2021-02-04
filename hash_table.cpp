// u6669461

#include "hash_table.h"
using namespace std;

template <class V>
Hash_table<V>::Hash_table(){

}

template <class V>
Hash_table<V>::Hash_table(int buckets, vector<pair<string, V>> input_list){
    size = 0;
    table_buckets = buckets;
    vector<pair<string, V>> empty_slot;
    vector<vector<pair<string, V>>> new_table(buckets, empty_slot);
    table = new_table;

    // Insert each element of the unsorted input list into the table
    for (int i = 0; i < input_list.size(); i++)
    {
        pair<string, V> pair_i = input_list[i];
        put(pair_i.first, pair_i.second);
    }
    
}

template <class V>
int Hash_table<V>::make_hash(string k) {
    int my_hash = hash<string>{}(k);
    int bucket = my_hash % table_buckets;
    if (bucket < 0) {
        bucket += table_buckets;
    }
    return bucket;
}

template <class V>
void Hash_table<V>::put(string k, V v) {
    int hash_k = make_hash(k);

    // Need to check if an element with that key is already in table
    bool in_table = false;
    for (int i = 0; i < table[hash_k].size(); i++)
    {
        pair<string, V> element_i = table[hash_k][i];
        if (element_i.first == k) {
            table[hash_k][i] = make_pair(k, v);
            in_table = true;
            break;
        }
    }

    if (!in_table) {
        table[hash_k].push_back(make_pair(k, v));
        size += 1;
    }
    
}

template <class V>
void Hash_table<V>::remove(string k) {
    // Similar to insert, except delete element when found, or do nothing if not found
    int hash_k = make_hash(k);

    bool in_table = false;
    for (int i = 0; i < table[hash_k].size(); i++)
    {
        pair<string, V> element_i = table[hash_k][i];
        if (element_i.first == k) {
            table[hash_k].erase(table[hash_k].begin() + i);
            in_table = true;
            size -= 1;
            std::cout << "Removed element with key: " << k << endl;
            break;
        }
    }
    if (!in_table) {
        std::cout << "No element with key: " << k << endl;
    } 
}

template <class V>
V Hash_table<V>::get(string k) {
    V v;
    int hash_k = make_hash(k);

    vector<pair<string, V>> slot = table[hash_k];

    for (int i = 0; i < slot.size(); i++)
    {
        pair<string, V> element_i = slot[i];
        if (element_i.first == k) {
            v = slot[i].second;
            return v;
        }
    }
    std::cout << "No element with key: " << k << endl;
    return v;
}

template <class V>
int Hash_table<V>::get_size() {
    return size;
}

template class Hash_table<Case>;
extern template class Hash_table<string>;