//
// Created by vaggelis on 13/1/2024.
//

#include "../../../headers/structures/scheduler/JobDependency.h"
#include "../../../headers/structures/scheduler/job/Job.h"
#include "../../../headers/config/Logger.h"

void JobDependency::addDependency(Job *job)  {
    LOG_DEBUG(([&](){char *buffer=new char[70];sprintf(buffer, "JobDependency::addDependency for job with id: %d" ,job->getJobId()); return buffer;})());

    pthread_rwlock_wrlock(&vectorRwlock);
    dependencies.push_back(job);
    pthread_rwlock_unlock(&vectorRwlock);
}

bool JobDependency::areDependenciesMet() {


    pthread_rwlock_rdlock(&vectorRwlock);
    for(int i=0;i< dependencies.getSize();i++) {
        if(!this->dependencies.at(i)->isCompleted()) {
            LOG_DEBUG(([&](){char *buffer=new char[70];sprintf(buffer, "JobDependency::areDependenciesMet for job with id: %d is false" ,this->dependencies.at(i)->getJobId());return buffer;})());
            return false;
        }
        LOG_DEBUG(([&](){char *buffer=new char[70];sprintf(buffer, "JobDependency::areDependenciesMet for job with id: %d is true" ,this->dependencies.at(i)->getJobId());return buffer;})());

    }
    pthread_rwlock_unlock(&vectorRwlock);
    return true;
}

JobDependency::JobDependency() {
    pthread_rwlock_init(&vectorRwlock, NULL);

}
