#include <cstdlib>
#include <ctime>

#include "../headers/GraphInitialization.h"
//#include "../headers/Point.h"
//#include "../headers/Neighbors.h"

using namespace std;

GraphInitialization::GraphInitialization(){
    this->numOfNode = 0;
    this->K = -1;
}

void GraphInitialization::putPoints(PointInfo point) {
    this->numOfNode ++;

    //point initialization id
    //          |
    //          ν
    //initializePoint(int numOdNodes){
    //  point.id = numOfNodes
    //  point.counter = 0;
    //}
    this->points.push_back(point);
}

void GraphInitialization::initializeK(){
    this->K = (int)(this->numOfNode * 0.01);
}

void GraphInitialization::generateRandomGraph(){
    for(int i=0;i<this->numOfNode;i++) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int j = 0; j < this->K; j++) {
            int randomNum;
            while(i != (randomNum = rand() % 20));
//            PointInfo point = this->points.at(randomNum);

            }

        }
//      this->graph.insert(point(i),vector(neighborspoints);

    }

}
