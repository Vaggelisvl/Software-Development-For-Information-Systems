
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
    ~NormCalculationJob() override = default;
    // Copy constructor
    NormCalculationJob(const NormCalculationJob& other) : Job(other) {
        points = other.points;
        graphInitialization = other.graphInitialization;
    }

    // Assignment operator
    NormCalculationJob& operator=(const NormCalculationJob& other) {
        if (this != &other) {
            Job::operator=(other);
            points = other.points;
            graphInitialization = other.graphInitialization;
        }
        return *this;
    }
    void execute() override ;
};
#endif
