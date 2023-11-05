//
// Created by snz on 11/3/2023.
//

#include <cmath>
#include "../headers/Metrics.h"

float Metrics::eukl_Apostash(Vector<float> a, Vector<float> b,int dimensions){
    float apostash = 0.0;

    for (int i = 0; i < dimensions; i++) {
        apostash += (a.at(i) - b.at(i)) * (a.at(i) - b.at(i));
    }
    return sqrt(apostash);
}