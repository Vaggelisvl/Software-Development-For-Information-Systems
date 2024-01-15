//
// Created by vaggelis on 4/1/2024.
//

#include "../../../../headers/structures/scheduler/job/KNNJob.h"

void KNNJob::execute() {
    optimizations->KNN();
}

KNNJob::KNNJob(Optimizations *optimizations,int id) : optimizations(optimizations) {
    this->setJobId(id);
}
