#ifndef _PROJECT_GRAPHINITIALIZATION_H
#define _PROJECT_GRAPHINITIALIZATION_H

#include "../vector/Vector.h"
#include "../unorderedMap/UnorderedMap.h"
#include "../point/Point.h"
#include "../point/Neighbors.h"


class GraphInitialization{
private:
    int numOfPoints;
    int K;
    Vector<Point> points;
    Vector<float> pointsMaxDistance;
    UnorderedMap< Point, Vector<Neighbors>> graph;
    int checkRandomNum(Vector<Neighbors>,int,int);
    int dimensions;

public:
//    void setDistances();
    void printGraph();
    GraphInitialization();
    void putPoints(Vector<float> coordinates);
    void initializeK();
    int getNumOfPoints();
    // for testing purposes
    int getK();
    Vector<Point> getPoints();
    Vector<Neighbors> getNeighborsOfPoint(Point point);
    void setK(int k);
    //end of testing purposes
    void calculateAllDistances();
    void setKRandomNeighbors();
    void sortKNeighbors();
    int KNNAlgorithm();
    Vector<Neighbors> findKNearestNeighborsForPoint(const Point& queryPoint, int k);
    void calculateAllPoints();
//    ~GraphInitialization();

};


#endif //_PROJECT_GRAPHINITIALIZATION_H
