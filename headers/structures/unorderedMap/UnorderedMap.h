//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_UNORDERMAP_H
#define PROJECT_2023_1_UNORDERMAP_H

#include <string>
#include "headers/structures/unorderedMap/KeyValue.h"
#include "../vector/Vector.h"

class UnorderedMap {
public:
    UnorderedMap(size_t size);

    // Insert a key-value pair into the hashmap
    void insert(int key, const std::string &value);

    // Find the value associated with a given key
    bool find(int key, std::string &value);

    // Remove a key-value pair from the hashmap
    void remove(int key);

    ~UnorderedMap();

private:
   Vector<KeyValue *> data;
    size_t capacity;

    // Hash function to map keys to array indices
    size_t hash(int key)

};


#endif //PROJECT_2023_1_UNORDERMAP_H
