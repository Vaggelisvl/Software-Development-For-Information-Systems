/**
 * @file JobNode.h
 * @brief This file contains the declaration of the JobNode class.
 */
#ifndef JOBNODE_H
#define JOBNODE_H

#include "job/Job.h"

class JobNode {
public:
    Job* job;
    JobNode* next;
    /**
    * @brief Constructor for the JobNode class.
    * @param job The job to be associated with this node.
    */
    explicit JobNode(Job* job) : job(job), next(NULL) {}
    ~JobNode() = default;

};
#endif //_PROJECT_JOBNODE_H
