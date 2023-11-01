//
// Created by e.vrailas on 24/10/2023.
//
#include "../../../headers/config/Logger.h"
#include "../../../headers/structures/vector/Vector.h"
#include <iostream>
template<typename T>
Vector<T>::Vector():size(0), capacity(1) {
    array = new T[capacity];

    LOG_INFO("Vector has been created!");
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

template<typename T>
int  Vector<T>::partition(T* givenArray, int low, int high) {
    T pivot = givenArray[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (givenArray[j] < pivot) {
            i++;
            T temp = givenArray[i];
            givenArray[i] = givenArray[j];
            givenArray[j] = temp;
        }
    }

    T temp = givenArray[i + 1];
    givenArray[i + 1] = givenArray[high];
    givenArray[high] = temp;

    return i + 1;
}

template<typename T>
void  Vector<T>::quickSort(T* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

template<typename T>
void Vector<T>::sort() {
    quickSort(array, 0, size - 1);
}


