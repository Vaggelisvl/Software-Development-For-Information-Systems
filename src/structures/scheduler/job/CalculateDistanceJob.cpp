//
// Created by vaggelis on 13/1/2024.
//

#include "../../../../headers/structures/scheduler/job/CalculateDistanceJob.h"

CalculateDistanceJob::CalculateDistanceJob(Optimizations *optimizations,int p1,int p2) :pointId1(p1),pointId2(p2){
    this->optimizations=optimizations;

}

void CalculateDistanceJob::execute() {
    optimizations->calculateDistance(optimizations->getPoint(pointId1),optimizations->getPoint(pointId2));
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
