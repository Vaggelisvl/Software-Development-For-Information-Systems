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

const float EPS = 1e-8;

class RandomProjectionTrees {
private:
    int D;
    Vector<Point> points;
    int numOfPoints;
    int dimensions;
    Vector<Vector<int> > tree;
    float calculateInnerProduct(Vector<float>, Vector<float>);

public:
    RandomProjectionTrees(int, int);
    int split(Vector<int>);
    Vector<Vector<int> > hyperplane(Vector<int>);
    void printTree();
    void putPoints(Vector<float>);
    void initGraph();

};


#endif //_PROJECT_RANDOMPROJECTIONTREES_H
