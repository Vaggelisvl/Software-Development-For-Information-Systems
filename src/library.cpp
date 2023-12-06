#include <fstream>
#include <ctime>
#include "../headers/structures/vector/Vector.h"
#include "../headers/structures/point/Point.h"
#include "../headers/structures/graph/GraphInitialization.h"
#include "../headers/structures/graph/Optimizations.h"
#include "../headers/structures/Dataset.h"
#include "../headers/utils/Statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int main(int argc, char *argv[]) {

    if(argc != 7){
        printf("wrong input\n");
        return 0;
    }
    //./name inputFile dimensions numOfPoints K queryId metrics
    char* inputFile = argv[1];
    int dimensions = atoi(argv[2]);
    int numOfPoints = atoi(argv[3]);
    int K = atoi(argv[4]);
    int queryId = atoi(argv[5]);
    char* metrics = argv[6];

    char buffer[50];
    LOG_INFO(buffer);
    sprintf(buffer, "argc: %d\n", argc);


    Dataset dataset(inputFile, numOfPoints, dimensions);

    Vector<Point> elements;
    dataset.readVectorFromFile(elements);

    //initialize graph, put points, set K, initialize random k neighbors...
    GraphInitialization g;
    for(int i=0;i<dataset.getNumOfPoints();i++){
        g.putPoints(elements.at(i).getCoordinates());
    }

    g.setK(K);
    g.setMetrics(metrics);
    g.setDimensions(dataset.getDimensions());
    g.setKRandomNeighbors();

    Statistics* statistics=new Statistics(elements,dataset.getNumOfPoints(),dataset.getDimensions());
    statistics->calculateAllDistances(metrics);

    //if query out of the graph
    if(queryId == dataset.getNumOfPoints() + 1){
        srand(static_cast<unsigned>(time(NULL)));
        Vector<float> queryVector;
        //generate random coordinates
        for (int i = 0; i < dataset.getDimensions(); i++) {
//          in space [-1.0-1.0]
            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
            queryVector.push_back(randomFloat);
        }
        Point queryPoint(queryId,queryVector);
        g.findKNearestNeighborsForPoint(queryPoint);
//        g.calculateAllDistances();

    }
    else{
        g.sortKNeighbors();
        while(!g.KNNAlgorithm());
        g.printNeighbors(queryId);
        g.printGraph("graph.txt");
    }


    statistics->calculateStatistics(K,&g);
    if(numOfPoints>20)
        statistics->printStatistics(K);
    else
        statistics->printInMatrixForm(K);

    statistics->printTotalPercentage(K);


    //for project 2
    printf("OPTIMIZATIONS\n");
    Optimizations op;
    for(int i=0;i<dataset.getNumOfPoints();i++){
        op.putPoints(elements.at(i).getCoordinates());
    }

    op.setK(K);
    op.setMetrics(metrics);
    op.setDimensions(dataset.getDimensions());
    op.setd(0.1);
    op.setKRandomNeighbors();
    op.initFlags();
    op.sortKNeighbors();

    //if query out of the graph
    if(queryId == dataset.getNumOfPoints() + 1){
        srand(static_cast<unsigned>(time(NULL)));
        Vector<float> queryVector;
        //generate random coordinates
        for (int i = 0; i < dataset.getDimensions(); i++) {
//          in space [-1.0-1.0]
            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
            queryVector.push_back(randomFloat);
        }
        Point queryPoint(queryId,queryVector);
        op.findKNearestNeighborsForPoint(queryPoint);

    }
    else{
        op.sortKNeighbors();
        while(op.KNN());
        op.printNeighbors(queryId);
    }
    Statistics* statistics2 = new Statistics(elements,dataset.getNumOfPoints(),dataset.getDimensions());
    statistics2->calculateAllDistances(metrics);

    op.printGraph("optimizedGraph.txt");


    statistics2->calculateStatistics(K,&op);
    if(numOfPoints>20)
        statistics2->printStatistics(K);
    else
        statistics2->printInMatrixForm(K);

    statistics2->printTotalPercentage(K);

}