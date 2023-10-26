//
// Created by e.vrailas on 24/10/2023.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <iostream>

template <typename T>
class Vector {
public:
    Vector<T>();


    void push_back(const T& value);

    int at(int index);
    int getSize() const ;
    void reserve(size_t newCapacity) ;
    void print();
private:
    T * array;
    size_t size;
    size_t capacity;


};

template<typename T>
void Vector<T>::print() {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

}


#endif //VECTOR_H
