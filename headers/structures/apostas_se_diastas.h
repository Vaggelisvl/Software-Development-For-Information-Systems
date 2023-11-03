#ifndef _PROJECT_APOSTAS_SE_DIASTAS_H
#define _PROJECT_APOSTAS_SE_DIASTAS_H

#include "Dataset.h"
#include "vector/Vector.h"

const int DIASTASH = 100;

struct Shmeio {
    Vector<float>shm;
};

float eukl_Apostash(Vector<float> , Vector<float> );

#endif //_PROJECT_APOSTAS_SE_DIASTAS_H
