//
// Created by vaggelis on 4/1/2024.
//

#ifndef _PROJECT_KNNJOB_H
#define _PROJECT_KNNJOB_H


#include "Job.h"
#include "../../../../headers/structures/graph/Optimizations.h"

class KNNJob : public Job {
private:
    Optimizations* optimizations;
public:
    explicit KNNJob(Optimizations* optimizations,int) ;
    ~KNNJob() override = default;
    // Copy constructor
    KNNJob(const KNNJob& other) : Job(other) {
        optimizations = other.optimizations;
    }

    // Assignment operator
    KNNJob& operator=(const KNNJob& other) {
        if (this != &other) {
            Job::operator=(other);
            optimizations = other.optimizations;
        }
        return *this;
    }
    void execute() override ;
};


#endif //_PROJECT_KNNJOB_H
