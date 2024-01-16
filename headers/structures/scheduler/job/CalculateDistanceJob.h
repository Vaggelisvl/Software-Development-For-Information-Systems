//
// Created by vaggelis on 13/1/2024.
//

#ifndef _PROJECT_CALCULATEDISTANCEJOB_H
#define _PROJECT_CALCULATEDISTANCEJOB_H


#include "Job.h"
#include "../../graph/Optimizations.h"

class CalculateDistanceJob : public Job {
private:
    Optimizations *optimizations;
    int pointId1;
    int pointId2;
    bool isFinished = false;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

public:
    bool getIsFinished() const;
    explicit CalculateDistanceJob(Optimizations *optimizations,int,int,int);
    ~CalculateDistanceJob() override=default;
    void waitUntilFinished();
    void execute() override;
    // Copy constructor
    CalculateDistanceJob(const CalculateDistanceJob& other) : Job(other) {
        optimizations = other.optimizations;
        pointId1 = other.pointId1;
        pointId2 = other.pointId2;
        isFinished = other.isFinished;
        mutex = other.mutex;
        cond = other.cond;
    }

    // Assignment operator
    CalculateDistanceJob& operator=(const CalculateDistanceJob& other) {
        if (this != &other) {
            Job::operator=(other);
            optimizations = other.optimizations;
            pointId1 = other.pointId1;
            pointId2 = other.pointId2;
            isFinished = other.isFinished;
            mutex = other.mutex;
            cond = other.cond;
        }
        return *this;
    }


};


#endif //_PROJECT_CALCULATEDISTANCEJOB_H
