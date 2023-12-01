#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

struct incrementalSearch{
    int pointId;
    int
};

class Optimizations : public GraphInitialization{
private:
    UnorderedMap< Point, Vector<Neighbors, bool> > graph;
    int checkDuplicate(Vector<Neighbors>, Vector<Neighbors>, int, int);
public:
    int localJoin();
};


#endif //_PROJECT_OPTIMIZATIONS_H
