#include <cstdlib>
#include <ctime>

#include "../../headers/structures/GraphInitialization.h"
#include "../../headers/structures/point/Point.h"
#include "../../headers/structures/point/Neighbors.h"

#include "point/Neighbors.cpp"

using namespace std;

GraphInitialization::GraphInitialization() : numOfPoints(0), K(-1){
}

void GraphInitialization::putPoints(Vector<float> coordinates) {
    Point currentPoint;
    currentPoint.setId(++this->numOfPoints);
    currentPoint.setCoordinates(coordinates);

    this->points.push_back(currentPoint);

    cout<<"put point with id: "<<currentPoint.getId()<<endl;
}

void GraphInitialization::initializeK(){
    this->K = 5;
//    this->K = (int)(this->numOfPoints * 0.01);
}


int GraphInitialization::getNumOfPoints(){
    return this->numOfPoints;
}

void GraphInitialization::setKRandomNeighbors(){
//    cout<<"ok"<<endl;
    srand(static_cast<unsigned>(time(nullptr)));

    for(int i=0;i<this->numOfPoints;i++) {
        int randomNum;
        Vector<Neighbors> neighborsVector;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint.getId(),neighborsVector);
        cout<<endl<<"point: "<<currentPoint.getId()<<endl;

        for (int j = 0; j < this->K-neighborsVector.getSize(); j++) {
            int flag = 1;
            while(flag){
                randomNum = (rand() % this->numOfPoints) + 1;

                int neighborsFlag = 1;
                int currentPointFlag = 1;

                for(int p=0;p<neighborsVector.getSize();p++) {
                    if (neighborsVector.at(p).getId() == randomNum) {
                        neighborsFlag = 0;
                    }
                    if(i+1 == randomNum){
                        currentPointFlag = 0;
                    }
                }

                if(neighborsFlag && currentPointFlag) {
                    cout<<"randPoint:"<<randomNum<<" ";
                    flag = 0;
                }
            }

            for(int p=0;p<this->points.getSize();p++) {
                if (this->points.at(p).getId() == randomNum) {
                    Neighbors neighborsOfPoint(randomNum,0.0,this->points.at(p).getCoordinates());
                    neighborsVector.push_back(neighborsOfPoint);

                    break;
                }
            }

        }
    }

    for(int i=0;i<this->numOfPoints;i++){
        Vector<Neighbors> neighborsVector;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint.getId(),neighborsVector);
        this->graph.insert(currentPoint,neighborsVector);
    }
//
    }


