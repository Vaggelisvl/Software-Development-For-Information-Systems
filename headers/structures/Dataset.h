#ifndef _PROJECT_DATASET_H
#define _PROJECT_DATASET_H

#include "../../headers/structures/vector/Vector.h"
#include "../../headers/config/Logger.h"
#include "../../headers/structures/point/Point.h"


class Dataset {
private:
    char* fileName;
    int numOfPoints;
    int dimensions;
public:
    Dataset(char*, int, int);
//    Dataset();
    void setNumOfPoints(int);
    int getNumOfPoints() const;
    int getDimensions() const;
    char* getFilename();
    void readVectorFromFile(Vector<Point>&);
//    ~Dataset();
};


#endif //_PROJECT_DATASET_H
