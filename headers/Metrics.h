//
// Created by snz on 11/3/2023.
//

#ifndef _PROJECT_METRICS_H
#define _PROJECT_METRICS_H

#include "structures/vector/Vector.h"
const int DIASTASH = 100;
class Metrics {
public:
    static float eukl_Apostash(Vector<float> a, Vector<float> b);
};


#endif //_PROJECT_METRICS_H
