
#ifndef FINDKNEARESTNEIGHBORSFORPOINTJOB_H
#define FINDKNEARESTNEIGHBORSFORPOINTJOB_H


#include "../../graph/Optimizations.h"
#include "Job.h"

class FindKNearestNeighborsForPointJob : public Job {
private:
    Optimizations* optimizations;
    Point queryPoint;
public:
    FindKNearestNeighborsForPointJob(Optimizations* optimizations, const Point& queryPoint);
    void execute() override ;
};


#endif //_PROJECT_FINDKNEARESTNEIGHBORSFORPOINTJOB_H
