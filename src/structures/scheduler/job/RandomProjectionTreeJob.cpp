//
// Created by vaggelis on 8/1/2024.
//

#include "../../../../headers/structures/scheduler/job/RandomProjectionTreeJob.h"

void RandomProjectionTreeJob::execute() {
    tree->creatTrees();
}

RandomProjectionTreeJob::RandomProjectionTreeJob(RandomProjectionTrees *tree,NormCalculationJob *normCalculationJob) : tree(tree) {
    char log[35];
    sprintf(log, "RandomProjectionTreeJob created");
    LOG_INFO(log);
    this->addDependency(normCalculationJob);
}
