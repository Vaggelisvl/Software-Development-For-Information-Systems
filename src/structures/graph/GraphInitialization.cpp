#include <cstdlib>
#include <ctime>

#include "../../../headers/structures/graph/GraphInitialization.h"
#include "../../../headers/Metrics.h"




GraphInitialization::GraphInitialization() : numOfPoints(0), K(-1),dimensions(100){
}

void GraphInitialization::putPoints(Vector<float> coordinates) {
    Point currentPoint;
    currentPoint.setId(++this->numOfPoints);
    currentPoint.setCoordinates(coordinates);

    this->points.push_back(currentPoint);
    Vector<Neighbors> neighborsVector;
    this->graph.insert(currentPoint,neighborsVector);
    printf("put point with id: %d\n", currentPoint.getId());

}

void GraphInitialization::initializeK(){
    if(this->numOfPoints > 1000){
        this->K = (int)(this->numOfPoints * 0.01);
    }
    else {
        this->K = 5;
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
        for(int j=0;j< this->K;j++){
            this->graph.find(this->points.at(i),neighborsVector);
            char buffer[100]; // Adjust the buffer size as needed
            int neighborId = neighborsVector.at(j).getId();
            float neighborDistance = neighborsVector.at(j).getDistance();
            sprintf(buffer, "neighbor: %d [%.2f] ", neighborId, neighborDistance);
            LOG_INFO(buffer);

        }

    }
}

void GraphInitialization::setKRandomNeighbors(){
    srand(static_cast<unsigned>(time(nullptr)));

    //for every point
    for(int i=0;i<this->numOfPoints;i++) {
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
                while(currentPoint.getId() == randomNum){
                    randomNum = (rand() % (this->numOfPoints)) + 1;

                }
//                cout<<"randnum:"<<randomNum<<endl;

                //if num is ok, stop the loop
                loopFlag = checkRandomNum(neighborsVector, randomNum, i+1);

                count ++;
                if(count == 20){

                    char buffer1[100]; // Adjust the buffer size as needed
                    char buffer2[100]; // Adjust the buffer size as needed

                    sprintf(buffer1, "cannot find a matching point!");
                    sprintf(buffer2, "point with id: %d do not correspond to other neighbors!", i + 1);
                    LOG_WARN(buffer1);
                    LOG_WARN(buffer2);

                    loopFlag = 0;
                }

            }

            for(int p=0;p<this->points.getSize();p++) {
                //find neighbor from points
                if (this->points.at(p).getId() == randomNum) {
                    float distance = Metrics::eukl_Apostash(currentPoint.getCoordinates(),this->points.at(p).getCoordinates(),this->dimensions);

                    //init current point neighbor
                    Neighbors neighborsOfPoint(randomNum,distance,this->points.at(p).getCoordinates());
                    neighborsVector.push_back(neighborsOfPoint);

                    //find reverse neighbor from point(currentPoint)
                    Vector<Neighbors> reverseNeighborsVector;
                    Point reversePoint = this->points.at(randomNum-1);
                    this->graph.find(reversePoint,reverseNeighborsVector);

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

void GraphInitialization::sortKNeighbors(){
    for(int i=0;i<this->numOfPoints;i++){
        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> neighborsVector;
        this->graph.find(currentPoint, neighborsVector);

        neighborsVector.sort();
    }
    char buffer[50];
    sprintf(buffer,"SORTED GRAPH:");
    this->printGraph();
}

void GraphInitialization::calculateAllPoints() {
    for(int i=0;i<this->numOfPoints;i++){
        printf("point: %d\n", i + 1);
        Point currentPoint = this->points.at(i);
        for(int j=0;j< this->numOfPoints;j++){
            Point point2 = this->points.at(j);
            if(point2.getId() == currentPoint.getId()){
                continue;
            }
            float dist =  Metrics::eukl_Apostash(currentPoint.getCoordinates(), point2.getCoordinates(),this->dimensions);
            printf("neighbor: %d with dist: %lf\n", j + 1, dist);
        }
    }
}


int GraphInitialization::KNNAlgorithm() {
    int flag = 0;

    //for every point in the graph
    for (int i = 0; i < this->numOfPoints; i++) {

        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> neighborsVector;
        this->graph.find(currentPoint, neighborsVector);


        neighborsVector.sort();
        //find max distance of neighbors
        float maxNeighborDistance = neighborsVector.at(this->K - 1).getDistance();

        //for every neighbor
        for (int j = 0; j < this->K; j++) {

            //find neighbor point with the neighbor vector of it
            Point neighborPoint = this->points.at(neighborsVector.at(j).getId() - 1);
            Vector<Neighbors> extendedNeighborsVector;
            this->graph.find(neighborPoint, extendedNeighborsVector);

            //for every extended neighbor
            for (int p = 0; p < this->K; p++) {

                //if is the revers neighbor ignore it
                if (extendedNeighborsVector.at(p).getId() == currentPoint.getId()) {
                    continue;
                }

                //if extended neighbor exist in the neighbor list
                int exist = 0;
                for(int l=0;l<this->K;l++){
                    if(neighborsVector.at(l).getId() == extendedNeighborsVector.at(p).getId()){
                        exist = 1;
                    }
                }
                if(exist){
                    continue;
                }

                float extendedDistance = Metrics::eukl_Apostash(currentPoint.getCoordinates(),extendedNeighborsVector.at(p).getCoordinates(),this->dimensions);

                //if is closer to current point
                if (maxNeighborDistance > extendedDistance) {

                    if(neighborsVector.at(j).getDistance() == extendedNeighborsVector.at(p).getDistance()){
                        LOG_ERROR("Some error occurred inside the KNNAlgorithm function");

                    }

                    flag = 1;
                    neighborsVector.sort();
                    //change the extended neighbor with the farthest current point neighbor
                    neighborsVector.at(this->K - 1) = extendedNeighborsVector.at(p);
                    neighborsVector.at(this->K - 1).setDistance(extendedDistance);
                    neighborsVector.sort();
                    maxNeighborDistance = neighborsVector.at(this->K - 1).getDistance();

                    this->graph.insert(currentPoint, neighborsVector);

                }
            }
        }
    }

    if(flag){
        return 0;
    }

    this->sortKNeighbors();
    this->printGraph();
    LOG_INFO("FINISH ALGORITHM");
    return 1;

}
Vector<Neighbors> GraphInitialization::findKNearestNeighborsForPoint(const Point& queryPoint, int k) {
    Vector<Neighbors> neighborsVector;
    this->graph.find(queryPoint, neighborsVector);
    neighborsVector.sort();

    // If there are not enough neighbors, search for more from other points not in the graph
    while (neighborsVector.getSize() < k) {
        // Search for more neighbors from points not in the graph
        for (int i = 0; i < this->numOfPoints; i++) {
            Point currentPoint = this->points.at(i);
            // Check if the current point is already in the neighbors list
            if (currentPoint.getId() == queryPoint.getId()) {
                continue;
            }
            Vector<Neighbors> currentNeighbors;
            this->graph.find(currentPoint, currentNeighbors);
            bool hasExceed=false;
            for (int j = 0; j < currentNeighbors.getSize(); j++) {
                for(int counter=0;counter<neighborsVector.getSize();counter++){
                    if(neighborsVector.at(counter).getId()!=currentNeighbors.at(j).getId()){
                        neighborsVector.push_back(currentNeighbors.at(j));
                        if (neighborsVector.getSize() >= k) {
                            hasExceed=true;
                            break;
                        }
                    }
                    if(hasExceed)
                        break;
                }

            }
        }
    }

    // Return the top-k neighbors
    neighborsVector.reserve(k);
    return neighborsVector;
}



