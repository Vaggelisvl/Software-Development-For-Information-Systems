#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

typedef struct DistanceContents {
    int id;
    float dist;
}DistanceContents;


class Optimizations : public GraphInitialization{
private:
    int checkDuplicate(Neighbors,Neighbors,Vector<Neighbors>, Vector<Neighbors>);
    int hashingDuplicateDistances(Point&, Point&);
    UnorderedMap<Point, DistanceContents > hashMap;
    UnorderedMap< Point, Vector<Neighbors> > reverseNN;
    float d;
    static int incrementalSearch(bool,bool);
    void removeReverseNeighbor(const Neighbors&,const Point&);
    void putReverseNeighbor(const Neighbors&,const Point&);
public:
    void setd(float);
    UnorderedMap<Point, Vector<Neighbors> > localJoin(int,int&,Vector<Point>&);
    int KNN();
    void initFlags();
    void findKNearestNeighborsForPoint(const Point& queryPoint) override;
    void initReverseNN();
    void printReverseNN(char*);
};


#endif //_PROJECT_OPTIMIZATIONS_H
