//
// Created by e.vrailas on 24/10/2023.
//

#include "../../../headers/structures/unorderedMap/UnorderedMap.h"
#include "../../../headers/config/Logger.h"

template<typename Key, typename Value>
UnorderedMap<Key, Value>::UnorderedMap(): data(nullptr), capacity(1000) {
    data = new KeyValue *[capacity]; // Create an array of pointers
    for (size_t i = 0; i < capacity; i++) {
        data[i] = nullptr; // Initialize each bucket with nullptr
    }
    LOG_INFO("UnorderedMap has been created!");
}

template<typename Key, typename Value>
void UnorderedMap<Key, Value>::insert(const Key &key, Value value) {

    size_t index = hash(key);
    KeyValue *current = data[index];
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
    auto *newNode = new KeyValue(key, value);
    newNode->next = data[index];
    data[index] = newNode;
}

template<typename Key, typename Value>
bool UnorderedMap<Key, Value>::find(const Key &key, Value &values) {
    size_t index = hash(key);
    KeyValue *current = data[index];

    while (current) {
        if (current->key == key) {
            values = current->value;
            return true;
        }
        current = current->next;
    }

    return false;
}

template<typename Key, typename Value>
void UnorderedMap<Key, Value>::remove(const Key &key) {
    size_t index = hash(key);
    KeyValue *current = data[index];
    KeyValue *prev = nullptr;

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

template<typename Key, typename Value>
UnorderedMap<Key, Value>::~UnorderedMap() {
    for (size_t i = 0; i < capacity; i++) {
        KeyValue *current = data[i];
        while (current) {
            KeyValue *temp = current;
            current = current->next;
            delete temp;
        }
        data[i] = nullptr; // Set the bucket to nullptr after deleting
    }
    delete[] data;
}

//TODO change the function to be more efficient
template<typename Key, typename Value>
size_t UnorderedMap<Key, Value>::hash(const Key &key) {
    return key.hashValue() % capacity;
}

template<typename Key, typename Value>
void UnorderedMap<Key, Value>::print() {
    for (size_t i = 0; i < capacity; i++) {
        KeyValue *current = data[i];
        while (current) {
            LOG_INFO((current->key + " " + current->value));
            current = current->next;
        }
    }


}

template<typename Key, typename Value>
Value UnorderedMap<Key, Value>::get(const Key &key) {
    size_t index = hash(key);
    KeyValue *current = data[index];

    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return Value();
}