//
// Created by vaggelis on 3/1/2024.
//

#ifndef PROJECT_JOB_H
#define PROJECT_JOB_H

#include "../JobDependency.h"

class Job {
private:
    JobDependency *dependency;
    bool completed;
    int jobID;
public:
    int getJobId() const ;
    void setJobId(int jobId) ;
    void incrementJobId() ;
    Job() ;
    // Copy constructor
    Job(const Job& other) {
        dependency = new JobDependency(*other.dependency);
        completed = other.completed;
        jobID = other.jobID;
    }

    // Assignment operator
    Job& operator=(const Job& other) {
        if (this != &other) {
            delete dependency;
            dependency = new JobDependency(*other.dependency);
            completed = other.completed;
            jobID = other.jobID;
        }
        return *this;
    }
    virtual ~Job() ;
    void printJobState();
    void addDependency(Job* job) ;
    bool isCompleted() ;
    virtual void execute() = 0; // Pure virtual function
    bool run() ;
    bool areDependenciesMet() ;

};
#endif //_PROJECT_JOB_H
