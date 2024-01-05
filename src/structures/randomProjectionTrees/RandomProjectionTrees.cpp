#include "../../../headers/structures/randomProjectionTrees/RandomProjectionTrees.h"

void RandomProjectionTrees::printTree(){
    for(int i=0;i<tree.getSize();i++){
        for(int j=0;j<tree.at(i).getSize();j++){
            printf("%d ",tree.at(i).at(j));
        }
        printf("\n");
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

int RandomProjectionTrees::split(Vector<int> branchPoints){
    //check if branchPoints size is less than D
    if(branchPoints.getSize() <= D){
        //create leaf node
        tree.push_back(branchPoints);
        return 0;
    }

    Vector<Vector<int> > hyperplaneVector = hyperplane(branchPoints);
    Vector<int> leftTree = hyperplaneVector.at(0);
    split(leftTree);
    Vector<int> rightTree = hyperplaneVector.at(1);
    split(rightTree);

}

RandomProjectionTrees::RandomProjectionTrees(int d, int dim):D(d),dimensions(dim),numOfPoints(0){}

void RandomProjectionTrees::putPoints(Vector<float> coordinates){
    Point point(numOfPoints+1,coordinates);
    points.push_back(point);
    numOfPoints++;
}

void RandomProjectionTrees::initGraph(){
    Vector<int> branchPoints;
    for(int i=0;i<numOfPoints;i++){
        branchPoints.push_back(i+1);
    }
    split(branchPoints);
}