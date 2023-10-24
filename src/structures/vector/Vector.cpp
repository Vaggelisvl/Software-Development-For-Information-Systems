//
// Created by e.vrailas on 24/10/2023.
//

#include "../../../headers/structures/vector/Vector.h"
Vector::Vector() : size(0), capacity(1) {
    array = new int[capacity];
    LOG_INFO("Vector has been created!")
}
Vector::~Vector() {
    delete[] array;
    LOG_INFO("Deleting Vector")
}

void Vector::push_back(int value)  {
    if (size == capacity) {
        // Double the capacity when it's not sufficient
        reserve(2 * capacity);
    }
    array[size++] = value;
}

int Vector::at(int index)  {
    if (index < 0 || index >= size) {
        throw "Index out of bounds";
    }
    return array[index];
}

int Vector::getSize()  {
    return size;
}

void Vector::reserve(int newCapacity) {
    int* newArray = new int[newCapacity];
    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}
