#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

typedef struct neighborList{
    Neighbors neighbor;
    bool flag;
//    neighborList(Neighbors, bool);
}neighborList;

class Optimizations : public GraphInitialization{
private:
    UnorderedMap< Point, Vector<neighborList> > graph;
    int checkDuplicate(Vector<neighborList>, Vector<neighborList>, int, int);
    int checkRandomNum(Vector<neighborList>,int,int);

public:
    int localJoin();
    void setKRandomNeighbors() override;
};


#endif //_PROJECT_OPTIMIZATIONS_H
