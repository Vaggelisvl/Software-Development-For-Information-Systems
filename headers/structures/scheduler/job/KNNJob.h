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
    explicit KNNJob(Optimizations* optimizations) ;
    void execute() override ;
};


#endif //_PROJECT_KNNJOB_H
