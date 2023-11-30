#include "../../../headers/structures/graph/GraphInitialization.h"

GraphInitialization::GraphInitialization() : numOfPoints(0), K(-1), dimensions(0) {
}

void GraphInitialization::putPoints(Vector<float> coordinates) {
    Point currentPoint;
    currentPoint.setId(++this->numOfPoints);
    currentPoint.setCoordinates(coordinates);

    this->points.push_back(currentPoint);
    Vector<Neighbors> neighborsVector;
    this->graph.insert(currentPoint, neighborsVector);
}

void GraphInitialization::setDimensions(int num){
    this->dimensions = num;
}


int GraphInitialization::getNumOfPoints() {
    return this->numOfPoints;
}

void GraphInitialization::setMetrics(char* nameOfMetrics) {
    this->metrics = nameOfMetrics;
}

int GraphInitialization::checkRandomNum(Vector<Neighbors> neighborsVector, int randNum, int currentPointId) {
    int flag = 1;

    for (int p = 0; p < neighborsVector.getSize(); p++) {
        //if num already in the neighbor list
        if (neighborsVector.at(p).getId() == randNum) {
            flag = 0;
            break;
        }

    }
    //find reverse neighbor vector from point(currentPoint)
    Vector<Neighbors> neighborCheckVector;
    Point reverseCheckPoint = this->points.at(randNum - 1);
    this->graph.find(reverseCheckPoint, neighborCheckVector);

    //if reverse neighbor list is full
    if (neighborCheckVector.getSize() == this->K) {
        flag = 0;
    }

    return !flag;
}

void GraphInitialization::printGraph() {
    FILE *file;
    file = fopen("graph.txt", "w");
    for (int i = 0; i < this->numOfPoints; ++i) {
        Vector<Neighbors> neighborsVector;
        //print graph
        fprintf(file, "point: %d{\n", i+1);
        for (int j = 0; j < this->K; j++) {
            this->graph.find(this->points.at(i), neighborsVector);
            char buffer[100]; // Adjust the buffer size as needed
            int neighborId = neighborsVector.at(j).getId();
            float neighborDistance = neighborsVector.at(j).getDistance();
            fprintf(file,"point: %d", neighborId);
            fprintf(file," distance: %f\n", neighborDistance);
//            LOG_INFO(buffer);

        }
        fprintf(file, "\n}\n");
    }
    fclose(file);
}

void GraphInitialization::printNeighbors(int id) {
    Point point = this->points.at(id - 1);
    Vector<Neighbors> neighborsVector;
    this->graph.find(point, neighborsVector);
    printf("%d nearest neighbors of Point %d:\n", this->K, id);
    for (int i = 0; i < this->K; i++) {
        printf("neighbor with id:%d     %f\n", neighborsVector.at(i).getId(),neighborsVector.at(i).getDistance());
    }
}

void GraphInitialization::setKRandomNeighbors() {
    srand(static_cast<unsigned>(time(nullptr)));

    //for every point
    for (int i = 0; i < this->numOfPoints; i++) {
        int randomNum;
        Vector<Neighbors> neighborsVector;
        Point currentPoint = this->points.at(i);
        this->graph.find(currentPoint, neighborsVector);

        int neighborCapacity = this->K - neighborsVector.getSize();
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
                loopFlag = checkRandomNum(neighborsVector, randomNum, i + 1);

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

void GraphInitialization::sortKNeighbors() {
    for (int i = 0; i < this->numOfPoints; i++) {
        //find current point with the neighbor vector of it
        Point currentPoint = this->points.at(i);
        Vector<Neighbors> neighborsVector;
        this->graph.find(currentPoint, neighborsVector);

        neighborsVector.sort();
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
                for (int l = 0; l < this->K; l++) {
                    if (neighborsVector.at(l).getId() == extendedNeighborsVector.at(p).getId()) {
                        exist = 1;
                    }
                }
                if (exist) {
                    continue;
                }

                float extendedDistance;
                if(strcmp(this->metrics, "manhattan") == 0) {
                    extendedDistance = Metrics::manhattanDistance(currentPoint.getCoordinates(),
                                                          extendedNeighborsVector.at(p).getCoordinates(),
                                                          this->dimensions);
                }
                else{
                    extendedDistance = Metrics::euclideanDistance(currentPoint.getCoordinates(),
                                                          extendedNeighborsVector.at(p).getCoordinates(),
                                                          this->dimensions);
                }

                //if is closer to current point
                if (maxNeighborDistance > extendedDistance) {

                    if (neighborsVector.at(j).getDistance() == extendedNeighborsVector.at(p).getDistance()) {
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

    if (flag) {
        return 0;
    }

    this->sortKNeighbors();
    LOG_INFO("FINISH ALGORITHM");
    return 1;

}


void GraphInitialization::findKNearestNeighborsForPoint(const Point &queryPoint) {
    srand(time(nullptr));
    Vector<Neighbors> uniqueNumbers;
    int randomNumber;
    int flag;
    //generate K random neighbors for query point
    for (int i = 0; i < this->K; i++) {
        flag = 1;
        while (flag) {
            flag = 0;
            randomNumber = (rand() % this->numOfPoints) + 1;
            for (int j = 0; j < i; j++) {
                if (uniqueNumbers.at(j).getId() == randomNumber) {
                    flag = 1;
                    break;
                }
            }
        }

        //convert point to neighbor
        Point neighborPoint = this->points.at(randomNumber - 1);
        float dist;
        if(strcmp(this->metrics, "manhattan") == 0) {
            dist = Metrics::manhattanDistance(neighborPoint.getCoordinates(), queryPoint.getCoordinates(),
                                                          this->dimensions);
        }
        else{
            dist = Metrics::euclideanDistance(neighborPoint.getCoordinates(), queryPoint.getCoordinates(),
                                                          this->dimensions);
        }

        Neighbors neighbor(neighborPoint.getId(), dist, neighborPoint.getCoordinates());

        uniqueNumbers.push_back(neighbor);
    }
    //insert query point to the graph
    this->graph.insert(queryPoint, uniqueNumbers);
    this->points.push_back(queryPoint);
    this->numOfPoints++;

    sortKNeighbors();
    printGraph();
    while (!KNNAlgorithm());
    calculateAllDistances();
    sortKNeighbors();

    //remove query point from the graph
    printNeighbors(queryPoint.getId());
    this->graph.remove(queryPoint);
    this->points.remove(queryPoint);
    this->numOfPoints--;
}

UnorderedMap<Point, Vector<Neighbors>> GraphInitialization::getGraph() {
    return this->graph;
}

Point GraphInitialization::getPoint(int id) {
    return this->points.at(id - 1);
}

int GraphInitialization::getK() {
    return this->K;
}

Vector<Point> GraphInitialization::getPoints() {
    return this->points;
}

Vector<Neighbors> GraphInitialization::getNeighborsOfPoint(Point point) {
    return graph.get(point);
}

void GraphInitialization::setK(int k) {
    this->K = k;

}

void GraphInitialization::calculateAllDistances() {
    printf("calculate all distances\n");
    PointInfo **pointInfo;
    pointInfo = new PointInfo *[numOfPoints];
    printf("calculate all  \n");
    for (int i = 0; i < numOfPoints; i++) {
        Point point = points.at(i);
        pointInfo[i] = new PointInfo(point.getId(), numOfPoints);
        for (int j = 0; j < numOfPoints; j++) {

            Point point1 = points.at(j);
            float dist;
            if(this->metrics == "manhattan\n") {
                dist = Metrics::manhattanDistance(point.getCoordinates(), point1.getCoordinates(),
                                                  this->dimensions);
            }
            else{
                dist = Metrics::euclideanDistance(point.getCoordinates(), point1.getCoordinates(),
                                                  this->dimensions);
            }
            pointInfo[i]->insert(point1.getId(),dist);
        }
    }
    printf("calculate all distances 1 \n");
    FILE *file;
    file = fopen("results.txt", "w");
    if(file == nullptr){
        LOG_ERROR("Cannot open results.txt file");
        exit(1);
    }

    for (int i = 0; i < numOfPoints; i++) {
        fprintf(file, "point: %d{\n", pointInfo[i]->getId());
        pointInfo[i]->sortDistances();
        //print 20 nearest neighbors points
        for(int j=0;j<pointInfo[i]->getPointsInserted();j++){
            if(fprintf(file,"point: %d", pointInfo[i]->getNeighborId(j))<0){
                LOG_ERROR("Cannot write point to results.txt file");
                exit(1);
            }

            if(fprintf(file," distance: %f\n", pointInfo[i]->getDistance(j))<0){
                LOG_ERROR("Cannot write distance to results.txt file");
                exit(1);
            }


        }
        fprintf(file, "\n}\n");
    }
    fclose(file);
}




