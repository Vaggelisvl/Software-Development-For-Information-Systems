#ifndef _PROJECT_GRAPHALGORITHM_H
#define _PROJECT_GRAPHALGORITHM_H

#include "../../headers/structures/GraphInitialization.h"
#include "../../headers/structures/point/Point.h"
#include "../../headers/structures/point/Neighbors.h"

class GraphAlgorithm{
private:
    UnorderedMap< Point, Vector<Neighbors>> KNgraph;

public:
    GraphAlgorithm();

};

#endif //_PROJECT_GRAPHALGORITHM_H
