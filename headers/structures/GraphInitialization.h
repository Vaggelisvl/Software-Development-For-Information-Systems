#ifndef _PROJECT_GRAPHINITIALIZATION_H
#define _PROJECT_GRAPHINITIALIZATION_H

#include "vector/Vector.h"
#include "unorderedMap/UnorderedMap.h"
#include "point/Point.h"
#include "point/Neighbors.h"
#include "apostas_se_diastas.h"


class GraphInitialization{
private:
    int numOfPoints;
    int K;
    Vector<Point> points;
    Vector<float> pointsMaxDistance;
    UnorderedMap< Point, Vector<Neighbors>> graph;
    int checkRandomNum(Vector<Neighbors>,int,int);
    void printGraph();
//    void setDistances();
public:
    GraphInitialization();
    void putPoints(Vector<float> coordinates);
    void initializeK();
    int getNumOfPoints();
    void setKRandomNeighbors();
    void sortKNeighbors();
    void basicGraphAlgorithm();
//    ~GraphInitialization();

};


#endif //_PROJECT_GRAPHINITIALIZATION_H
