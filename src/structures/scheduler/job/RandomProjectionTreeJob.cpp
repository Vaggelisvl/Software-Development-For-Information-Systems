//
// Created by vaggelis on 8/1/2024.
//

#include "../../../../headers/structures/scheduler/job/RandomProjectionTreeJob.h"

void RandomProjectionTreeJob::execute() {
    tree->creatTrees();
}

RandomProjectionTreeJob::RandomProjectionTreeJob(RandomProjectionTrees *tree,NormCalculationJob *normCalculationJob,int id ) : tree(tree) {
    LOG_DEBUG(([&](){char *log=new char[35];sprintf(log, "RandomProjectionTreeJob created"); return log;})());
    this->setJobId(id);
    this->addDependency(normCalculationJob);
}
