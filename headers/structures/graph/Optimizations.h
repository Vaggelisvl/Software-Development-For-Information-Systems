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

typedef struct incrementalSearchContents{
    bool flag;
    int id;
    bool operator==(const incrementalSearchContents& other) const ;
//    float dist;
}incrementalSearchContents;

class Optimizations : public GraphInitialization{
private:
//    UnorderedMap< Point, Vector<Neighbors> > graph;
    UnorderedMap<Point, Vector<incrementalSearchContents> > incrementalSearchMap;
    int checkDuplicate(Neighbors,Neighbors,Vector<Neighbors>, Vector<Neighbors>);
    int checkRandomNum(Vector<Neighbors>,int,int);
    int hashingDuplicateDistances(Point&, Point&);
    UnorderedMap<Point, DistanceContents > hashMap;
    int counter = 0;
    void tmpPrint(UnorderedMap<Point, Vector<Neighbors> >);
public:
    UnorderedMap<Point, Vector<Neighbors> > localJoin(int,int&,Vector<Point>&);
    void setGraph(UnorderedMap<Point, Vector<Neighbors> >);
    int KNN();
    void initFlags();
    void changeFlag(int, bool, int);
    void newParticipation(int, int);
    void removeParticipation(int, int);
//    void setKRandomNeighbors() override;
    int incrementalSearch(int,int,int);
    void findKNearestNeighborsForPoint(const Point& queryPoint) override;
    UnorderedMap<Point,Vector<Neighbors>>  updateGraph( Vector<Vector<Neighbors>>& updates);
    Vector<Vector<Neighbors>> computeUpdates();
    Vector<Vector<Neighbors>> fillNeighborsUpdatesDefault();
//    void printGraph() override;
    void printdup();
    void printParticipation(int);
    void samplingAndReverseJoin();
};


#endif //_PROJECT_OPTIMIZATIONS_H
