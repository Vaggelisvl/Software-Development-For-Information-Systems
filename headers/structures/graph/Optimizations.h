#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

typedef struct neighborList{
    Neighbors neighbor;
    bool flag;
}neighborList;

class Optimizations : public GraphInitialization{
private:
    UnorderedMap< Point, Vector<neighborList> > graph;
    int checkDuplicate(Vector<Neighbors>, Vector<Neighbors>, int, int);
    int checkRandomNum(Vector<neighborList>,int,int);

public:
    int localJoin();
    // void setKRandomNeighbors() override
    void sampling();
};


#endif //_PROJECT_OPTIMIZATIONS_H
