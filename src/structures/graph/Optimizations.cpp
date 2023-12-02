#include "../../../headers/structures/graph/Optimizations.h"

bool NeighborList::operator<(const NeighborList& other) const
{
    return this->neighbor.getDistance()<other.neighbor.getDistance();
}

bool NeighborList::operator==(const NeighborList& other) const
{
   return  this->neighbor.getId() == other.neighbor.getId() && this->neighbor.getDistance() == other.neighbor.getDistance();

}

int Optimizations::checkDuplicate(NeighborList point1, NeighborList point2, Vector<NeighborList> neighborsList1, Vector<NeighborList> neighborsList2){
    if(point1.neighbor.getId() == point2.neighbor.getId()){
        return 1;
    }

    //if extended neighbor exist in the neighbor list
    for (int l = 0; l < this->K; l++) {
        if (neighborsList1.at(l).neighbor.getId() == point2.neighbor.getId()) {
            return 1;
        }
        if(neighborsList2.at(l).neighbor.getId() == point1.neighbor.getId()) {
            return 1;
        }
    }
    return 0;
}

int Optimizations::checkRandomNum(Vector<NeighborList> NeighborListArg, int randNum, int currentPointId) {
    int flag = 0;

    for (int p = 0; p < NeighborListArg.getSize(); p++) {
        //if num already in the neighbor list
        if (NeighborListArg.at(p).neighbor.getId() == randNum) {
            flag = 1;
            break;
        }

    }
    //find reverse neighbor vector from point(currentPoint)
    Vector<NeighborList> neighborCheckList;
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
        Vector<NeighborList> neighborListArg;
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
                    int hashNum = hashingDuplicateDistances(currentPoint, this->points.at(p));
                    if (hashNum == 0) {

                        if (strcmp(this->metrics, "manhattan") == 0) {
                            distance = Metrics::manhattanDistance(currentPoint.getCoordinates(),
                                                              this->points.at(p).getCoordinates(),
                                                              this->dimensions);
                        }
                        else {
                            distance = Metrics::euclideanDistance(currentPoint.getCoordinates(),
                                                              this->points.at(p).getCoordinates(),
                                                              this->dimensions);
                        }
                        //put dist in to the hashMap
                        DistanceContents newHashNum;
                        newHashNum.id = this->points.at(p).getId();
                        newHashNum.dist = distance;
                        this->hashMap.insert(currentPoint, newHashNum);
                        this->counter++;
                    }
                    else {
                        //if distance already exist in the hashMap
                        DistanceContents content;
                        Point hashPoint = this->points.at(hashNum - 1);
                        this->hashMap.find(hashPoint, content);
                        distance = content.dist;
                    }

                    //init current point neighbor with flag true
                    Neighbors neighborsOfPoint(randomNum, distance, this->points.at(p).getCoordinates());
                    NeighborList neighborsOfPointArg;
                    neighborsOfPointArg.neighbor = neighborsOfPoint;
                    neighborsOfPointArg.flag = true;
                    neighborListArg.push_back(neighborsOfPointArg);

                    //find reverse neighbor from point(currentPoint)
                    Vector<NeighborList> reverseNeighborsList;
                    Point reversePoint = this->points.at(randomNum - 1);
                    this->graph.find(reversePoint, reverseNeighborsList);

                    //init neighbor reserve neighbor with flag true
                    Neighbors reverseNeighborsOfPoint(i + 1, distance, currentPoint.getCoordinates());
                    NeighborList reverseNeighborsOfPointArg;
                    reverseNeighborsOfPointArg.neighbor = reverseNeighborsOfPoint;
                    reverseNeighborsOfPointArg.flag = true;
                    reverseNeighborsList.push_back(reverseNeighborsOfPointArg);

                    //put neighbor reverse neighbor
                    reverseNeighborsList.sort();
                    this->graph.insert(reversePoint, reverseNeighborsList);
                    break;
                }
            }

        }
        neighborListArg.sort();
        this->graph.insert(currentPoint, neighborListArg);

    }

}

int Optimizations::incrementalSearch(NeighborList point1, NeighborList point2) {
    if(point1.flag || point2.flag){
        return 1;
    }
    else{
        return 0;
    }
}

int Optimizations::hashingDuplicateDistances(Point& point1, Point& point2) {
    DistanceContents hashNum;
    this->hashMap.find(point1, hashNum);
    if(hashNum.id == point2.getId()){
        return point1.getId();
    }
    this->hashMap.find(point2, hashNum);
    if(hashNum.id == point1.getId()){
        return point2.getId();
    }

    else{
        return 0;
    }

}

int Optimizations::localJoin() {
    printf("again\n");
    int repeatFlag = 0;

    //for every point in the graph
    for (int i = 0; i < this->numOfPoints; i++) {
        UnorderedMap<Point, Vector<NeighborList> > tempGraph;
        int count = 0;
        Vector<Point> tempPointVector;

        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<NeighborList> currentNeighborsList;
        this->graph.find(currentPoint, currentNeighborsList);


        //for every neighbor of the current point
        for (int j = 0; j < this->K; j++) {
            //find neighbor point with the neighbor vector of it
            Point neighborPoint1 = this->points.at(currentNeighborsList.at(j).neighbor.getId() - 1);
            Vector<NeighborList> neighborsList1;
            this->graph.find(neighborPoint1, neighborsList1);
            neighborsList1.sort();

            //for every second neighbor of the current point
            for (int k = 0; k < this->K; k++) {
                //find max distance of neighbors
                neighborsList1.sort();
                float maxDistance1 = neighborsList1.at(this->K - 1).neighbor.getDistance();

                Point neighborPoint2 = this->points.at(currentNeighborsList.at(k).neighbor.getId() - 1);
                Vector<NeighborList> neighborsList2;
                this->graph.find(neighborPoint2, neighborsList2);

                //find max distance of neighbors
                neighborsList2.sort();
                float maxDistance2 = neighborsList2.at(this->K - 1).neighbor.getDistance();

                if(checkDuplicate(currentNeighborsList.at(j),currentNeighborsList.at(k),neighborsList1, neighborsList2)){
                    continue;
                }

                //if neighbor1 or neighbor2 is new in the local join
//                if(incrementalSearch(currentNeighborsList.at(j), currentNeighborsList.at(k))) {
//                    printf("ok\n");

                    //neighbor1 and neighbor2 participate in the local join
                    currentNeighborsList.at(j).flag = false;
                    currentNeighborsList.at(k).flag = false;

                    float dist;
                    int hashNum = hashingDuplicateDistances(neighborPoint1, neighborPoint2);
                    if (hashNum == 0) {

                        if (strcmp(this->metrics, "manhattan") == 0) {
                            dist = Metrics::manhattanDistance(neighborPoint1.getCoordinates(),
                                                              neighborPoint2.getCoordinates(),
                                                              this->dimensions);
                        } else {
                            dist = Metrics::euclideanDistance(neighborPoint1.getCoordinates(),
                                                              neighborPoint2.getCoordinates(),
                                                              this->dimensions);
                        }
                        //put dist in to the hashMap
                        DistanceContents newHashNum;
                        newHashNum.id = neighborPoint2.getId();
                        newHashNum.dist = dist;
                        this->hashMap.insert(neighborPoint1, newHashNum);

                    }
                    else {
                        DistanceContents content;
                        Point hashPoint = this->points.at(hashNum - 1);
                        this->hashMap.find(hashPoint, content);
                        dist = content.dist;
                    }
                    this->counter++;
                    printf("point1=%d point2=%d dist=%f\n",neighborPoint1.getId(),neighborPoint2.getId(),dist);

                    //put neighbor point 2 to point 1
                    if (dist < maxDistance1) {
                        Neighbors tempNeighbor(neighborPoint2.getId(), dist, neighborPoint2.getCoordinates());
                        neighborsList1.at(this->K - 1).neighbor = tempNeighbor;
                        neighborsList1.at(this->K - 1).flag = true;
                        neighborsList1.sort();
                        tempGraph.insert(neighborPoint1, neighborsList1);
                        tempPointVector.push_back(neighborPoint1);
                        count++;
                    }
                    //put neighbor point 1 to point 2
                    if (dist < maxDistance2) {
                        Neighbors tempNeighbor(neighborPoint1.getId(), dist, neighborPoint1.getCoordinates());
                        neighborsList2.at(this->K - 1).neighbor = tempNeighbor;
                        neighborsList2.at(this->K - 1).flag = true;
                        neighborsList2.sort();
                        tempGraph.insert(neighborPoint2, neighborsList2);
                        tempPointVector.push_back(neighborPoint2);
                        count++;
                    }
//                }

            }
        }
        //for every new neighbor vector of points
        for(int p=0;p<count;p++){
            Vector<NeighborList> neighborsV;
            tempGraph.find(tempPointVector.at(p),neighborsV);
            //replace the Point with the new neighbor vector
            this->graph.insert(tempPointVector.at(p), neighborsV);
            repeatFlag = 1;
        }
    }
    return repeatFlag;

}

void Optimizations::printdup(){
    printf("this->hashMap.getSize()=%d\n",this->counter);
}


void Optimizations::printGraph() {
    FILE *file;
    file = fopen("optimizedGraph.txt", "w");
    for (int i = 0; i < this->numOfPoints; ++i) {
        Vector<NeighborList> neighborsListArg;
        //print graph
        fprintf(file, "point: %d{\n", i+1);
        for (int j = 0; j < this->K; j++) {
            this->graph.find(this->points.at(i), neighborsListArg);
            char buffer[100]; // Adjust the buffer size as needed
            int neighborId = neighborsListArg.at(j).neighbor.getId();
            float neighborDistance = neighborsListArg.at(j).neighbor.getDistance();
            fprintf(file,"point: %d", neighborId);
            fprintf(file," distance: %f\n", neighborDistance);
//            LOG_INFO(buffer);

        }
        fprintf(file, "\n}\n");
    }
    fclose(file);
}

