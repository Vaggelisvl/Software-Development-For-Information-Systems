//
// Created by vaggelis on 8/1/2024.
//
#include "Job.h"
#include "../../randomProjectionTrees/RandomProjectionTrees.h"
#include "NormCalculationJob.h"

#ifndef _PROJECT_RANDOMPROJECTIONTREEJOB_H
#define _PROJECT_RANDOMPROJECTIONTREEJOB_H



class RandomProjectionTreeJob : public Job {
private:
    RandomProjectionTrees* tree;
//    NormCalculationJob*normCalculationJob;
public:
    explicit RandomProjectionTreeJob(RandomProjectionTrees* tree,Vector<NormCalculationJob*>, int) ;
    ~RandomProjectionTreeJob() override = default;
    // Copy constructor
    RandomProjectionTreeJob(const RandomProjectionTreeJob& other) : Job(other) {
        tree = other.tree;
    }

    // Assignment operator
    RandomProjectionTreeJob& operator=(const RandomProjectionTreeJob& other) {
        if (this != &other) {
            Job::operator=(other);
            tree = other.tree;
        }
        return *this;
    }
    void execute() override ;
};

#endif //_PROJECT_RANDOMPROJECTIONTREEJOB_H
