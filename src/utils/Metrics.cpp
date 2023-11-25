#include <stdlib.h>
#include <math.h>

#include "../../headers/utils/Metrics.h"

float Metrics::euclideanDistance(Vector<float> a, Vector<float> b,int dimensions){
    float apostash = 0.0;

    for (int i = 0; i < dimensions; i++) {
        apostash += (a.at(i) - b.at(i)) * (a.at(i) - b.at(i));
    }
    return sqrt(apostash);
}

float Metrics::manhattanDistance(Vector<float> a, Vector<float> b, int dimension) {
    float apostash = 0.0;

    for (int i = 0; i < dimension; i++) {
        apostash += abs(a.at(i) - b.at(i));
    }
    return apostash;

}