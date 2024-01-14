
#ifndef JOBQUEUE_H
#define JOBQUEUE_H


#include "JobNode.h"

class JobQueue {
private:
    JobNode* front;
    JobNode* back;
    int size;

public:
    JobQueue() : front(nullptr), back(nullptr) {}

    void push(Job* job) ;

    Job* pop() ;
    Job* peek() ;// Add this line
    int getSize();
    JobNode* begin() ;
    inline bool empty() { return front == nullptr;}
};

#endif
