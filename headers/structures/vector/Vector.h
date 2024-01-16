#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <cstdio>

template <typename T>
class Vector {
public:
    Vector<T>();
    Vector(const Vector<T>& other);
    ~Vector();
    void push_back(const T& value);
    Vector<T>& operator=(const Vector<T>& other);
    const T* begin() const {
        return array;
    };
    const T* end() const{
        return array+size;
    };
    void sort();
    T & at(int index);
    int getSize() const ;
    void reserve(size_t newCapacity) ;
    void print();

    void replace(const T& oldValue, const T& newValue);
    void remove(const T& value) ;
    bool operator==(const Vector<T>& other) const;

    size_t getCapacity() const ;
    // Define the less than operator
    bool operator<(const Vector<T>& other) const ;

    // Define the greater than operator
    bool operator>(const Vector<T>& other) const ;
    bool empty() const {
        return size == 0;
    }

    // Clear the vector
    void clear() {
        delete[] array;
        size = 0;
        capacity = 1;
        array = new T[capacity];
    }

    // Insert a value at a specific position
    void insert(int index, const T& value) {
        if (index < 0 || index > size) {
            throw "Index out of bounds";
        }
        if (size == capacity) {
            reserve(2 * capacity);
        }
        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
    }

    // Erase a value at a specific position
    void erase(int index) {
        if (index < 0 || index >= size) {
            throw "Index out of bounds";
        }
        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    // Access an element using the subscript operator
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw "Index out of bounds";
        }
        return array[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw "Index out of bounds";
        }
        return array[index];
    }
    // New constructor that creates a Vector from a range
    Vector(T* start, T* end) ;
    // New constructor that creates a Vector from a range
    Vector(int start, int end) {
        size = end - start;
        capacity = size;
        array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            array[i] = array[start + i];
        }
    }
private:
    void quickSort(T* array, int low, int high);
    int partition(T* array, int low, int high);
    T * array;
    size_t size;
    size_t capacity;




};

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        delete[] array;
        size = other.size;
        capacity = other.capacity;
        array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) {
    size = other.size;
    capacity = other.capacity;
    array = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        array[i] = other.array[i];
    }

}

template<typename T>
Vector<T>::Vector(T *start, T *end) {
    size = end - start;
    capacity = size;
    array = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        array[i] = start[i];
    }
}

template<typename T>
size_t Vector<T>::getCapacity() const {
    return capacity;
}

template<typename T>
Vector<T>::Vector():size(0), capacity(1) {
    array = new T[capacity];

//    LOG_INFO("vector has been created!");
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
T& Vector<T>::at(int index)  {
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
void Vector<T>::print() {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    printf("\n");
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



template<typename T>
bool Vector<T>::operator>(const Vector<T> &other) const {
    return (other < *this);
}
template<typename T>
bool Vector<T>::operator==(const Vector<T> &other) const  {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] != other.array[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vector<T>::operator<(const Vector<T> &other) const {
    if (size < other.size) {
        return true;
    } else if (size > other.size) {
        return false;
    } else {
        for (size_t i = 0; i < size; i++) {
            if (array[i] < other.array[i]) {
                return true;
            } else if (array[i] > other.array[i]) {
                return false;
            }
        }
        return false;
    }
}

template <typename T>
void Vector<T>::replace(const T& oldValue, const T& newValue) {
    for (int i = 0; i < size; i++) {
        if (array[i] == oldValue) {
            array[i] = newValue;
            break;
            // If you want to replace only the first occurrence, you can add a break statement here.
        }
    }
}

template<typename T>
Vector<T>::~Vector() {
//    delete[] array;

}
template <typename T>
void Vector<T>::remove(const T& value) {
    int index = -1; // Initialize with an invalid index.

    // Find the index of the element with the given value.
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            index = i;
            break; // Stop searching once the value is found.
        }
    }

    // If the value was found, remove it from the vector.
    if (index != -1) {
        // Shift elements to the left to fill the gap.
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        size--; // Decrement the size to reflect the removal.
    }
}


#endif //VECTOR_H