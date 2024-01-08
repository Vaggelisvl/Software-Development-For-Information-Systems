//
// Created by vaggelis on 3/1/2024.
//

#ifndef _PROJECT_JOB_H
#define _PROJECT_JOB_H
class Job {
//private:
//    int jobID=0;
public:
//    int getJobId() const ;
//    void setJobId(int jobId) ;
//    void incrementJobId() ;

    virtual void execute() = 0; // Pure virtual function
};
#endif //_PROJECT_JOB_H
