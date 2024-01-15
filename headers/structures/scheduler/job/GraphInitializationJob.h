//
// Created by vaggelis on 14/1/2024.
//

#ifndef _PROJECT_GRAPHINITIALIZATIONJOB_H
#define _PROJECT_GRAPHINITIALIZATIONJOB_H


#include "Job.h"
#include "../../randomProjectionTrees/RandomProjectionTrees.h"

class GraphInitializationJob : public Job {
private:
    RandomProjectionTrees* tree;
public:
    explicit GraphInitializationJob(RandomProjectionTrees* tree, int jobId) ;
    void execute() override ;
};


#endif //_PROJECT_GRAPHINITIALIZATIONJOB_H
