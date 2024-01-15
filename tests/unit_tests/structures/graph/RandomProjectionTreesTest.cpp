#include <gtest/gtest.h>
#include "../../../../headers/structures/scheduler/JobScheduler.h"
#include "../../../../headers/structures/randomProjectionTrees/RandomProjectionTrees.h"

class RandomProjectionTreesTest : public ::testing::Test {
protected:
    RandomProjectionTrees *rTree;

    void SetUp() override {
        rTree = new RandomProjectionTrees(2);
    }

    void TearDown() override {
        delete rTree;
    }
};

TEST_F(RandomProjectionTreesTest, putPointsAddsPointsCorrectly) {
    Vector<float> coordinates;
    coordinates.push_back(1.0f);
    coordinates.push_back(2.0f);
    rTree->putPoints(coordinates);
    ASSERT_EQ(rTree->getPoints().getSize(), 1);
}

TEST_F(RandomProjectionTreesTest, calculateInnerProductReturnsCorrectValue) {
    Vector<float> vector1;
    vector1.push_back(1.0f);
    vector1.push_back(2.0f);
    rTree->setDimensions(2);
    Vector<float> vector2;
    vector2.push_back(3.0f);
    vector2.push_back(4.0f);
    float result = rTree->calculateInnerProduct(vector1, vector2);
    ASSERT_FLOAT_EQ(result, 11.0f);
}


TEST_F(RandomProjectionTreesTest, splitCreatesLeafNodeWhenSizeLessThanD) {
    Vector<int> branchPoints = {1, 2};
    Vector<Vector<int>> currentTree;
    rTree->split(branchPoints, currentTree);
    ASSERT_EQ(currentTree.getSize(), 1);
}

TEST_F(RandomProjectionTreesTest, creatTreesIncreasesNumberOfTrees) {
    rTree->creatTrees();
    ASSERT_EQ(rTree->getNumberOfTrees(), 1);
}


TEST_F(RandomProjectionTreesTest, fillGraphFillsGraphToKNeighbors) {
    JobScheduler *scheduler = new JobScheduler(4);
    int id = 1;
    rTree->fillGraph(scheduler, id);
    for (auto &point: rTree->getPoints()) {
        Vector<Neighbors> neighbors;
        rTree->getGraph().find(point, neighbors);
        ASSERT_EQ(neighbors.getSize(), rTree->getK());
    }
    delete scheduler;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}