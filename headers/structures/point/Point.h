//
// Created by snz on 10/31/2023.
//

#ifndef _PROJECT_POINT_H
#define _PROJECT_POINT_H


#include "../vector/Vector.h"

class Point {
protected:
    Vector<float > coordinates;
    int id;

public:
    Point(int id, Vector<float> coordinates);
    Point();

    virtual int getId() const;
    Vector<float> getCoordinates() const;
    void setCoordinates(Vector<float> coordinates);

    virtual void setId(int id);
};


#endif //_PROJECT_POINT_H
