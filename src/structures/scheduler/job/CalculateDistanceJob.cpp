//
// Created by vaggelis on 13/1/2024.
//

#include "../../../../headers/structures/scheduler/job/CalculateDistanceJob.h"

CalculateDistanceJob::CalculateDistanceJob(Optimizations *optimizations,int p1,int p2) :pointId1(p1),pointId2(p2){
    this->optimizations=optimizations;
    char log[100];
    sprintf(log, "CalculateDistanceJob created with pointIds %d and %d", pointId1,pointId2);
    LOG_INFO(log);

}

void CalculateDistanceJob::execute() {
    char log1[100];
    sprintf(log1, "Calculating distance between %d and %d", pointId1,pointId2);
    LOG_INFO(log1);
    optimizations->calculateDistance(optimizations->getPoint(pointId1),optimizations->getPoint(pointId2));
    char log[100];
    sprintf(log, "Distance between %d and %d calculated", pointId1,pointId2);
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
