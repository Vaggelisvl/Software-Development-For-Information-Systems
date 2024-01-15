//
// Created by vaggelis on 7/12/2023.
//
#include <gtest/gtest.h>

#include "../../../../headers/structures/graph/Optimizations.h"

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

TEST(OptimizationsTest, KNNJoinRepeatsOperationUntilNoNewNeighbors)
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
    int repeatFlag = graph.KNN();

    // then
    ASSERT_EQ(repeatFlag, 0);
}

TEST(OptimizationsTest, IncrementalSearchFindsNewNeighbors)
{
    //given
    Optimizations graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.setKRandomNeighbors();
    Neighbors n1(0,1, vecCords);
    n1.setHasBeenChoosen(1);
    n1.setFlag(true);
    Neighbors n2(1,1, vecCords);
    n2.setHasBeenChoosen(1);
    n2.setFlag(true);

    //when
    int result = graph.incrementalSearch(n1, n2);


    //then

    ASSERT_EQ(result, 1);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}