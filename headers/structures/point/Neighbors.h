#ifndef NEIGHBORS_H
#define NEIGHBORS_H


#include "Point.h"

class Neighbors : public Point{
private:
    float distance;
    bool flag;
public:
    Neighbors(int id, float distance, Vector<float> coordinates);
    Neighbors();
    int getId() const;
    float getDistance() const;
    bool getFlag() const;
    void setDistance(float d);
    void setId(int id) override;
    void setFlag(bool flag);
    bool operator<(const Neighbors& other) const;
//    bool operator>(const Neighbors& other) const;
    bool operator==(const Neighbors& other) const ;

};


#endif