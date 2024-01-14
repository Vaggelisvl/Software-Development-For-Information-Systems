//
// Created by vaggelis on 13/1/2024.
//

#ifndef JOBDEPENDENCY_H
#define JOBDEPENDENCY_H


#include "../vector/Vector.h"
class Job;
class JobDependency {
private:
   Vector<Job* > dependencies;

public:
    void addDependency(Job* job) ;
    bool areDependenciesMet() ;
};


#endif //_PROJECT_JOBDEPENDENCY_H
