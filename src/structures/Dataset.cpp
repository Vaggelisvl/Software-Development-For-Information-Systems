
#include "../../headers/structures/Dataset.h"

Dataset::Dataset(int num, int dimension):numofPoints(num), dimensions(dimension) {}

Dataset::Dataset() {}

void Dataset::setNumOfPoints(int num){
    this->numofPoints = num;
}

void Dataset::setDimensions(int dimension){
    this->dimensions = dimension;
}

int Dataset::getNumofPoints() {
    return this->numofPoints;
}

int Dataset::getDimensions() {
    return this->dimensions;
}