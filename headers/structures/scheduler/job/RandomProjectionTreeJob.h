//
// Created by vaggelis on 8/1/2024.
//
#include "Job.h"
#include "../../randomProjectionTrees/RandomProjectionTrees.h"

#ifndef _PROJECT_RANDOMPROJECTIONTREEJOB_H
#define _PROJECT_RANDOMPROJECTIONTREEJOB_H



class RandomProjectionTreeJob : public Job {
private:
    RandomProjectionTrees* tree;
public:
    explicit RandomProjectionTreeJob(RandomProjectionTrees* tree) ;
    void execute() override ;
};

#endif //_PROJECT_RANDOMPROJECTIONTREEJOB_H
