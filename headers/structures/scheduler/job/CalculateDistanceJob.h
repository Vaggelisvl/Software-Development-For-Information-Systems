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
//    int getPointId1() const ;
//
//    void setPointId1(int pointId1) ;
//
//    int getPointId2() const ;
//    void setPointId2(int pointId2) ;
    bool getIsFinished() const;
public:
    explicit CalculateDistanceJob(Optimizations *optimizations,int,int,int);
    void waitUntilFinished();
    void execute() override;
};


#endif //_PROJECT_CALCULATEDISTANCEJOB_H
