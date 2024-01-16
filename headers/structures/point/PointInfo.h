

#ifndef POININFO_H
#define POININFO_H

#include "../vector/Vector.h"

class PointInfo {
public:
    PointInfo(int i,int points);
    ~PointInfo()= default;
    void insert(int i ,float dis);
    void sortDistances(); // Function to sort distances
    int getPointsInserted();
    float getDistance(int i);
    int getId();
    int getNeighborId(int i);
private:
    struct Value{
        int id;
        float distance;

        Value(int i,float dist):id(i),distance(dist){};
    };
    int id;
    Value** distances;
    int pointsInserted;

    void quickSort(int low, int high);
    int partition(int low, int high);



};


#endif
