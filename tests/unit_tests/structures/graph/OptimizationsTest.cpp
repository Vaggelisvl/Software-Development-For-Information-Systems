//
// Created by vaggelis on 7/12/2023.
//
#include <gtest/gtest.h>

#include "../../../../headers/structures/graph/Optimizations.h"
TEST(OptimizationsTest, OptimizationsInitSampling)
{

    // given
    Optimizations graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.setKRandomNeighbors();

    // when
    graph.initSampling();


    // then
    UnorderedMap< Point ,Vector<Neighbors> >graphMap = graph.getGraph();
    Vector<Neighbors> neighbors ;
    graphMap.find(graph.getPoint(0),neighbors);
    for( int i=0;i<neighbors.getSize();i++){
        ASSERT_EQ(neighbors.at(i).getHasBeenChoosen(), 0);
    }

}

TEST(OptimizationsTest, OptimizationsInitFlags)
{

    // given
    Optimizations graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.setKRandomNeighbors();

    // when
    graph.initFlags();


    // then
    UnorderedMap< Point ,Vector<Neighbors> >graphMap = graph.getGraph();
    Vector<Neighbors> neighbors ;
    graphMap.find(graph.getPoint(0),neighbors);
    for(int i=0;i<neighbors.getSize();i++){
        ASSERT_EQ(neighbors.at(i).getFlag(), true);
    }

    Vector<Neighbors> neighbors1 ;
    graphMap.find(graph.getPoint(1),neighbors1);
    for(int i=0;i<neighbors1.getSize();i++){
        ASSERT_EQ(neighbors.at(i).getFlag(), true);
    }

}

TEST(OptimizationsTest, OptimizationsSetd)
{

    // given
    Optimizations graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.setKRandomNeighbors();

    // when
   graph.setd(5);


    // then
    ASSERT_EQ(graph.getd(), 5);


}

TEST(OptimizationsTest, OptimizationsInitReverseNN)
{

    // given
    Optimizations graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.setKRandomNeighbors();

    // when
    graph.setd(5);


    // then
    ASSERT_EQ(graph.getd(), 5);


}

// TEST(OptimizationsTest, OptimizationsSampling)
// {
//
//     // given
//     Optimizations graph;
//     Vector<float> vecCords;
//     vecCords.push_back(1.1f);
//     vecCords.push_back(2.2f);
//     vecCords.push_back(3.3f);
//     graph.putPoints(vecCords);
//     graph.putPoints(vecCords);
//     graph.putPoints(vecCords);
//     graph.setKRandomNeighbors();
//
//     // when
//     graph.sampling();
//
//
//
//     // then
//
//     ASSERT_EQ(graph.getNeighborsOfPoint(graph.getPoint(0)).at(0).getHasBeenChoosen(), 1);
//
//
// }