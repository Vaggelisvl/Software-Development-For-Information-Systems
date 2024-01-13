//
// Created by vaggelis on 8/1/2024.
//

#include "../../../../headers/structures/scheduler/job/RandomProjectionTreeJob.h"

void RandomProjectionTreeJob::execute() {
    tree->creatTrees();
}

RandomProjectionTreeJob::RandomProjectionTreeJob(RandomProjectionTrees *tree) : tree(tree) {}
