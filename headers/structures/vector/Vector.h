//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_VECTOR_H
#define PROJECT_2023_1_VECTOR_H

class Vector {
public:
    Vector();

    ~Vector();

    void push_back(int value);

    int at(int index);
    int getSize() const ;

private:
    int* array;
    int size;
    int capacity;

    void reserve(int newCapacity) ;
};


#endif //PROJECT_2023_1_VECTOR_H
