#ifndef _PROJECT_DATASET_H
#define _PROJECT_DATASET_H


class Dataset {
private:
    int numofPoints;
    int dimensions;
public:
    Dataset(int, int);
    Dataset();
    void setNumOfPoints(int);
    void setDimensions(int);
    int getNumofPoints();
    int getDimensions();
    ~Dataset();
};


#endif //_PROJECT_DATASET_H
