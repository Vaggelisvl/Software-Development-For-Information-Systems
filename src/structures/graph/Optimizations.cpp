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