//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_UNORDERMAP_H
#define PROJECT_2023_1_UNORDERMAP_H

#include "../point/Point.h"
#include "../../config/Logger.h"

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

    //for testing purposes
    Vector<Key> getKeys();
    //

    void print();

    Value get(const Key& key);


    ~UnorderedMap();

private:
    struct KeyValue {
        Key key;
        Value value;
        KeyValue* next;

        KeyValue(const Key& k, const Value v) : key(k), value(v), next(NULL) {}
    };
    KeyValue ** data;
    size_t capacity;

    // Hash function to map keys to array indices
    size_t hash(const Key& key);
};

template<typename Key, typename Value>
Vector<Key> UnorderedMap<Key, Value>::getKeys() {
    Vector<Key> keys;
    for (size_t i = 0; i < capacity; i++) {
        KeyValue* current = data[i];
        if(current== NULL){
            break;
        }
        while (current) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    return keys;
}


template<typename Key, typename Value>
Value UnorderedMap<Key, Value>::get(const Key &key) {
    size_t index = hash(key);
    KeyValue* current = data[index];

    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    static Value v;

    return  v;
}

template<typename Key , typename Value>
UnorderedMap<Key,Value>::UnorderedMap(): data(NULL), capacity(1000) {
    data = new KeyValue*[capacity]; // Create an array of pointers
    for (size_t i = 0; i < capacity; i++) {
        data[i] = NULL; // Initialize each bucket with nullptr
    }
//    LOG_INFO("UnorderedMap has been created!");
}
template<typename Key , typename Value>
void UnorderedMap<Key,Value>::insert(const Key& key,  Value value) {

    size_t index = hash(key);
    KeyValue* current = data[index];
    // Check if the key already exists in the linked list
    while (current) {
        if (current->key == key) {
            // Key already exists, update the value
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Add a new node to the beginning of the linked list
    KeyValue* newNode = new KeyValue(key, value);
    newNode->next = data[index];
    data[index] = newNode;
}
template<typename Key , typename Value>
bool UnorderedMap<Key,Value>::find(const Key& key, Value &values) {
    size_t index = hash(key);
    KeyValue* current = data[index];

    while (current) {
        if (current->key == key) {
            values = current->value;
            return true;
        }
        current = current->next;
    }

    return false;
}
template<typename Key,typename Value>
void UnorderedMap<Key,Value>::remove(const Key& key) {
    size_t index = hash(key);
    KeyValue* current = data[index];
    KeyValue* prev = NULL;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                data[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}
template<typename Key,typename Value>
UnorderedMap<Key,Value>::~UnorderedMap() {
//    for (size_t i = 0; i < capacity; i++) {
//        KeyValue* current = data[i];
//        while (current) {
//            KeyValue* temp = current;
//            current = current->next;
//            delete temp;
//
//        }
//        data[i] = nullptr; // Set the bucket to nullptr after deleting
//    }
//    delete[] data;
}

//TODO change the function to be more efficient
template <typename Key, typename Value>
size_t UnorderedMap<Key, Value>::hash(const Key& key) {
    return key.hashValue() % capacity;
}

template<typename Key, typename Value>
void UnorderedMap<Key, Value>::print() {
    for (size_t i = 0; i < capacity; i++) {
        KeyValue* current = data[i];
        while (current) {
            current = current->next;
        }
    }
}




#endif //PROJECT_2023_1_UNORDERMAP_H
