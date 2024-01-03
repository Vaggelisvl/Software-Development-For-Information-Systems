//
// Created by vaggelis on 3/1/2024.
//

#ifndef _PROJECT_JOBSCHEDULER_H
#define _PROJECT_JOBSCHEDULER_H


#include <csignal>
#include "Job.h"
#include "JobQueue.h"

class JobScheduler {
private:
    JobQueue queue;
    pthread_t* threads;
    int numThreads;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool stop;

public:
    explicit JobScheduler(int numThreads) ;
    ~JobScheduler() ;
    void submit(Job* job) ;
};
#endif //_PROJECT_JOBSCHEDULER_H
