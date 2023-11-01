#ifndef _PROJECT_GRAPHINITIALIZATION_H
#define _PROJECT_GRAPHINITIALIZATION_H

#include "vector/Vector.h"
#include "unorderedMap/UnorderedMap.h"

typedef struct{
    int id;
    Vector<float> coordinates;
    Vector<float> distance;
    int counter;
}PointInfo;

typedef Vector<PointInfo> neighborsPoints;


class GraphInitialization{
private:
    int numOfNode;
    int K;
    Vector<PointInfo> points;
    UnorderedMap< PointInfo, neighborsPoints> graph;
public:
    GraphInitialization();
    void putPoints(PointInfo);
    void initializeK();
    void generateRandomGraph();
    ~GraphInitialization();

};


#endif //_PROJECT_GRAPHINITIALIZATION_H
