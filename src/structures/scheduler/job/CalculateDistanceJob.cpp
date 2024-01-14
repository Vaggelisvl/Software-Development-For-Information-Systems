//
// Created by vaggelis on 13/1/2024.
//

#include "../../../../headers/structures/scheduler/job/CalculateDistanceJob.h"

CalculateDistanceJob::CalculateDistanceJob(Optimizations *optimizations,int p1,int p2,int id) :pointId1(p1),pointId2(p2){


    this->optimizations=optimizations;
    this->setJobId(id);
    char log[100];
//    sprintf(log, "CalculateDistanceJob created with pointIds %d and %d", pointId1,pointId2);
//    LOG_INFO(log);

}

void CalculateDistanceJob::execute() {
    LOG_DEBUG(([&](){char* buffer = new char[100];sprintf(buffer, "Calculating distance between %d and %d", pointId1,pointId2);return buffer;})());

    optimizations->calculateDistance(optimizations->getPoint(pointId1),optimizations->getPoint(pointId2));
    pthread_mutex_lock(&mutex);
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
//
//void CalculateDistanceJob::setPointId1(int pointId1) {
//    this->pointId1 = pointId1;
//}
//
//void CalculateDistanceJob::setPointId2(int pointId2){
//   this->pointId2 = pointId2;
//}
//
//int CalculateDistanceJob::getPointId1() const {
//    return pointId1;
//}
//
//int CalculateDistanceJob::getPointId2() const {
//    return pointId2;
//}