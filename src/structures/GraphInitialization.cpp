#include <cstdlib>
#include <ctime>
#include <iostream>

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
    Vector<Neighbors> neighborsVector;
    this->graph.insert(currentPoint,neighborsVector);

    cout<<"put point with id: "<<currentPoint.getId()<<endl;
}

void GraphInitialization::initializeK(){
    this->K = 3;
//    this->K = (int)(this->numOfPoints * 0.01);
}


int GraphInitialization::getNumOfPoints(){
    return this->numOfPoints;
}

int GraphInitialization::checkRandomNum(Vector<Neighbors> neighborsVector, int randNum, int currentPointId) {
    int flag = 1;

    for(int p=0;p<neighborsVector.getSize();p++) {
        //if num already in the neighbor list
        if (neighborsVector.at(p).getId() == randNum) {
//            cout<<"again1"<<endl;
            flag = 0;
            break;
        }

        //if num is the current point id
        if(currentPointId == randNum){
            flag = 0;
//            cout<<"again2"<<endl;
            break;
        }
    }
    //find reverse neighbor vector from point(currentPoint)
    Vector<Neighbors> neighborCheckVector;
    Point reverseCheckPoint = this->points.at(randNum-1);
    this->graph.find(reverseCheckPoint,neighborCheckVector);
    //if reverse neighbor list is full
    if(neighborCheckVector.getSize() == this->K){
//        cout<<"again3"<<endl;
        flag = 0;
    }

    return !flag;
}

void GraphInitialization::setKRandomNeighbors(){
    srand(static_cast<unsigned>(time(nullptr)));

    //for every point
    for(int i=0;i<this->numOfPoints;i++) {
        cout<<"---------------i="<<i+1<<"-----------------"<<endl;
        int randomNum;
        Vector<Neighbors> neighborsVector;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint,neighborsVector);

        int neighborCapacity = this->K-neighborsVector.getSize();
        //for every neighbor
        for (int j = 0; j < neighborCapacity; j++) {
            int loopFlag = 1;
            while(loopFlag){
                //generate random num
                randomNum = (rand() % (this->numOfPoints)) + 1;
                cout<<"randnum:"<<randomNum<<endl;

                //if num is ok, stop the loop
                loopFlag = checkRandomNum(neighborsVector, randomNum, i+1);

            }

            for(int p=0;p<this->points.getSize();p++) {
                //find neighbor from points
                if (this->points.at(p).getId() == randomNum) {
                    //init current point neighbor
                    Neighbors neighborsOfPoint(randomNum,0.0,this->points.at(p).getCoordinates());
                    neighborsVector.push_back(neighborsOfPoint);
                    cout<<"pointid:"<<p+1<<endl;

                    //find reverse neighbor from point(currentPoint)
                    Vector<Neighbors> reverseNeighborsVector;
                    Point reversePoint = this->points.at(randomNum-1);
                    this->graph.find(reversePoint,reverseNeighborsVector);
                    cout<<"reverse:"<<reversePoint.getId()<<endl;

                    //init neighbor reserve neighbor
                    Neighbors reverseNeighborsOfPoint(i+1,0.0,currentPoint.getCoordinates());
                    reverseNeighborsVector.push_back(reverseNeighborsOfPoint);

                    //put neighbor reverse neighbor
                    this->graph.insert(reversePoint, reverseNeighborsVector);
                    break;
                }
            }

        }
        this->graph.insert(currentPoint,neighborsVector);

    }
    for (int i = 0; i < this->numOfPoints; ++i) {
        Vector<Neighbors> neighborsVector;
        //print graph
        cout<<endl<<"point: "<<i+1<<endl;
        for(int j=0;j< this->K;j++){
            this->graph.find(this->points.at(i),neighborsVector);
            cout<<"rand:"<<neighborsVector.at(j).getId()<<" ";
        }
        cout<<endl;
    }

}

//GraphInitialization::~GraphInitialization(){
//    for(int i=0;i<this->numOfPoints;i++){
//        this->graph.remove(this->points.at(i));
//    }
//}


