
#ifndef JOBQUEUE_H
#define JOBQUEUE_H


#include "JobNode.h"

class JobQueue {
private:
    JobNode* front;
    JobNode* back;
    int size;

public:
    JobQueue() : front(NULL), back(NULL) {}
//    ~JobQueue();
    void push(Job* job) ;

    Job* pop() ;
    Job* peek() ;// Add this line
    int getSize();
    JobNode* begin() ;
    inline bool empty() { return front == NULL;}
};

#endif
