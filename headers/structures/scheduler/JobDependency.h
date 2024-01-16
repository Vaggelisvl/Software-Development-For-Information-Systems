//
// Created by vaggelis on 13/1/2024.
//
#include <pthread.h>

#ifndef JOBDEPENDENCY_H
#define JOBDEPENDENCY_H


#include "../vector/Vector.h"
class Job;
class JobDependency {
private:
   Vector<Job* > dependencies;
    pthread_rwlock_t vectorRwlock;
public:
    JobDependency() ;
    // Copy constructor
    JobDependency(const JobDependency& other) {
        pthread_rwlock_init(&vectorRwlock, NULL);
        for (size_t i = 0; i < other.dependencies.getSize(); ++i) {
            dependencies.push_back(other.dependencies[i]);
        }
    }

    // Assignment operator
    JobDependency& operator=(const JobDependency& other) {
        if (this != &other) {
            pthread_rwlock_destroy(&vectorRwlock);
            pthread_rwlock_init(&vectorRwlock, NULL);
            dependencies.clear();
            for (size_t i = 0; i < other.dependencies.getSize(); ++i) {
                dependencies.push_back(other.dependencies[i]);
            }
        }
        return *this;
    }

    ~JobDependency();
    void addDependency(Job* job) ;
    bool areDependenciesMet() ;
};


#endif //_PROJECT_JOBDEPENDENCY_H
