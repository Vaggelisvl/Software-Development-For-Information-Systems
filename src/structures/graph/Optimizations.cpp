#include "../../../headers/structures/graph/Optimizations.h"

int Optimizations::checkDuplicate(Vector<Neighbors> neighborsVector1, Vector<Neighbors> neighborsVector2, int j, int k){
    if(neighborsVector1.at(j).getId() == neighborsVector2.at(k).getId()){
        return 1;
    }

    //if extended neighbor exist in the neighbor list
    for (int l = 0; l < this->K; l++) {
        if (neighborsVector1.at(l).getId() == neighborsVector2.at(k).getId()) {
            return 1;
        }
    }

    for (int l = 0; l < this->K; l++) {
        if (neighborsVector2.at(l).getId() == neighborsVector1.at(j).getId()) {
            return 1;
        }
    }
    return 0;
}

int Optimizations::checkRandomNum(Vector<neighborList> neighborListArg, int randNum, int currentPointId) {
    int flag = 0;

    for (int p = 0; p < neighborList.getSize(); p++) {
        //if num already in the neighbor list
        if (neighborList.at(p).neighbor.getId() == randNum) {
            flag = 1;
            break;
        }

    }
    //find reverse neighbor vector from point(currentPoint)
    Vector<neighborList> neighborCheckList;
    Point reverseCheckPoint = this->points.at(randNum - 1);
    this->graph.find(reverseCheckPoint, neighborCheckList);

    //if reverse neighbor list is full
    if (neighborCheckList.getSize() == this->K) {
        flag = 1;
    }

    return flag;
}


void Optimizations::setKRandomNeighbors() {
    srand(static_cast<unsigned>(time(nullptr)));

    //for every point
    for (int i = 0; i < this->numOfPoints; i++) {
        int randomNum;
        Vector<neighborList> neighborListArg;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint, neighborListArg);

        int neighborCapacity = this->K - neighborListArg.getSize();
        //for every neighbor
        for (int j = 0; j < neighborCapacity; j++) {
            int loopFlag = 1;
            int count = 0;
            while (loopFlag) {
                //generate random num

                randomNum = (rand() % (this->numOfPoints)) + 1;
                while (currentPoint.getId() == randomNum) {
                    randomNum = (rand() % (this->numOfPoints)) + 1;

                }

                //if num is ok, stop the loop
                loopFlag = checkRandomNum(neighborListArg, randomNum, i + 1);

                count++;
                if (count == 20) {

                    char buffer1[100]; // Adjust the buffer size as needed
                    char buffer2[100]; // Adjust the buffer size as needed

                    sprintf(buffer1, "cannot find a matching point!");
                    sprintf(buffer2, "point with id: %d do not correspond to other neighbors!", i + 1);
                    LOG_WARN(buffer1);
                    LOG_WARN(buffer2);

                    loopFlag = 0;
                }

            }

            for (int p = 0; p < this->points.getSize(); p++) {
                //find neighbor from points
                if (this->points.at(p).getId() == randomNum) {
                    float distance;
                    if(strcmp(this->metrics, "manhattan") == 0) {
                        distance = Metrics::manhattanDistance(currentPoint.getCoordinates(),
                                                              this->points.at(p).getCoordinates(), this->dimensions);

                    }
                    else{
                        distance = Metrics::euclideanDistance(currentPoint.getCoordinates(),
                                                              this->points.at(p).getCoordinates(), this->dimensions);
                    }

                    //init current point neighbor
                    Neighbors neighborsOfPoint(randomNum, distance, this->points.at(p).getCoordinates());
                    neighborsVector.push_back(neighborsOfPoint);

                    //find reverse neighbor from point(currentPoint)
                    Vector<Neighbors> reverseNeighborsVector;
                    Point reversePoint = this->points.at(randomNum - 1);
                    this->graph.find(reversePoint, reverseNeighborsVector);

                    //init neighbor reserve neighbor
                    Neighbors reverseNeighborsOfPoint(i + 1, distance, currentPoint.getCoordinates());
                    reverseNeighborsVector.push_back(reverseNeighborsOfPoint);

                    //put neighbor reverse neighbor
                    this->graph.insert(reversePoint, reverseNeighborsVector);
                    break;
                }
            }

        }
        this->graph.insert(currentPoint, neighborsVector);

    }

}

int Optimizations::localJoin() {
    int flag = 0;

    //for every point in the graph
    for (int i = 0; i < this->numOfPoints; i++) {
        UnorderedMap<Point, Vector<Neighbors> > tempGraph;
        int count = 0;
        Vector<Point> tempPointVector;

        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> currentNeighborsVector;
        this->graph.find(currentPoint, currentNeighborsVector);



        for (int j = 0; j < this->K; j++) {

            //find neighbor point with the neighbor vector of it
            Point neighborPoint1 = this->points.at(currentNeighborsVector.at(j).getId() - 1);
            Vector<Neighbors> neighborsVector1;
            this->graph.find(neighborPoint1, neighborsVector1);


            for (int k = j + 1; k < this->K; k++) {

                //find max distance of neighbors
                neighborsVector1.sort();
                float maxDistance1 = neighborsVector1.at(this->K - 1).getDistance();

                Point neighborPoint2 = this->points.at(currentNeighborsVector.at(k).getId() - 1);
                Vector<Neighbors> neighborsVector2;
                this->graph.find(neighborPoint2, neighborsVector2);

                //find max distance of neighbors
                neighborsVector2.sort();
                float maxDistance2 = neighborsVector2.at(this->K - 1).getDistance();

                if(checkDuplicate(neighborsVector1, neighborsVector2,j ,k)){
                    continue;
                }

                float dist;
                if (strcmp(this->metrics, "manhattan") == 0) {
                    dist = Metrics::manhattanDistance(neighborPoint1.getCoordinates(),
                                                      neighborPoint2.getCoordinates(),
                                                      this->dimensions);
                } else {
                    dist = Metrics::euclideanDistance(neighborPoint1.getCoordinates(),
                                                      neighborPoint2.getCoordinates(),
                                                      this->dimensions);
                }
                //put neighbor point 2 to point 1
                if (dist < maxDistance1) {
                    Neighbors tempNeighbor(neighborPoint2.getId(), dist, neighborPoint2.getCoordinates());
                    neighborsVector1.at(this->K - 1) = tempNeighbor;
                    neighborsVector1.sort();
                    tempGraph.insert(neighborPoint1, neighborsVector1);
                    tempPointVector.push_back(neighborPoint1);
                    count++;
                }
                //put neighbor point 1 to point 2
                if (dist < maxDistance2) {
//                    printf("ok2\n");
                    Neighbors tempNeighbor(neighborPoint1.getId(), dist, neighborPoint1.getCoordinates());
                    neighborsVector2.at(this->K - 1) = tempNeighbor;
                    neighborsVector2.sort();
                    tempGraph.insert(neighborPoint2, neighborsVector2);
                    tempPointVector.push_back(neighborPoint2);
                    count++;
                }

            }
        }
        //for every new neighbor vector of points
        for(int p=0;p<count;p++){
            Vector<Neighbors> neighborsV;
            tempGraph.find(tempPointVector.at(p),neighborsV);
            //replace the Point with the new neighbor vector
            this->graph.insert(tempPointVector.at(p), neighborsV);
            flag = 1;
        }
    }
    return flag;

}