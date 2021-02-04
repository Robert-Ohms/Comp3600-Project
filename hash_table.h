// u6669461

#pragma once
#include <vector>
#include "case.h"

using namespace std;
template <class V>
class Hash_table {
    public:
        Hash_table();

        Hash_table(int buckets, vector<pair<string, V>> input_list);
        // Given a key, returns an int index in the hash table
        virtual int make_hash(string k);

        // Insert a key value pair into the hash table
        virtual void put(string k, V v);

        // Remove a key value pair from the hash table
        // Potentially not used, as intention is have hash table store legacy data
        virtual void remove(string k);

        // Get the value of a given key
        virtual V get(string k);

        virtual int get_size();
        
    protected:
        // Use closed addressing hash table
        int size;
        int table_buckets;
        vector<vector<pair<string, V>>> table;
};

extern template class Hash_table<Case>;
extern template class Hash_table<string>;