#include <gtest/gtest.h>
#include "../../../../headers/structures/graph/GraphInitialization.h"




TEST(GraphInitializationTest, GraphInitializationInitializeK) {

// given
    GraphInitialization graph;

// when
    graph.setK(5);// when creating a graph at first the numPoints is set to 0
// so k should be set to 5


// then
    ASSERT_EQ(graph.getK(), 5);

}

TEST(GraphInitializationTest, GraphInitializationPutPoints) {

    // given
    GraphInitialization graph;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);

    // when
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);
    graph.putPoints(vecCords);


    // then
    ASSERT_EQ(graph.getNumOfPoints(), 3);

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}