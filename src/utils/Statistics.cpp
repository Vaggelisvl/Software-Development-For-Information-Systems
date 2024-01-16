//
// Created by snz on 11/26/2023.
//

#include <cstdlib>
#include "../../headers/utils/Statistics.h"
#include "../../headers/utils/Metrics.h"
#include "../../headers/config/Logger.h"

Statistics::Statistics( Vector<Point> points, int numOfPoints, int dimensions) {

    this->numOfPoints = numOfPoints;
    this->dimensions = dimensions;
    this->pointInfo = new PointInfo *[numOfPoints];
    this->points = points;
    this->statisticInfo = new StatisticInfo*[numOfPoints];
    for(int i=0;i<numOfPoints;i++){
        statisticInfo[i]=new StatisticInfo();
    }
    this->totalStatisticInfo=new StatisticInfo();
}

void Statistics::calculateAllDistances(char*metric) {
    for (int i = 0; i < numOfPoints; i++) {
        Point point = points.at(i);
        pointInfo[i] = new PointInfo(point.getId(), numOfPoints);
        for (int j = 0; j < numOfPoints; j++) {

            Point point1 = points.at(j);
            float dist;
            if(compareStrings(metric, "manhattan")) {
                dist = Metrics::manhattanDistance(point.getCoordinates(), point1.getCoordinates(),
                                                  this->dimensions);
            }
            else{
                dist = Metrics::euclideanDistance(point.getCoordinates(), point1.getCoordinates(),
                                                  this->dimensions);
            }
            pointInfo[i]->insert(point1.getId(),dist);
        }
    }
    FILE *file;
    file = fopen("results.txt", "w");
    if(file == NULL){
        LOG_ERROR("Cannot open results.txt file");
        exit(1);
    }

    for (int i = 0; i < numOfPoints; i++) {
        fprintf(file, "point: %d{\n", pointInfo[i]->getId());
        pointInfo[i]->sortDistances();
        //print 20 nearest neighbors points
        for(int j=0;j<pointInfo[i]->getPointsInserted();j++){
            if(fprintf(file,"point: %d", pointInfo[i]->getNeighborId(j))<0){
                LOG_ERROR("Cannot write point to results.txt file");
                exit(1);
            }

            if(fprintf(file," distance: %f\n", pointInfo[i]->getDistance(j))<0){
                LOG_ERROR("Cannot write distance to results.txt file");
                exit(1);
            }


        }
        fprintf(file, "\n}\n");
    }
    fclose(file);
}

bool Statistics::compareStrings(const char *str1, const char *str2) {
    // Iterate through each character and compare
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2)
            return false; // Characters are different


        // Move to the next character
        ++str1;
        ++str2;
    }

    // Check if both strings have reached the end
    return (*str1 == '\0' && *str2 == '\0');
}

void Statistics::calculateStatistics(int k,GraphInitialization *graph) {
    bool hasBeenCalculated=false;
    for(int i =0;i<this->numOfPoints;i++){
        hasBeenCalculated=false;
        if(k>pointInfo[i]->getPointsInserted()){
            k=pointInfo[i]->getPointsInserted();

        }
        Vector<Neighbors> neighborsVector;
        graph->getGraph().find(points.at(pointInfo[i]->getId()-1), neighborsVector);
        if(k>neighborsVector.getSize()){
            k=neighborsVector.getSize();
            LOG_WARN("K is bigger than the number of neighbors of the point");
        }
        for(int counter=0;counter<k;counter++) {
            hasBeenCalculated=false;
            for (int j = 0; j < neighborsVector.getSize(); j++) {
                if (pointInfo[i]->getNeighborId(counter) == neighborsVector.at(j).getId()) {
                    statisticInfo[i]->increaseRightDecision();
                    statisticInfo[i]->increaseTotal();
                    hasBeenCalculated=true;

                }
            }
            if(!hasBeenCalculated){
                statisticInfo[i]->increaseWrongDecision();
                statisticInfo[i]->increaseTotal();
            }
        }

        statisticInfo[i]->calculatePercentage();
    }
    for(int i=0;i<numOfPoints;i++){
        totalStatisticInfo->increaseRightDecisions(statisticInfo[i]->getRightDecision());
        totalStatisticInfo->increaseWrongDecisions(statisticInfo[i]->getWrongDecision());
        totalStatisticInfo->increaseTotals(statisticInfo[i]->getTotal());
    }
    totalStatisticInfo->calculatePercentage();

}

void Statistics::printStatistics(int k) {
    LOG_INFO("Statistics:");
    for(int i=0;i<numOfPoints;i++){
        printf("Point: %d\n",pointInfo[i]->getId());
        statisticInfo[i]->printStatistics();
    }

}

void Statistics::printInMatrixForm(int k){

    // Calculate the length of the "Point" string
    int pointLabelLength = snprintf(NULL, 0, "| Point: %d", pointInfo[0]->getId());
    const char* label = "|Right Decisions:";
    int labelLength = snprintf(NULL, 0, "%s", label);

    // Print the "Point" row
    for(int i=0;i<labelLength;i++)
        printf(" ");
    for (int i = 0; i < numOfPoints; i++) {
        printf("| Point: %d", pointInfo[i]->getId());
        // Pad with spaces to align the next column
        for (int j = 0; j < snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()) - snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()); j++) {
            printf(" ");
        }
    }

    // Print "Right Decisions" row
    printf("|Right Decisions:");
    for (int i = 0; i < numOfPoints; i++) {
        printf("| %d", statisticInfo[i]->getRightDecision());
        // Pad with spaces to align the next column
        for (int j = 0; j < snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()) - snprintf(NULL, 0, "| %d", statisticInfo[i]->getRightDecision()); j++) {
            printf(" ");
        }
    }

    // Print "Wrong Decisions" row
    printf("|Wrong Decisions:");
    for (int i = 0; i < numOfPoints; i++) {
        printf("| %d", statisticInfo[i]->getWrongDecision());
        // Pad with spaces to align the next column
        for (int j = 0; j < snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()) - snprintf(NULL, 0, "| %d", statisticInfo[i]->getWrongDecision()); j++) {
            printf(" ");
        }
    }

    // Print "Total Decisions" row
    printf("|Total Decisions:");
    for (int i = 0; i < numOfPoints; i++) {
        printf("| %d", statisticInfo[i]->getTotal());
        // Pad with spaces to align the next column
        for (int j = 0; j < snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()) - snprintf(NULL, 0, "| %d", statisticInfo[i]->getTotal()); j++) {
            printf(" ");
        }
    }

    // Print "Percentage" row
    printf("|Percentage:");
    const char* perLabel = "|Percentage:";
    int labelPerLength = snprintf(NULL, 0, "%s", perLabel);
    for(int i=0;i<labelLength-labelPerLength;i++)
        printf(" ");
    for (int i = 0; i < numOfPoints; i++) {
        printf("| %d%%", statisticInfo[i]->getPercentage());
        // Pad with spaces to align the next column
        for (int j = 0; j < snprintf(NULL, 0, "| Point: %d", pointInfo[i]->getId()) - snprintf(NULL, 0, "| %d%%", statisticInfo[i]->getPercentage()); j++) {
            printf(" ");
        }
    }
}

void Statistics::printTotalPercentage(int k) {
    LOG_INFO("Total Statistics");
    totalStatisticInfo->printStatistics();

}

Statistics::~Statistics() {
    for(int i=0;i<numOfPoints;i++){
        delete statisticInfo[i];
    }
    delete[] statisticInfo;
    delete totalStatisticInfo;
    for(int i=0;i<numOfPoints;i++){
        delete pointInfo[i];
    }
    delete[] pointInfo;

}

