#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

//typedef struct Neighbors{
//    Neighborss Neighbors;
//    bool flag;
//    bool operator<(const Neighbors& other) const;
//    //    bool operator>(const Neighborss& other) const;
//    bool operator==(const Neighbors& other) const ;
//}Neighbors;

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
    bool hasBeenInitialized=false;
public:
    void sampling();
    void initSampling();
    void setd(float);
    //for testing purposes
    float getd();
    //end of testing purposes
    UnorderedMap<Point, Vector<Neighbors> > localJoin(int,int&,Vector<Point>&);
    int KNN();
    void initFlags();
    int incrementalSearch(Neighbors &,Neighbors&);
    void findKNearestNeighborsForPoint(const Point& queryPoint) override;
    void initReverseNN();
    void removeReverseNeighbor(const Neighbors&,const Point&);
    void putReverseNeighbor(const Neighbors&,const Point&);
    void printReverseNN(char*);
};


#endif //_PROJECT_OPTIMIZATIONS_H
