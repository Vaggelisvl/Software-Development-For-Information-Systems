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

const float EPS = 1e-8;

class RandomProjectionTrees : public Optimizations{
private:
//    int K;
    int D;
//    Vector<Point> points;
//    int numOfPoints;
//    int dimensions;
    Vector<Vector<int> > tree;
    float calculateInnerProduct(Vector<float>, Vector<float>);
    UnorderedMap<Point, Vector<Neighbors> > localGraphInitialization();
//    char* metrics;
//    UnorderedMap< Point, Vector<Neighbors> > graph;


public:
    RandomProjectionTrees(int);
    int split(Vector<int>);
    Vector<Vector<int> > hyperplane(Vector<int>);
    void printTree();
    void putPoints(Vector<float>);
    void initGraph();
    void setMetrics(char*);

};


#endif //_PROJECT_RANDOMPROJECTIONTREES_H