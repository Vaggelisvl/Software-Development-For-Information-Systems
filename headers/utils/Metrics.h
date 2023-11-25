//
// Created by snz on 11/3/2023.
//

#ifndef _PROJECT_METRICS_H
#define _PROJECT_METRICS_H

#include "../structures/vector/Vector.h"
class Metrics {
public:
    static float euclideanDistance(Vector<float> a, Vector<float> b,int dimenstion);
     static float manhattanDistance(Vector<float> a, Vector<float> b,int dimension);
};


#endif //_PROJECT_METRICS_H
