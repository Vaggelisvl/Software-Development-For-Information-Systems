//
// Created by e.vrailas on 24/10/2023.
//

#include "../../../headers/structures/unorderedMap/UnorderedMap.h"
UnorderedMap::UnorderedMap(size_t size): capacity(size) {
    data.resize(capacity, nullptr);
    LOG_INFO("UnorderedMap has been created!")
}

void UnorderedMap::insert(int key, const int &value) {
    size_t index = hash(key);
    KeyValue* current = data[index];

    // Check if the key already exists in the linked list
    while (current) {
        if (current->getKey() == key) {
            // Key already exists, update the value
            current->setNext(new KeyValue(key, value));
            return;
        }
        current = current->getNext();
    }

    // Add a new node to the beginning of the linked list
    KeyValue* newNode = new KeyValue(key, value);
    newNode->setNext(data[index]);
    data[index] = newNode;
}

bool UnorderedMap::find(int key, int &value) {
    size_t index = hash(key);
    KeyValue* current = data[index];

    while (current) {
        if (current->getKey() == key) {
            value = current->getValue();
            return true;
        }
        current = current->getNext();
    }

    return false;
}

void UnorderedMap::remove(int key) {
    size_t index = hash(key);
    KeyValue* current = data[index];
    KeyValue* prev = nullptr;

    while (current) {
        if (current->getKey() == key) {
            if (prev) {
                prev->setNext(current->getNext());
            } else {
                data[index] = current->getNext();
            }
            delete current;
            return;
        }
        prev = current;
        current = current->getNext();
    }
}

UnorderedMap::~UnorderedMap() {
    for (size_t i = 0; i < capacity; i++) {
        KeyValue* current = data[i];
        while (current) {
            KeyValue* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
}

//TODO change the function to be more efficient
size_t UnorderedMap::hash(int key) {
    return key % capacity;
}