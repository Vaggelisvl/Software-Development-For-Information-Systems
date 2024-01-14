////
//// Created by vaggelis on 4/1/2024.
////
//#include "../../../../headers/structures/scheduler/job/Job.h"
//
//int Job::getJobId() const {
//    return jobID;
//}
//
//void Job::setJobId(int jobId) {
//    jobID = jobId;
//}
//
//void Job::incrementJobId() { jobID++; }
#include "../../../../headers/structures/scheduler/job/Job.h"

void Job::run() {
    if(dependency.areDependenciesMet()) {
        execute();
        completed = true;
    }
}

bool Job::isCompleted() {
    return completed;
}

void Job::addDependency(Job *job) {
    dependency.addDependency(job);
}

Job::Job() : completed(false) {}
