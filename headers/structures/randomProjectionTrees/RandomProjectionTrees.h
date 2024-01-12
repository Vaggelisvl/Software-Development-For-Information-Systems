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

typedef struct TreeContents{
    int id;
    Vector<Vector<int> > tree;
}TreeContents;

const float EPS = 1e-8;

class RandomProjectionTrees : public Optimizations{
private:
    int D;
    float calculateInnerProduct(Vector<float>, Vector<float>);
    void graphInitialization(Vector<Vector<int> >);
    Vector<TreeContents> trees;
    void fillGraph();


public:
    RandomProjectionTrees(int);
    int split(Vector<int>, Vector<Vector<int> > &);
    Vector<Vector<int> > hyperplane(Vector<int>);
    void printTree();
    void putPoints(Vector<float>);
    void initGraph();
//    void setMetrics(char*);

};


#endif //_PROJECT_RANDOMPROJECTIONTREES_H
