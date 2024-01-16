#ifndef _PROJECT_RANDOMPROJECTIONTREES_H
#define _PROJECT_RANDOMPROJECTIONTREES_H

#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string.h>

#include "../vector/Vector.h"
#include "../unorderedMap/UnorderedMap.h"
#include "../point/Point.h"
#include "../point/Neighbors.h"
#include "../../../headers/utils/Metrics.h"
#include "../../../headers/structures/point/PointInfo.h"
#include "../../../headers/structures/graph/Optimizations.h"
#include "../scheduler/JobScheduler.h"

typedef struct TreeContents{
    int id;
    Vector<Vector<int> > tree;
}TreeContents;

const float EPS = 1e-8;

class RandomProjectionTrees : public Optimizations{
private:
    int numberOfTrees;
    int D;
    Vector<TreeContents> trees;
    pthread_rwlock_t treeslock;
public:

    float calculateInnerProduct(Vector<float>, Vector<float>);
    RandomProjectionTrees(int);
    ~RandomProjectionTrees()=default;
    int split(Vector<int>, Vector<Vector<int> > &);
    Vector<Vector<int> > hyperplane(Vector<int>);
    void printTree();
    void putPoints(Vector<float>);
    void creatTrees();
    void graphInitialization(JobScheduler* scheduler,int);//jobScheduler
    int getNumberOfTrees();
    void fillGraph(JobScheduler* scheduler,int&);
};


#endif //_PROJECT_RANDOMPROJECTIONTREES_H
