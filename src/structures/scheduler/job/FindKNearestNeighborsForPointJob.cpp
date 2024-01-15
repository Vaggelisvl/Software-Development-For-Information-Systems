
#include "../../../../headers/structures/scheduler/job/FindKNearestNeighborsForPointJob.h"

void FindKNearestNeighborsForPointJob::execute() {
    optimizations->findKNearestNeighborsForPoint(queryPoint);
}

FindKNearestNeighborsForPointJob::FindKNearestNeighborsForPointJob(Optimizations *optimizations,
                                                                   const Point &queryPoint)             : optimizations(optimizations), queryPoint(queryPoint) {}