//
// Created by vaggelis on 13/1/2024.
//

#include "../../../headers/structures/scheduler/JobDependency.h"
#include "../../../headers/structures/scheduler/job/Job.h"
void JobDependency::addDependency(Job *job)  {
    dependencies.push_back(job);
}

bool JobDependency::areDependenciesMet() {
    for(Job* job : dependencies) {
        if(!job->isCompleted()) {
            return false;
        }
    }
    return true;
}