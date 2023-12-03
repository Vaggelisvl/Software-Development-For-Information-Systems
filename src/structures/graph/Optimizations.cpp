#include "../../../headers/structures/graph/Optimizations.h"

//bool Neighbors::operator<(const Neighbors& other) const
//{
//    return this->neighbor.getDistance()<other.neighbor.getDistance();
//}
//
//bool Neighbors::operator==(const Neighbors& other) const
//{
//   return  this->neighbor.getId() == other.neighbor.getId() && this->neighbor.getDistance() == other.neighbor.getDistance();
//
//}

int Optimizations::checkDuplicate(Neighbors point1, Neighbors point2, Vector<Neighbors> neighborsList1, Vector<Neighbors> neighborsList2){
    if(point1.getId() == point2.getId()){
        return 1;
    }

    //if extended neighbor exist in the neighbor list
    for (int l = 0; l < this->K; l++) {
        if (neighborsList1.at(l).getId() == point2.getId()) {
            return 1;
        }
        if(neighborsList2.at(l).getId() == point1.getId()) {
            return 1;
        }
    }
    return 0;
}

int Optimizations::incrementalSearch(int pointId1, int pointId2, int currentPointId) {
    bool flag1;
    bool flag2;
    //find flag from point1 int the current local join
    Vector<incrementalSearchContents> localJoinParticipationVector;
    this->incrementalSearchMap.find(this->points.at(pointId1-1), localJoinParticipationVector);
    int size = localJoinParticipationVector.getSize();
    for(int i=0;i<size;i++){
        if(localJoinParticipationVector.at(i).id == currentPointId){
            flag1 = localJoinParticipationVector.at(i).flag;
            break;
        }
    }
    //find flag from point2 in the current local join
    this->incrementalSearchMap.find(this->points.at(pointId2-1), localJoinParticipationVector);
    size = localJoinParticipationVector.getSize();
    for(int i=0;i<size;i++){
        if(localJoinParticipationVector.at(i).id == currentPointId){
            flag2 = localJoinParticipationVector.at(i).flag;
            break;
        }
    }
    if(flag1 || flag2){
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

void Optimizations::initFlags() {
    for(int i=0;i<this->numOfPoints;i++){
        Vector<incrementalSearchContents> localJoinParticipationVector;
        this->incrementalSearchMap.find(this->points.at(i), localJoinParticipationVector);
        for(int j=0;j<localJoinParticipationVector.getSize();j++){
            localJoinParticipationVector.at(j).flag = true;
            localJoinParticipationVector.push_back(localJoinParticipationVector.at(j));
        }
        this->incrementalSearchMap.insert(this->points.at(i), localJoinParticipationVector);
    }
}

void Optimizations::changeFlag(int pointId, bool flag, int localJoinPointId){
    Vector<incrementalSearchContents> localJoinParticipationVector;
    this->incrementalSearchMap.find(this->points.at(pointId-1), localJoinParticipationVector);
    int size = localJoinParticipationVector.getSize();
    for(int i=0;i<size;i++){
        if(localJoinParticipationVector.at(i).id == localJoinPointId){
            localJoinParticipationVector.at(i).flag = flag;
            localJoinParticipationVector.push_back(localJoinParticipationVector.at(i));
            break;
        }
    }
    this->incrementalSearchMap.insert(this->points.at(pointId-1), localJoinParticipationVector);
}

void Optimizations::newParticipation(int pointId, int localJoinPointId){
    Vector<incrementalSearchContents> localJoinParticipationVector;
    this->incrementalSearchMap.find(this->points.at(pointId-1), localJoinParticipationVector);
    incrementalSearchContents newParticipation;
    newParticipation.id = localJoinPointId;
    newParticipation.flag = false;
    localJoinParticipationVector.push_back(newParticipation);
    this->incrementalSearchMap.insert(this->points.at(pointId-1), localJoinParticipationVector);
}

//void Optimizations::removeParticipation(int pointId, int localJoinPointId){
//    Vector<incrementalSearchContents> localJoinParticipationVector;
//    this->incrementalSearchMap.find(this->points.at(pointId-1), localJoinParticipationVector);
//    int size = localJoinParticipationVector.getSize();
//    for(int i=0;i<size;i++){
//        if(localJoinParticipationVector.at(i).id == localJoinPointId){
//            localJoinParticipationVector.remove(localJoinParticipationVector.at(i));
//            break;
//        }
//        this->incrementalSearchMap.insert(this->points.at(pointId-1), localJoinParticipationVector);
//}

int Optimizations::localJoin() {
    printf("again\n");
    int repeatFlag = 0;

    //for every point in the graph
    for (int i = 0; i < this->numOfPoints; i++) {
        UnorderedMap<Point, Vector<Neighbors> > tempGraph;
        int count = 0;
        Vector<Point> tempPointVector;

        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> currentNeighborsList;
        this->graph.find(currentPoint, currentNeighborsList);


        //for every neighbor of the current point
        for (int j = 0; j < this->K; j++) {
            //find neighbor point with the neighbor vector of it
            Point neighborPoint1 = this->points.at(currentNeighborsList.at(j).getId() - 1);
            Vector<Neighbors> neighborsList1;
            this->graph.find(neighborPoint1, neighborsList1);
            neighborsList1.sort();

            //for every second neighbor of the current point
            for (int k = 0; k < this->K; k++) {
                //find max distance of neighbors
                neighborsList1.sort();
                float maxDistance1 = neighborsList1.at(this->K - 1).getDistance();

                Point neighborPoint2 = this->points.at(currentNeighborsList.at(k).getId() - 1);
                Vector<Neighbors> neighborsList2;
                this->graph.find(neighborPoint2, neighborsList2);

                //find max distance of neighbors
                neighborsList2.sort();
                float maxDistance2 = neighborsList2.at(this->K - 1).getDistance();

                if(checkDuplicate(currentNeighborsList.at(j),currentNeighborsList.at(k),neighborsList1, neighborsList2)){
                    continue;
                }

                //if neighbor1 or neighbor2 is new in the local join
                if(incrementalSearch(currentNeighborsList.at(j).getId(), currentNeighborsList.at(k).getId(),currentPoint.getId())){
//                    printf("ok\n");

                    //neighbor1 and neighbor2 participate in the local join
                newParticipation(currentNeighborsList.at(j).getId(), currentPoint.getId());
                newParticipation(currentNeighborsList.at(k).getId(), currentPoint.getId());

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
//                    printf("point1=%d point2=%d dist=%f\n",neighborPoint1.getId(),neighborPoint2.getId(),dist);

                    //put neighbor point 2 to point 1
                    if (dist < maxDistance1) {
                        Neighbors tempNeighbor(neighborPoint2.getId(), dist, neighborPoint2.getCoordinates());
                        neighborsList1.at(this->K - 1) = tempNeighbor;
                        changeFlag(neighborPoint2.getId(),true,neighborPoint2.getId());
//                        neighborsList1.at(this->K - 1).flag = true;
                        neighborsList1.sort();
                        tempGraph.insert(neighborPoint1, neighborsList1);
                        tempPointVector.push_back(neighborPoint1);
                        count++;
                    }
                    //put neighbor point 1 to point 2
                    if (dist < maxDistance2) {
                        Neighbors tempNeighbor(neighborPoint1.getId(), dist, neighborPoint1.getCoordinates());
                        neighborsList2.at(this->K - 1) = tempNeighbor;
                        changeFlag(neighborPoint1.getId(),true,neighborPoint1.getId());
//                        neighborsList2.at(this->K - 1).flag = true;
                        neighborsList2.sort();
                        tempGraph.insert(neighborPoint2, neighborsList2);
                        tempPointVector.push_back(neighborPoint2);
                        count++;
                    }
                }

            }
        }
        //for every new neighbor vector of points
        for(int p=0;p<count;p++){
            Vector<Neighbors> neighborsV;
            tempGraph.find(tempPointVector.at(p),neighborsV);
            //replace the Point with the new neighbor vector
            this->graph.insert(tempPointVector.at(p), neighborsV);
            repeatFlag = 1;
        }
    }
    return repeatFlag;

}

//void Optimizations::findKNearestNeighborsForPoint(const Point &queryPoint) {
//    srand(time(nullptr));
//    Vector<Neighbors> uniqueNumbers;
//    int randomNumber;
//    int flag;
//    //generate K random neighbors for query point
//    for (int i = 0; i < this->K; i++) {
//        flag = 1;
//        while (flag) {
//            flag = 0;
//            randomNumber = (rand() % this->numOfPoints) + 1;
//            for (int j = 0; j < i; j++) {
//                if (uniqueNumbers.at(j).getId() == randomNumber) {
//                    flag = 1;
//                    break;
//                }
//            }
//        }
//
//        //convert point to neighbor
//        Point neighborPoint = this->points.at(randomNumber - 1);
//        float dist;
//        if(strcmp(this->metrics, "manhattan") == 0) {
//            dist = Metrics::manhattanDistance(neighborPoint.getCoordinates(), queryPoint.getCoordinates(),
//                                              this->dimensions);
//        }
//        else{
//            dist = Metrics::euclideanDistance(neighborPoint.getCoordinates(), queryPoint.getCoordinates(),
//                                              this->dimensions);
//        }
//
//        Neighbors neighbor(neighborPoint.getId(), dist, neighborPoint.getCoordinates());
//
//        uniqueNumbers.push_back(neighbor);
//        changeFlag(neighborPoint.getId(),true,queryPoint.getId());
//    }
//    //insert query point to the graph
//    this->graph.insert(queryPoint, uniqueNumbers);
//    this->points.push_back(queryPoint);
//    this->numOfPoints++;
//
////    sortKNeighbors();
//    printGraph();
//    while (!KNNAlgorithm());
//    calculateAllDistances();
////    sortKNeighbors();
//
//    //remove query point from the graph
//    printNeighbors(queryPoint.getId());
//    this->graph.remove(queryPoint);
//    this->points.remove(queryPoint);
//    this->numOfPoints--;
//}

void Optimizations::printdup(){
    printf("this->hashMap.getSize()=%d\n",this->counter);
}


//void Optimizations::printGraph() {
//    FILE *file;
//    file = fopen("optimizedGraph.txt", "w");
//    for (int i = 0; i < this->numOfPoints; ++i) {
//        Vector<Neighbors> neighborsListArg;
//        //print graph
//        fprintf(file, "point: %d{\n", i+1);
//        for (int j = 0; j < this->K; j++) {
//            this->graph.find(this->points.at(i), neighborsListArg);
//            char buffer[100]; // Adjust the buffer size as needed
//            int neighborId = neighborsListArg.at(j).neighbor.getId();
//            float neighborDistance = neighborsListArg.at(j).neighbor.getDistance();
//            fprintf(file,"point: %d", neighborId);
//            fprintf(file," distance: %f\n", neighborDistance);
////            LOG_INFO(buffer);
//
//        }
//        fprintf(file, "\n}\n");
//    }
//    fclose(file);
//}

