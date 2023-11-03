#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../../headers/structures/GraphInitialization.h"
#include "apostas_se_diastas.cpp"
//#include "../../headers/structures/point/Point.h"
//#include "../../headers/structures/point/Neighbors.h"

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
    if(this->numOfPoints > 1000){
        this->K = (int)(this->numOfPoints * 0.01);
    }
    else {
        this->K = 3;
    }
}


int GraphInitialization::getNumOfPoints(){
    return this->numOfPoints;
}

int GraphInitialization::checkRandomNum(Vector<Neighbors> neighborsVector, int randNum, int currentPointId) {
    int flag = 1;

    for(int p=0;p<neighborsVector.getSize();p++) {
        //if num already in the neighbor list
        if (neighborsVector.at(p).getId() == randNum) {
            flag = 0;
            break;
        }

        //if num is the current point id
        if(currentPointId == randNum){
            flag = 0;
            break;
        }
    }
    //find reverse neighbor vector from point(currentPoint)
    Vector<Neighbors> neighborCheckVector;
    Point reverseCheckPoint = this->points.at(randNum-1);
    this->graph.find(reverseCheckPoint,neighborCheckVector);

    //if reverse neighbor list is full
    if(neighborCheckVector.getSize() == this->K){
        flag = 0;
    }

    return !flag;
}

void GraphInitialization::printGraph(){
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

void GraphInitialization::setKRandomNeighbors(){
    srand(static_cast<unsigned>(time(nullptr)));

    //for every point
    for(int i=0;i<this->numOfPoints;i++) {
//        cout<<"---------------i="<<i+1<<"-----------------"<<endl;
        int randomNum;
        Vector<Neighbors> neighborsVector;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint,neighborsVector);

        int neighborCapacity = this->K-neighborsVector.getSize();
        //for every neighbor
        for (int j = 0; j < neighborCapacity; j++) {
            int loopFlag = 1;
            int count = 0;
            while(loopFlag){
                //generate random num

                randomNum = (rand() % (this->numOfPoints)) + 1;
//                cout<<"randnum:"<<randomNum<<endl;

                //if num is ok, stop the loop
                loopFlag = checkRandomNum(neighborsVector, randomNum, i+1);

                count ++;
                if(count == 10){
                    cout<<"cannot find a matching point!"<<endl;
                    cout<<"point with id:"<<i+1<<" do not correspond to other neighbors!"<<endl;

                    loopFlag = 0;
                }

            }

            for(int p=0;p<this->points.getSize();p++) {
                //find neighbor from points
                if (this->points.at(p).getId() == randomNum) {
                    float distance = eukl_Apostash(currentPoint.getCoordinates(),this->points.at(p).getCoordinates());

                    cout<<"distance: "<<distance<<endl;
                    //init current point neighbor
                    Neighbors neighborsOfPoint(randomNum,distance,this->points.at(p).getCoordinates());
                    neighborsVector.push_back(neighborsOfPoint);
//                    cout<<"pointid:"<<p+1<<endl;

                    //find reverse neighbor from point(currentPoint)
                    Vector<Neighbors> reverseNeighborsVector;
                    Point reversePoint = this->points.at(randomNum-1);
                    this->graph.find(reversePoint,reverseNeighborsVector);
//                    cout<<"reverse:"<<reversePoint.getId()<<endl;

                    //init neighbor reserve neighbor
                    Neighbors reverseNeighborsOfPoint(i+1,distance,currentPoint.getCoordinates());
                    reverseNeighborsVector.push_back(reverseNeighborsOfPoint);

                    //put neighbor reverse neighbor
                    this->graph.insert(reversePoint, reverseNeighborsVector);
                    break;
                }
            }

        }
        this->graph.insert(currentPoint,neighborsVector);

    }
    this->printGraph();

}

//void GraphInitialization::setDistances() {
//    float distance;
//
//    //for every point in the graph
//    for(int i=0;i<this->numOfPoints;i++){
//
//        //find current point with the neighbor vector of it
//        Point currentPoint = this->points.at(i);
//        Vector<Neighbors> neighborsVector;
//        this->graph.find(currentPoint,neighborsVector);
//
//        int size = neighborsVector.getSize();
//
//        //for every neighbor
//        for(int j=0;j<neighborsVector.getSize();j++){
//            cout<<"here"<<endl;
//            Neighbors currentNeighbor;
//            currentNeighbor = neighborsVector.at(j);
//
//            distance = eukl_Apostash(currentPoint.getCoordinates(),currentNeighbor.getCoordinates());
//
//            currentNeighbor.setDistance(distance);
//
//            neighborsVector.push_back(currentNeighbor);
//        }
//    }
//}

void GraphInitialization::sortKNeighbors(){
    for(int i=0;i<this->numOfPoints;i++){
        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> neighborsVector;
        this->graph.find(currentPoint, neighborsVector);

        neighborsVector.sort();
    }
    cout<<"SORTED GRAPH:"<<endl;
    this->printGraph();
}

void GraphInitialization::basicGraphAlgorithm() {

    int changeFlag = 1;

    while(changeFlag) {
        cout<<"again"<<endl;
        changeFlag = 0;

        //for every point in the graph
        for (int i = 0; i < this->numOfPoints; i++) {

//        if(changeFlag){
//            i--;
//        }

            //find current point with the neighbor vector of it
            Point currentPoint = this->points.at(i);
            Vector<Neighbors> neighborsVector;
            this->graph.find(currentPoint, neighborsVector);

            //find max distance of neighbors
//            float maxNeighborDistance = neighborsVector.at(K - 1).getDistance();
            float maxNeighborDistance = 1.2;
//            cout<<"max="<<maxNeighborDistance<<endl;

            //for every neighbor
            for (int j = 0; j < this->K; j++) {

                //find neighbor point with the neighbor vector of it
                Point neighborPoint = this->points.at(i);
                Vector<Neighbors> extendedNeighborsVector;
                this->graph.find(neighborPoint, extendedNeighborsVector);

                //for every extended neighbor
                for (int p = 0; p < this->K; p++) {

                    //if is the revers neighbor ignore it
                    if (extendedNeighborsVector.at(p) == currentPoint) {
//                        cout<<"same"<<endl;
                        continue;
                    }

//                    cout<<"extendedDistance"<<extendedNeighborsVector.at(p).getDistance()<<endl;
                    //if is closer to current point
                    if (maxNeighborDistance > extendedNeighborsVector.at(p).getDistance()) {
//                    cout<<"here  i="<<i<<endl;
                        changeFlag = 1;
                        maxNeighborDistance = extendedNeighborsVector.at(p).getDistance();

                        //change the extended neighbor with the farthest current point neighbor
                        neighborsVector.at(K - 1) = extendedNeighborsVector.at(p);

                        neighborsVector.sort();
                    }
                }
            }
        }
    }
    this->printGraph();

}

//GraphInitialization::~GraphInitialization(){
//    for(int i=0;i<this->numOfPoints;i++){
//        this->graph.remove(this->points.at(i));
//    }
//}