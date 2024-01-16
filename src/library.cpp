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
#include "../headers/structures/scheduler/job/KNNJob.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <string.h>


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
    Logger::SetSpecificLoggingEnabled("NONE");
    clock_t start = clock();
    if(argc != 11){
        printf("Invalid input. Please provide the correct arguments in the following format: <inputFile> <dimensions> <numOfPoints> <K> <queryId> <d> <metrics> <D> <numOfTrees> <numOfThreads>\n");
        return 0;
    }
    //./name inputFile dimensions numOfPoints K queryId metrics
    char* inputFile = argv[1];
    int dimensions = atoi(argv[2]);
    int numOfPoints = atoi(argv[3]);
    int K = atoi(argv[4]);
    int queryId = atoi(argv[5]);
    int d = atoi(argv[6]);
    char* metrics = argv[7];
    int D = atoi(argv[8]);
    int numOfTrees = atoi(argv[9]);
    int numOfThreads = atoi(argv[10]);

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


//    project 1
//    initialize graph, put points, set K, initialize random k neighbors...
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
            //in space [-1.0-1.0]
            float randomFloat = -1.0 + 2.0 * ((float)rand() / (float)RAND_MAX);
            queryVector.push_back(randomFloat);
        }
        Point queryPoint(queryId,queryVector);
        g.findKNearestNeighborsForPoint(queryPoint);

    }
    else{
        g.sortKNeighbors();
        while(!g.KNNAlgorithm());
        g.calculateAllDistances();
        g.printNeighbors(queryId);
        g.printGraph("graph.txt");
    }


    statistics->calculateStatistics(K,&g);
//    if(numOfPoints>20)
//        statistics->printStatistics(K);
//    else
        statistics->printInMatrixForm(K);

    statistics->printTotalPercentage(K);


    //for project 2
    printf("OPTIMIZATIONS\n");
    Optimizations op;
op.setd(d);
    for(int i=0;i<dataset.getNumOfPoints();i++){
        op.putPoints(elements.at(i).getCoordinates());
    }

    op.setK(K);
    op.setMetrics(metrics);
    op.setDimensions(dataset.getDimensions());
    op.setd(d);
    op.setKRandomNeighbors();
    op.initFlags();
    op.initReverseNN();
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
        op.initSampling();
        while(op.KNN());
        op.printNeighbors(queryId);
    }
    Statistics* statistics2 = new Statistics(elements,dataset.getNumOfPoints(),dataset.getDimensions());
    statistics2->calculateAllDistances(metrics);

    op.printGraph("optimizedGraph.txt");
    op.printReverseNN("reverseNN.txt");


    statistics2->calculateStatistics(K,&op);
//    if(numOfPoints>20)
//        statistics2->printStatistics(K);
//    else
        statistics2->printInMatrixForm(K);

    statistics2->printTotalPercentage(K);

    printLogoFromFile("logo.txt");


    //project 3
    FILE *file;
    file = fopen("times.txt", "w");
    printf("RANDOM PROJECTION TREES\n");
    int jobs=0;
    RandomProjectionTrees r(D);
    r.setMetrics(metrics);
    r.setK(K);
    r.setDimensions(dataset.getDimensions());
    for(int i=0;i<dataset.getNumOfPoints();i++){
        r.putPoints(elements.at(i).getCoordinates());
    }

    Vector<NormCalculationJob*>normCalculationJobs;
    JobScheduler *scheduler;
    scheduler=new JobScheduler(numOfThreads);
    scheduler->start_execute(); // Start the worker threads before submitting any jobs
    int divisionResult = dataset.getNumOfPoints() / K;
    int chunkSize = K < divisionResult ? divisionResult : K;
    for (int i = 0; i < dataset.getNumOfPoints(); i += chunkSize) {
        Vector<Point> points;
        for (int j = i; j < i + chunkSize && j < dataset.getNumOfPoints(); j++) {
            points.push_back(elements.at(j));
        }
        normCalculationJobs.push_back(new NormCalculationJob(points, jobs++, &r));
    }
    char buffer3[50];
    sprintf(buffer3, "Number of jobs: %d\n", jobs);
    LOG_ERROR(buffer3);

//    NormCalculationJob *normCalculationJob=new NormCalculationJob(r.getPoints(),jobs++,&r);
//    NormCalculationJob *normCalculationJob2=new NormCalculationJob(r.getPoints(),jobs++,&r);
    for (int i = 0; i <normCalculationJobs.getSize() ; ++i) {
        scheduler->submit(normCalculationJobs.at(i));
    }
    for(int i=0;i<numOfTrees;i++)
        scheduler->submit(new RandomProjectionTreeJob(&r,normCalculationJobs,jobs++));
    clock_t startt,endt;
    double cputime;
    startt = clock();
    r.graphInitialization(scheduler,jobs++);
    endt = clock();
    cputime = (double)(endt - startt) / CLOCKS_PER_SEC;
    fprintf(file, "time for %d points and %d neighbors:%f\n",dataset.getNumOfPoints(),K,cputime);

    scheduler->wait_to_finish(); // Wait for all jobs to finish after they have been submitted
    scheduler->start_execute();
    scheduler->submit(new KNNJob(&r,jobs++));
    clock_t end = clock();
    scheduler->wait_to_finish();
    scheduler->printStats();
    r.printTree();
    delete scheduler;
    delete statistics;
    delete statistics2;

    for (int i = 0; i <normCalculationJobs.getSize() ; ++i) {
        delete normCalculationJobs.at(i);
    }


    r.printGraph("project3.txt");
    char buffer2[50];
    sprintf(buffer2, "Execution time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    LOG_INFO(buffer2);

}