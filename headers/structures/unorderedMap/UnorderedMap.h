//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_UNORDERMAP_H
#define PROJECT_2023_1_UNORDERMAP_H

#include <string>
#include "../vector/Vector.h"

template<typename Key, typename Value>
class UnorderedMap {
public:
    UnorderedMap();

    // Insert a key-value pair into the hashmap
    void insert(const Key& key, Value value);

    // Find the values associated with a given key
    bool find(const Key& key, Value& value);

    // Remove a key-value pair from the hashmap
    void remove(const Key& key);

    void print();


    ~UnorderedMap();

private:
    struct KeyValue {
        Key key;
        Value value;
        KeyValue* next;

        KeyValue(const Key& k, const Value v) : key(k), value(v), next(nullptr) {}
    };
    KeyValue ** data;
    size_t capacity;

    // Hash function to map keys to array indices
    size_t hash(const Key& key);

};




#endif //PROJECT_2023_1_UNORDERMAP_H
