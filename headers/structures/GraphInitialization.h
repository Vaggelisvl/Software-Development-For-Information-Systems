#ifndef _PROJECT_GRAPHINITIALIZATION_H
#define _PROJECT_GRAPHINITIALIZATION_H

#include "vector/Vector.h"
#include "unorderedMap/UnorderedMap.h"
#include "point/Point.h"
#include "point/Neighbors.h"

//typedef Vector<Neighbors> neighborsPoints;
//typedef Vector<Point> points;


class GraphInitialization{
private:
    int numOfPoints;
    int K;
    Vector<Point> points;
    UnorderedMap< Point, Vector<Neighbors>> graph;
    int checkRandomNum(Vector<Neighbors>,int,int);
public:
    GraphInitialization();
    void putPoints(Vector<float> coordinates);
    void initializeK();
    int getNumOfPoints();
    void setKRandomNeighbors();
//    ~GraphInitialization();

};


#endif //_PROJECT_GRAPHINITIALIZATION_H
