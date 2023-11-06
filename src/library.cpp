#include <fstream>

#include "../headers/structures/vector/Vector.h"
#include "../headers/structures/point/Point.h"
#include "../headers/structures/graph/GraphInitialization.h"
#include "../headers/structures/Dataset.h"




using namespace std;
int main(int argc, char *argv[]) {

    char* inputFile = argv[1];
    int dimensions = atoi(argv[2]);
    int numOfPoints = 0;
    char buffer[50];
    sprintf(buffer, "argc: %d\n", argc);
    LOG_INFO(buffer);

    if(argc > 3){
        numOfPoints = atoi(argv[3]);
    }

    Dataset dataset(inputFile, numOfPoints, dimensions);

    Vector<Point> elements;
    dataset.readVectorFromFile(elements);


    //initialize graph, put points, set K, initialize random k neighbors
    GraphInitialization g;
    for(int i=0;i<dataset.getNumOfPoints();i++){
        g.putPoints(elements.at(i).getCoordinates());
    }
    g.initializeK();
    g.initializeDimensions(dataset.getDimensions());
    g.setKRandomNeighbors();
//    g.calculateAllDistances();
    g.sortKNeighbors();
    while(!g.KNNAlgorithm());

    int randQuery = (rand() % (dataset.getNumOfPoints())) + 2;
    //if query out of the graph
    if(randQuery == dataset.getNumOfPoints() + 1){
        srand(static_cast<unsigned>(time(nullptr)));
        Vector<float> queryVector;
        //generate random coordinates
        for (int i = 0; i < dataset.getDimensions(); i++) {
//          in space [-1.0-1.0]
            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
            queryVector.push_back(randomFloat);
        }
        Point queryPoint(randQuery,queryVector);
        g.findKNearestNeighborsForPoint(queryPoint);
    }
    else{
        g.sortKNeighbors();
        while(!g.KNNAlgorithm());
        g.printNeighbors(randQuery);

    }
}