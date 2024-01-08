
#ifndef NORMCALCULATIONJOB_H
#define NORMCALCULATIONJOB_H


#include "Job.h"
#include "../../point/Point.h"

class NormCalculationJob : public Job {
private:
    Vector<Point> points;
public:
    NormCalculationJob(Vector<Point> points) : points(points) {}
    void execute() override ;
};
#endif
