//
// Created by vaggelis on 13/1/2024.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../vector/Vector.h"
#include "../../config/Logger.h"
template <typename T>
class PriorityQueue {
private:
    int size;
    int capacity;
    T* heap;

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void siftUp(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        if (left < size && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        int right = rightChild(i);
        if (right < size && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            siftDown(maxIndex);
        }
    }

    T parent(int i) {
        return (i - 1) / 2;
    }

    T leftChild(int i) {
        return 2 * i + 1;
    }

    T rightChild(int i) {
        return 2 * i + 2;
    }

public:
    explicit PriorityQueue(int capacity) : size(0), capacity(capacity) {
        heap = new T[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void insert(T value) {
        if (size == capacity) {
            // Double the capacity of the queue
            capacity *= 2;
            // Create a new array with the new capacity
            T* newHeap = new T[capacity];
            // Copy the elements from the old array to the new array
            for (int i = 0; i < size; ++i) {
                newHeap[i] = heap[i];
            }
            // Delete the old array
            delete[] heap;
            // Set the heap pointer to the new array
            heap = newHeap;
        }
        heap[size] = value;
        siftUp(size);
        size++;
    }

    T getMax() {
        if (size == 0) {
            LOG_ERROR("Priority queue is empty");
        }
        return heap[0];
    }

    T extractMax() {
        if (size == 0) {
            LOG_ERROR("Priority queue is empty");
        }
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);
    }
};
#endif