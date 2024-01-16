//
// Created by vaggelis on 8/1/2024.
//

#include "../../../../headers/structures/scheduler/job/RandomProjectionTreeJob.h"

void RandomProjectionTreeJob::execute() {
    tree->creatTrees();
}

RandomProjectionTreeJob::RandomProjectionTreeJob(RandomProjectionTrees *tree,Vector<NormCalculationJob*>normCalculationJob,int id ) : tree(tree) {
//    LOG_DEBUG(([&](){char *log=new char[35];sprintf(log, "RandomProjectionTreeJob created"); return log;})());
    this->setJobId(id);
    for(int i=0;i<normCalculationJob.getSize();i++)
         this->addDependency(normCalculationJob.at(i));
}
