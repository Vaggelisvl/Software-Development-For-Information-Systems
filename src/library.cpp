#include <iostream>
#include <fstream>

#include "../headers/structures/vector/Vector.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/point/Point.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/GraphInitialization.h"
#include "../headers/structures/Dataset.h"

#include "../src/structures/vector/Vector.cpp"
#include "../src/structures/unorderedMap/UnorderedMap.cpp"
#include "../src/structures/point/Point.cpp"
#include "../src/config/Logger.cpp"
#include "../src/structures/GraphInitialization.cpp"



using namespace std;
int main(int argc, char *argv[]) {

    char* inputFile = argv[1];
    int dimensions = atoi(argv[2]);
    int numOfPoints = 0;
    std::cout<<"argc"<<argc<<endl;
    for (int i=0;i<argc;i++)
        std::cout<<"argv "<<i<<"value :"<<argv[i]<<endl;

    if(argc > 3){
        numOfPoints = atoi(argv[3]);
    }

    Dataset dataset(inputFile, numOfPoints, dimensions);
    cout<<dataset.getFilename()<<endl;

    Vector<Point> elements;
    dataset.readVectorFromFile(elements);

//    std::cout<<dataset.getNumOfPoints()<<std::endl;
//    std::cout<<" num"<<dataset.getNumOfPoints()<<endl;
//    for(int i=0;i<dataset.getNumOfPoints();i++){
//        cout<<"\n\n\n\n"<<endl;
//        cout<<"vector element: "<<elements.at(i).getId()<<endl;
//    }

    //initialize graph, put points, set K, initialize random k neighbors
    GraphInitialization g;
    for(int i=0;i<dataset.getNumOfPoints();i++){
        g.putPoints(elements.at(i).getCoordinates());
    }
    g.initializeK();
    cout<<"numofpoint="<<g.getNumOfPoints()<<endl;
    g.setKRandomNeighbors();
    cout<<"FINISH WITH RANDOM"<<endl;
    g.sortKNeighbors();
    while(!g.KNNAlgorithm());
}