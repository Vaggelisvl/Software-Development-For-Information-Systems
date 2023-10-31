//
// Created by snz on 10/31/2023.
//

#ifndef _PROJECT_NEIGHBORS_H
#define _PROJECT_NEIGHBORS_H


#include "Point.h"

class Neighbors : public Point{
private:
    float distance;
public:
    Neighbors(int id, float distance, Vector<float> coordinates);
    Neighbors();
    int getId() const;
    float getDistance() const;
    void setDistance(float distance);
    void setId(int id) override;

};


#endif //_PROJECT_NEIGHBORS_H
