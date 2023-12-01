#ifndef _PROJECT_GRAPHINITIALIZATION_H
#define _PROJECT_GRAPHINITIALIZATION_H

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


class GraphInitialization{
private:
    Vector<float> pointsMaxDistance;
    int checkRandomNum(Vector<Neighbors>,int,int);
protected:
    int numOfPoints;
    int K;
    Vector<Point> points;
    UnorderedMap< Point, Vector<Neighbors> > graph;
    int dimensions;
    char* metrics;
public:
    void printGraph();
    void printNeighbors(int id);
    GraphInitialization();
    void putPoints(Vector<float> coordinates);
    void setDimensions(int num);
//    int getNumOfPoints();
    void setMetrics(char*);
    // for testing purposes
//    int getK();
//    Vector<Point> getPoints();
//    Vector<Neighbors> getNeighborsOfPoint(Point point);
    void setK(int);
    //end of testing purposes
    void calculateAllDistances();
    void setKRandomNeighbors();
    void sortKNeighbors();
    int KNNAlgorithm();
    void findKNearestNeighborsForPoint(const Point& queryPoint);
    UnorderedMap< Point, Vector<Neighbors> > getGraph();
//    Point getPoint(int id);
};


#endif //_PROJECT_GRAPHINITIALIZATION_H
