

#include <cstdint>
#include "../../headers/structures/Dataset.h"


using namespace std;

Dataset::Dataset(char* filename,int num, int dimension):fileName(filename), numOfPoints(num), dimensions(dimension) {}

//Dataset::Dataset() {}

void Dataset::setNumOfPoints(int num){
    this->numOfPoints = num;
}

int Dataset::getNumOfPoints() const {
    return this->numOfPoints;
}

int Dataset::getDimensions() const {
    return this->dimensions;
}


void Dataset::readVectorFromFile(Vector<Point>& elements) {
    FILE *file = fopen(this->fileName, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file\n");
        return;
    }
    if(!this->numOfPoints) {
        uint32_t N;

        fread(&N, sizeof(uint32_t), 1, file);
        setNumOfPoints((int)N);
    }

    int num=0;
    // Reserve capacity in the Vector to accommodate N elements.
    elements.reserve(this->numOfPoints);
    for (uint32_t i = 0; i < this->numOfPoints; i++) {
        Vector<float> coordinates;
        for(int j=0;j< this->dimensions;j++){
            float element;  // Use the same type as the Vector
            fread(&element, sizeof(float ), 1, file);
            coordinates.push_back(element);
        }
        elements.push_back(Point(++num, coordinates));

    }
    fclose(file);
}