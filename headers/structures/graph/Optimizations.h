#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

typedef struct NeighborList{
    Neighbors neighbor;
    bool flag;
    bool operator<(const NeighborList& other) const;
    //    bool operator>(const Neighbors& other) const;
    bool operator==(const NeighborList& other) const ;
}NeighborList;

typedef struct DistanceContents {
    int id;
    float dist;
}DistanceContents;

class Optimizations : public GraphInitialization{
private:
    UnorderedMap< Point, Vector<NeighborList> > graph;
    int checkDuplicate(NeighborList,NeighborList,Vector<NeighborList>, Vector<NeighborList>);
    int checkRandomNum(Vector<NeighborList>,int,int);
    int hashingDuplicateDistances(Point&, Point&);
    UnorderedMap<Point, DistanceContents > hashMap;
    int counter = 0;
public:
    int localJoin();
    void setKRandomNeighbors() override;
    int incrementalSearch(NeighborList, NeighborList);
    void printGraph() override;
    void printdup();
};


#endif //_PROJECT_OPTIMIZATIONS_H
