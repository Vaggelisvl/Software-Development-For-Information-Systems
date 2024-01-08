
#ifndef JOBQUEUE_H
#define JOBQUEUE_H


#include "JobNode.h"

class JobQueue {
private:
    JobNode* front;
    JobNode* back;

public:
    JobQueue() : front(nullptr), back(nullptr) {}

    void push(Job* job) ;

    Job* pop() ;

   inline bool empty() { return front == nullptr;}
};

#endif
