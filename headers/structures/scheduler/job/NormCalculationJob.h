
#ifndef NORMCALCULATIONJOB_H
#define NORMCALCULATIONJOB_H


#include "Job.h"
#include "../../point/Point.h"
#include "../../graph/GraphInitialization.h"

class NormCalculationJob : public Job {
private:
    Vector<Point> points;
    GraphInitialization* graphInitialization;
public:
    NormCalculationJob(Vector<Point> points,int id,GraphInitialization* graphInitialization) ;
    void execute() override ;
};
#endif
