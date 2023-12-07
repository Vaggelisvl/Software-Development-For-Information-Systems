#ifndef _PROJECT_OPTIMIZATIONS_H
#define _PROJECT_OPTIMIZATIONS_H
/**
* @file Optimizations.h
* @brief This file contains the declaration of the Optimizations class.
*/
#include "GraphInitialization.h"

typedef struct DistanceContents {
    int id;
    float dist;
}DistanceContents;


class Optimizations : public GraphInitialization{
private:
    /**
    * @brief This function checks if a point is a duplicate in the neighbor list of another point.
    * @param point1 The first point to check.
    * @param point2 The second point to check.
    * @param neighborsList1 The neighbor list of the first point.
    * @param neighborsList2 The neighbor list of the second point.
    * @return 1 if the point is a duplicate, 0 otherwise.
    */
    int checkDuplicate(Neighbors,Neighbors,Vector<Neighbors>, Vector<Neighbors>);
    /**
    * @brief This function checks if the distance between two points has already been calculated and stored in the hash map.
    * @param point1 The first point.
    * @param point2 The second point.
    * @return The id of the point if the distance has been calculated, 0 otherwise.
    */
    int hashingDuplicateDistances(Point&, Point&);
    UnorderedMap<Point, DistanceContents > hashMap;
    UnorderedMap< Point, Vector<Neighbors> > reverseNN;
    float d;
    bool hasBeenInitialized=false;
public:

    /**
    * @brief This function is used to sample a subset of neighbors for each point in the graph.
    * The sampling rate is determined by a random float p between 0.1 and 1.0.
    * The function sets a percentage of the neighbors of each point to be sampled based on p.
    */
    void sampling();

    /**
    * @brief This function initializes the sampling process by setting the 'hasBeenChoosen' attribute of each point and its neighbors to 0.
    */
    void initSampling();

    /**
    * @brief This function sets the value of the member variable 'd'.
    * @param d The value to set.
    */
    void setd(float);
    //for testing purposes
    /**
    * @brief This function gets the value of the member variable 'd'.
    * @return The value of 'd'.
    */
    float getd();
    //end of testing purposes

    /**
    * @brief This function performs a local join operation on a point and its neighbors.
    * @param i The index of the point in the points vector.
    * @param count A reference to a count variable to keep track of the number of new neighbors.
    * @param tempPointVector A reference to a vector to store the points that will be inserted in the graph.
    * @return A temporary graph with the new neighbor vectors of points.
    */
    UnorderedMap<Point, Vector<Neighbors> > localJoin(int,int&,Vector<Point>&);

    /**
    * @brief This function performs the KNN join operation on the graph.
    * @return 1 if the operation should be repeated, 0 otherwise.
    */
    int KNN();

    /**
    * @brief This function initializes the flags of all neighbors of each point in the graph to true.
     */
    void initFlags();

    /**
    * @brief This function performs an incremental search to find new neighbors in the local join.
    * @param n1 The first neighbor to check.
    * @param n2 The second neighbor to check.
    * @return 1 if either neighbor is new in the local join, 0 otherwise.
    */
    int incrementalSearch(Neighbors &,Neighbors&);

    /**
    * @brief This function finds the K nearest neighbors for a query point and inserts it into the graph.
    * @param queryPoint The query point.
    */
    void findKNearestNeighborsForPoint(const Point& queryPoint) override;

    /**
    * @brief This function initializes the reverse nearest neighbor (RNN) graph.
    */
    void initReverseNN();

    /**
    * @brief This function removes a point from the reverse nearest neighbor (RNN) list of another point.
    * @param neighbor The neighbor to remove.
    * @param point The point from whose RNN list the neighbor should be removed.
    */
    void removeReverseNeighbor(const Neighbors&,const Point&);

    /**
    * @brief This function adds a point to the reverse nearest neighbor (RNN) list of another point.
    * @param neighbor The neighbor to add.
    * @param point The point to whose RNN list the neighbor should be added.
    */
    void putReverseNeighbor(const Neighbors&,const Point&);

    /**
    * @brief This function prints the reverse nearest neighbor (RNN) graph to a file.
    * @param outputFile The name of the output file.
    */
    void printReverseNN(char*);
};


#endif //_PROJECT_OPTIMIZATIONS_H
