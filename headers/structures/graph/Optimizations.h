#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H

#include "GraphInitialization.h"

class Optimizations : public GraphInitialization{
private:
public:
    int localJoin();
    void sampling();
};


#endif //_PROJECT_OPTIMIZATIONS_H
