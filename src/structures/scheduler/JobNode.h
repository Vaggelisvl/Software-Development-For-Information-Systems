//
// Created by vaggelis on 3/1/2024.
//

#ifndef _PROJECT_JOBNODE_H
#define _PROJECT_JOBNODE_H

#include "Job.h"

class JobNode {
public:
    Job* job;
    JobNode* next;

    explicit JobNode(Job* job) : job(job), next(nullptr) {}
};
#endif //_PROJECT_JOBNODE_H
