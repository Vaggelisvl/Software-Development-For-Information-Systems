
#include <iostream>
#include <cmath>

#include "../../headers/structures/apostas_se_diastas.h"

float eukl_Apostash(Vector<float> a, Vector<float> b) {
    float apostash = 0.0;

    for (int i = 0; i < DIASTASH; i++) {
        apostash += (a.at(i) - b.at(i)) * (a.at(i) - b.at(i));
    }
    return sqrt(apostash);
}