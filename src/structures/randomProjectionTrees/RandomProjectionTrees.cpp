#include "../../../headers/structures/randomProjectionTrees/RandomProjectionTrees.h"

void RandomProjectionTrees::printTree(){
    for(int k=0;k<trees.getSize();k++){
        printf("Tree %d\n", trees.at(k).id);
        for(int i=0;i<trees.at(k).tree.getSize();i++){
            for(int j=0;j<trees.at(k).tree.at(i).getSize();j++){
                printf("%d ",trees.at(k).tree.at(i).at(j));
            }
            printf("\n");
        }
    }
}

float RandomProjectionTrees::calculateInnerProduct(Vector<float> vector1, Vector<float> vector2){
    float innerProduct = 0.0f;
    for (int i = 0; i < dimensions; i++){
        innerProduct += vector1.at(i) * vector2.at(i);
    }
    return innerProduct;
}

Vector<Vector<int> > RandomProjectionTrees::hyperplane(Vector<int> branchPoints) {
    Vector<int> leftTree;
    Vector<int> rightTree;

    //find 2 random points
    int randNum1;
    int randNum2;
    randNum1 = branchPoints.at(rand() % branchPoints.getSize());
    randNum2 = branchPoints.at(rand() % branchPoints.getSize());
    if(randNum1 == randNum2){
        while(randNum1 == randNum2){
            randNum2 = branchPoints.at(rand() % branchPoints.getSize());
        }
    }

    //find midpoint
    Vector<float> midPoint;
    Vector<float> hyperplaneVector;
    for (int i = 0; i < dimensions; i++){
        float temp1 = points.at(randNum1-1).getCoordinates().at(i);
        float temp2 = points.at(randNum2-1).getCoordinates().at(i);
        float midTemp = (temp1 + temp2) / 2;
        midPoint.push_back(midTemp);

        //find hyperplane
        float hyperplaneTemp = temp1 - temp2;
        hyperplaneVector.push_back(hyperplaneTemp);
    }
    //calculate offset
    float offset = calculateInnerProduct(hyperplaneVector, midPoint);

    //find distance of each point from hyperplane
    for(int i=0;i<branchPoints.getSize();i++){
        //find point position
        int pos = branchPoints.at(i);
        float distance = calculateInnerProduct(hyperplaneVector, points.at(pos-1).getCoordinates());
        distance-= offset;


        if(distance < -EPS){
            leftTree.push_back(pos);
        }
        else if(distance > EPS){
            rightTree.push_back(pos);
        }
        else if(distance == 0){
            //randomly assign to left or right
            int randNum = rand() % 2;
            if(randNum == 0){
                leftTree.push_back(pos);
            }
            else{
                rightTree.push_back(pos);
            }
        }
    }
    //if all points are on one side
    if(rightTree.getSize() == 0 || leftTree.getSize() == 0){
        //assign to left or right randomly
        for(int i=0;i<branchPoints.getSize();i++){
            int pos = branchPoints.at(i);
            int randNum = rand() % 2;
            if(randNum == 0){
                leftTree.push_back(pos);
            }
            else{
                rightTree.push_back(pos);
            }
        }

    }
    //return rightTree and leftTree
    Vector<Vector<int> > returnVector;
    returnVector.push_back(leftTree);
    returnVector.push_back(rightTree);
    return returnVector;
}

int RandomProjectionTrees::split(Vector<int> branchPoints, Vector<Vector<int> > &currentTree){
    srand(static_cast<unsigned>(time(nullptr)));

    //check if branchPoints size is less than D
    if(branchPoints.getSize() <= D){
        //create leaf node
        currentTree.push_back(branchPoints);
        return 0;
    }

    Vector<Vector<int> > hyperplaneVector = hyperplane(branchPoints);
    Vector<int> leftTree = hyperplaneVector.at(0);
    split(leftTree,currentTree);
    Vector<int> rightTree = hyperplaneVector.at(1);
    split(rightTree, currentTree);

}

RandomProjectionTrees::RandomProjectionTrees(int d):D(d){}

void RandomProjectionTrees::putPoints(Vector<float> coordinates){
    Point point(numOfPoints+1,coordinates);
    points.push_back(point);
    numOfPoints++;
}

void RandomProjectionTrees::initGraph(){
//    srand(time(NULL));

    Vector<int> branchPoints;
    for(int i=0;i<numOfPoints;i++){
        branchPoints.push_back(i+1);
    }
    int treeCount = 0;
    Vector<Vector<int> > tempTree;
    split(branchPoints, tempTree);
    treeCount++;
    trees.push_back(TreeContents{treeCount,tempTree});

    for(int i=0;i<trees.getSize();i++) {
        graphInitialization(trees.at(i).tree);
    }

}


void RandomProjectionTrees::graphInitialization(Vector<Vector<int> > tempTree){
    //for each leaf
    for(int i=0;i<tempTree.getSize();i++){
        //for each point in leaf
        for(int j=0;j<tempTree.at(i).getSize();j++){
            Point firstPoint = points.at(tempTree.at(i).at(j)-1);
            //for each other point in leaf
            for(int k=0;k<tempTree.at(i).getSize();k++){
                Point secondPoint = points.at(tempTree.at(i).at(k)-1);
                if(j != k) {

                    //calculate distance
                    float distance = calculateDistance(firstPoint, secondPoint);


                    Vector<Neighbors> neighborsList1;
                    Vector<Neighbors> neighborsList2;
                    graph.find(firstPoint, neighborsList1);
                    graph.find(secondPoint, neighborsList2);

                    int check = checkDuplicate(firstPoint, secondPoint, neighborsList1, neighborsList2);
                    if (check) {
                        continue;
                    }
                    if (neighborsList1.getSize() == K) {
                        //sort neighborsList1
                        neighborsList1.sort();
                        //find max distance
                        float maxDist = neighborsList1.at(K - 1).getDistance();
                        //check if second point is closer than max distance
                        if (distance < maxDist) {
                            //if yes, replace max distance with second point
                            Neighbors newNeighbor(secondPoint.getId(), distance, secondPoint.getCoordinates());
                            neighborsList1.at(K - 1) = newNeighbor;
                            graph.insert(firstPoint, neighborsList1);
                        }
                    } else {
                        Neighbors newNeighbor(secondPoint.getId(), distance, secondPoint.getCoordinates());
                        neighborsList1.push_back(newNeighbor);
                        graph.insert(firstPoint, neighborsList1);
                    }

                    if (neighborsList2.getSize() == K) {
                        //sort neighborsList2
                        neighborsList2.sort();
                        //find max distance
                        float maxDist = neighborsList2.at(K - 1).getDistance();
                        //check if second point is closer than max distance
                        if (distance < maxDist) {
                            //if yes, replace max distance with second point
                            Neighbors newNeighbor(firstPoint.getId(), distance, firstPoint.getCoordinates());
                            neighborsList2.at(K - 1) = newNeighbor;
                            graph.insert(secondPoint, neighborsList2);
                        }
                    } else {
                        Neighbors newNeighbor(firstPoint.getId(), distance, firstPoint.getCoordinates());
                        neighborsList2.push_back(newNeighbor);
                        graph.insert(secondPoint, neighborsList2);
                    }

                }
            }
        }
    }
    fillGraph();
}

void RandomProjectionTrees::fillGraph() {
    for(int k=0;k<numOfPoints;k++) {
        Vector<Neighbors> neighborsVector;
        Point currentPoint = points.at(k);
        graph.find(currentPoint, neighborsVector);
        for (int i = neighborsVector.getSize(); i <= K; i++) {
            int randomNum;
            int loopFlag = 1;
            while (loopFlag) {
                loopFlag = 0;
                //generate random num
                randomNum = (rand() % (this->numOfPoints)) + 1;

                //if num is already in tree, generate another
                int check = checkDuplicate(currentPoint, points.at(randomNum - 1), neighborsVector, neighborsVector);
                if (check) {
                    loopFlag = 1;
                }
            }
            Point secondPoint = points.at(randomNum - 1);

            float dist = calculateDistance(currentPoint, secondPoint);

            Neighbors newNeighbor(secondPoint.getId(), dist, secondPoint.getCoordinates());
            neighborsVector.push_back(newNeighbor);
            graph.insert(currentPoint, neighborsVector);
        }
    }
}