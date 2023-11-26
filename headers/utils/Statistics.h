//
// Created by snz on 11/26/2023.
//

#ifndef _PROJECT_STATISTICS_H
#define _PROJECT_STATISTICS_H


#include "../structures/point/PointInfo.h"
#include "../structures/point/Point.h"
#include "../structures/vector/Vector.h"
#include "../structures/graph/GraphInitialization.h"
#include "StatisticInfo.h"

class Statistics {
private:
    PointInfo **pointInfo;
    Vector<Point> points;
    int numOfPoints;
    bool compareStrings(const char* str1, const char* str2);
    int dimensions;
    StatisticInfo** statisticInfo;
    StatisticInfo* totalStatisticInfo;

public:
    Statistics( Vector<Point> points,int numOfPoints,int dimensions);
    void calculateAllDistances(char* metric);
    void printStatistics(int k);
    void calculateStatistics(int k,GraphInitialization *graph);
    void printInMatrixForm(int k);
    void printTotalPercentage(int k);
};


#endif //_PROJECT_STATISTICS_H
