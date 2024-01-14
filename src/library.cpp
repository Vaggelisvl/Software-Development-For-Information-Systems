#include <fstream>
#include <ctime>
#include "../headers/structures/vector/Vector.h"
#include "../headers/structures/point/Point.h"
#include "../headers/structures/graph/GraphInitialization.h"
#include "../headers/structures/graph/Optimizations.h"
#include "../headers/structures/randomProjectionTrees/RandomProjectionTrees.h"
#include "../headers/structures/Dataset.h"
#include "../headers/utils/Statistics.h"
#include "../headers/structures/scheduler/JobScheduler.h"
#include "../headers/structures/scheduler/job/RandomProjectionTreeJob.h"
#include "../headers/structures/scheduler/job/NormCalculationJob.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printLogoFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];  // Adjust the size as needed
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open file: %s\n", filename);
    }
}

using namespace std;
int main(int argc, char *argv[]) {

    clock_t start = clock();
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
    // Seed the random number generator at the start of the program
    //to ensure that the sequence of random numbers generated during the program's execution is different each time we run the program,
    // but remains consistent during a single run of the program.
    srand(static_cast<unsigned>(time(NULL)));


    Dataset dataset(inputFile, numOfPoints, dimensions);

    Vector<Point> elements;
    dataset.readVectorFromFile(elements);


    //project 1
    //initialize graph, put points, set K, initialize random k neighbors...
//    GraphInitialization g;
//    for(int i=0;i<dataset.getNumOfPoints();i++){
//        g.putPoints(elements.at(i).getCoordinates());
//    }
//
//    g.setK(K);
//    g.setMetrics(metrics);
//    g.setDimensions(dataset.getDimensions());
//    g.setKRandomNeighbors();
//
//    Statistics* statistics=new Statistics(elements,dataset.getNumOfPoints(),dataset.getDimensions());
//    statistics->calculateAllDistances(metrics);
//
//    //if query out of the graph
//    if(queryId == dataset.getNumOfPoints() + 1){
//        srand(static_cast<unsigned>(time(NULL)));
//        Vector<float> queryVector;
//        //generate random coordinates
//        for (int i = 0; i < dataset.getDimensions(); i++) {
//            //in space [-1.0-1.0]
//            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
//            queryVector.push_back(randomFloat);
//        }
//        Point queryPoint(queryId,queryVector);
//        g.findKNearestNeighborsForPoint(queryPoint);
//
//    }
//    else{
//        g.sortKNeighbors();
//        while(!g.KNNAlgorithm());
//        g.calculateAllDistances();
//        g.printNeighbors(queryId);
//        g.printGraph("graph.txt");
//    }
//
//
//    statistics->calculateStatistics(K,&g);
////    if(numOfPoints>20)
////        statistics->printStatistics(K);
////    else
//        statistics->printInMatrixForm(K);
//
//    statistics->printTotalPercentage(K);
//
//
//    //for project 2
//    printf("OPTIMIZATIONS\n");
//    Optimizations op;
//    for(int i=0;i<dataset.getNumOfPoints();i++){
//        op.putPoints(elements.at(i).getCoordinates());
//    }
//
//    op.setK(K);
//    op.setMetrics(metrics);
//    op.setDimensions(dataset.getDimensions());
//    op.setd(0.01);
//    op.setKRandomNeighbors();
//    op.initFlags();
//    op.initReverseNN();
//    op.sortKNeighbors();
//
//    //if query out of the graph
//    if(queryId == dataset.getNumOfPoints() + 1){
//        srand(static_cast<unsigned>(time(NULL)));
//        Vector<float> queryVector;
//        //generate random coordinates
//        for (int i = 0; i < dataset.getDimensions(); i++) {
////          in space [-1.0-1.0]
//            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
//            queryVector.push_back(randomFloat);
//        }
//        Point queryPoint(queryId,queryVector);
//        op.findKNearestNeighborsForPoint(queryPoint);
//
//    }
//    else{
//        op.sortKNeighbors();
//        op.initSampling();
//        while(op.KNN());
//        op.printNeighbors(queryId);
//    }
//    Statistics* statistics2 = new Statistics(elements,dataset.getNumOfPoints(),dataset.getDimensions());
//    statistics2->calculateAllDistances(metrics);
//
//    op.printGraph("optimizedGraph.txt");
//    op.printReverseNN("reverseNN.txt");
//
//
//    statistics2->calculateStatistics(K,&op);
////    if(numOfPoints>20)
////        statistics2->printStatistics(K);
////    else
//        statistics2->printInMatrixForm(K);
//
//    statistics2->printTotalPercentage(K);
//
//    printLogoFromFile("logo.txt");


    //project 3
    printf("RANDOM PROJECTION TREES\n");
    RandomProjectionTrees r(3);
    r.setMetrics(metrics);
    r.setK(K);
    r.setDimensions(dataset.getDimensions());
    for(int i=0;i<dataset.getNumOfPoints();i++){
        r.putPoints(elements.at(i).getCoordinates());
    }

    JobScheduler *scheduler;
    scheduler=new JobScheduler(5);
    scheduler->start_execute(); // Start the worker threads before submitting any jobs
    NormCalculationJob normCalculationJob(r.getPoints());

    scheduler->submit(new NormCalculationJob(r.getPoints()));
    for(int i=0;i<10;i++) {
        scheduler->submit(new RandomProjectionTreeJob(&r));
    }
//    scheduler.submit(new RandomProjectionTreeJob(&r));

//    r.initGraph();
    r.graphInitialization(scheduler);


    // Calculate the time taken by the function in microseconds

    scheduler->wait_to_finish(); // Wait for all jobs to finish after they have been submitted
    clock_t end = clock();
    scheduler->printStats();
    r.printTree();
//    printf("ok\n");
    r.printGraph("project3.txt");
    char buffer2[50];
    sprintf(buffer2, "Execution time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    LOG_INFO(buffer2);

}