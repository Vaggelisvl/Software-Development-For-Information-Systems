//
// Created by e.vrailas on 24/10/2023.
//
#include "../../../headers/config/Logger.h"
#include "../../../headers/structures/vector/Vector.h"
#include <iostream>
template<typename T>
Vector<T>::Vector():size(0), capacity(1) {
    array = new T[capacity];

//    LOG_INFO("Vector has been created!");
}

template<typename T>
void Vector<T>::push_back(const T& value)  {
    if (size == capacity) {
        // Double the capacity when it's not sufficient
        reserve(2 * capacity);
    }
    array[size++] = value;
}
template<typename T>
T Vector<T>::at(int index)  {
    if (index < 0 || index >= size) {
        throw "Index out of bounds";
    }
    return array[index];
}

template<typename T>
int Vector<T>::getSize() const  {
    return size;
}
template<typename T>
void Vector<T>::reserve(size_t newCapacity) {
    T* newArray = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

template<typename T>
T Vector<T>::end() {
    return array+size;
}

template<typename T>
T Vector<T>::begin() {
    return array;
}
template<typename T>
void Vector<T>::print() {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

}

