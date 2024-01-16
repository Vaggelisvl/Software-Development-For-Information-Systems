//
// Created by vaggelis on 13/1/2024.
//

#include <unistd.h>
#include "../../../../headers/structures/scheduler/job/CalculateDistanceJob.h"

CalculateDistanceJob::CalculateDistanceJob(Optimizations *optimizations,int p1,int p2,int id) :pointId1(p1),pointId2(p2){


    this->optimizations=optimizations;
    this->setJobId(id);
    char log[100];

}

void CalculateDistanceJob::execute() {
//    LOG_DEBUG(([&](){char* buffer = new char[100];sprintf(buffer, "Calculating distance between %d and %d", pointId1,pointId2);return buffer;})());

    pthread_mutex_lock(&mutex);
    optimizations->calculateNormDistance(optimizations->getPoint(pointId1),optimizations->getPoint(pointId2));

    isFinished = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

bool CalculateDistanceJob::getIsFinished() const {
    return isFinished;
}

void CalculateDistanceJob::waitUntilFinished() {
    pthread_mutex_lock(&mutex);
    while (!isFinished) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
}