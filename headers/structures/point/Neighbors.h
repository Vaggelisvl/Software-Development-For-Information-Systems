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
    void setDistance(float d);
    void setId(int id) override;
    bool operator<(const Neighbors& other) const;
    bool operator>(const Neighbors& other) const;
    bool operator==(const Neighbors& other) const ;

};


#endif //_PROJECT_NEIGHBORS_H