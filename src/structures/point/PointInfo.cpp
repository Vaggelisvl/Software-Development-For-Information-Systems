//
// Created by snz on 11/4/2023.
//

#include "../../../headers/structures/point/PointInfo.h"

PointInfo::PointInfo(int i, int points) {
    this->id = i;
    this->distances = new Value *[points];
    this->pointsInserted = 0;
}

void PointInfo::insert(int i, float dis) {
    if(dis==0)
        return;
    this->distances[pointsInserted++] = new Value(i, dis);
}

void PointInfo::sortDistances() {
    quickSort(0, pointsInserted - 1);
}


void PointInfo::quickSort(int low, int high) {
    if (low < high) {
        int pivotIndex = partition(low, high);
        quickSort(low, pivotIndex - 1);
        quickSort(pivotIndex + 1, high);
    }
}


int PointInfo::partition(int low, int high) {
    float pivot = distances[high]->distance;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (distances[j]->distance < pivot) {
            i++;
            // Swap distances[i] and distances[j]
            Value *temp = distances[i];
            distances[i] = distances[j];
            distances[j] = temp;
        }
    }
    // Swap distances[i+1] and distances[high]
    Value* temp = distances[i + 1];
    distances[i + 1] = distances[high];
    distances[high] = temp;

    return i + 1;
}

int PointInfo::getPointsInserted() {
    return this->pointsInserted;
}

float PointInfo::getDistance(int i) {
    return this->distances[i]->distance;
}

int PointInfo::getId() {
    return this->id;
}

int PointInfo::getNeighborId(int i) {
    return this->distances[i]->id;
}

