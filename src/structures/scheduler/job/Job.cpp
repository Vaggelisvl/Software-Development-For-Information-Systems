////
//// Created by vaggelis on 4/1/2024.
////
//#include "../../../../headers/structures/scheduler/job/Job.h"


#include "../../../../headers/structures/scheduler/job/Job.h"
#include "../../../../headers/config/Logger.h"

int Job::getJobId() const {
    return jobID;
}

void Job::setJobId(int jobId) {
    jobID = jobId;
}

void Job::incrementJobId() { jobID++; }

bool Job::run() {
    if (dependency->areDependenciesMet()) {
        execute();
//        LOG_DEBUG(([&]() {
//            char *buffer = new char[55];
//            sprintf(buffer, "Job::run: Job %d completed", jobID);
//            return buffer;
//        })());
        completed = true;
        return true;
    } else {
//        LOG_DEBUG(([&]() {
//            char *buffer = new char[55];
//            sprintf(buffer, "Job::run: Dependencies not met for job %d", jobID);
//            return buffer;
//        })());
        return false;
    }
}

bool Job::isCompleted() {
    return completed;
}

void Job::addDependency(Job *job) {
//    char log[35];
//    sprintf(log, "Dependency added");
    dependency->addDependency(job);
}

Job::Job() : completed(false) {
    this->dependency = new JobDependency();
}

bool Job::areDependenciesMet() {
//    LOG_DEBUG(([&]() {
//        char *buffer = new char[55];
//        sprintf(buffer, "Job::areDependenciesMet for job with id %d", jobID);
//        return buffer;
//    })());
    return dependency->areDependenciesMet();
}

void Job::printJobState() {
    char log[100];
    sprintf(log, "Job is %s", completed ? "completed" : "not completed");
    sprintf(log, "Job Dependencies Met: %s", dependency->areDependenciesMet() ? "true" : "false");
    LOG_INFO(log);

}


