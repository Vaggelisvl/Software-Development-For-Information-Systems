//
// Created by vaggelis on 14/1/2024.
//

#include "../../../../headers/structures/scheduler/job/GraphInitializationJob.h"

GraphInitializationJob::GraphInitializationJob(RandomProjectionTrees *tree, int jobId) {
    this->tree = tree;
    this->setJobId(jobId);

}

void GraphInitializationJob::execute() {
//    tree->graphInitialization();

}
