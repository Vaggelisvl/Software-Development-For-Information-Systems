//
// Created by snz on 11/4/2023.
//

#ifndef _PROJECT_POININFO_H
#define _PROJECT_POININFO_H

#include "../vector/Vector.h"

class PointInfo {
public:
    PointInfo(int i,int points);
    void insert(int i ,float dis);
    void sortDistances(); // Function to sort distances
    void print();
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


#endif //_PROJECT_POININFO_H
