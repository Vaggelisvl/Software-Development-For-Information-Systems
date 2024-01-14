//
// Created by vaggelis on 13/1/2024.
//

#include "../../../headers/structures/scheduler/JobDependency.h"
#include "../../../headers/structures/scheduler/job/Job.h"
void JobDependency::addDependency(Job *job)  {
    char log[35];
    sprintf(log, "JobDependency::addDependency");
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