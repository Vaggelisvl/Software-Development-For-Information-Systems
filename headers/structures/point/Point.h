//
// Created by snz on 10/31/2023.
//

#ifndef POINT_H
#define POINT_H


#include "../vector/Vector.h"

class Point {
protected:
    Vector<float > coordinates;
    int id;
    int hasBeenChoosen;

public:
    Point(int id, Vector<float> coordinates);
    Point();
    void setHasBeenChoosen(int hasBeenChoosen);
    int getHasBeenChoosen() const;
    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
    virtual int getId() const;
    Vector<float> getCoordinates() const;
    void setCoordinates(Vector<float> coordinates);
    size_t customHash() const;
    size_t hashValue() const ;
    virtual void setId(int id);


    Point(Point const &point);
};


#endif //_PROJECT_POINT_H
