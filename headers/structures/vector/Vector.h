//
// Created by e.vrailas on 24/10/2023.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
template <typename T>
class Vector {
public:
    Vector<T>();


    void push_back(const T& value);
    T begin();
    T end();
    const T* begin() const {
        return array;
    };
    const T* end() const{
        return array+size;
    };
    void sort();
    T at(int index);
    int getSize() const ;
    void reserve(size_t newCapacity) ;
    void print();
private:
    void quickSort(T* array, int low, int high);
    int partition(T* array, int low, int high);
    T * array;
    size_t size;
    size_t capacity;


};



#endif //VECTOR_H
