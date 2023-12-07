//
// Created by snz on 11/6/2023.
//
#include <gtest/gtest.h>
#include "../../../../headers/structures/unorderedMap/UnorderedMap.h"
#include "../../../../headers/structures/point/Neighbors.h"

TEST(UnorderedMapTest, UnorderedMapInsertFind) {

    // given
    UnorderedMap<Point, Vector<Neighbors>> map;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    Point point(1, vecCords);
    Vector<Neighbors> vecNeighbors;
    vecNeighbors.push_back(Neighbors(1, 1.1f, vecCords));
    vecNeighbors.push_back(Neighbors(2, 2.1f, vecCords));
    Vector<Neighbors> testVec;

    // when
    map.insert(point, vecNeighbors);

    // then
    map.find(point, testVec);
    ASSERT_EQ(testVec.at(0), vecNeighbors.at(0));


}

TEST(UnorderedMapTest, UnorderedMapRemove) {

// given
    UnorderedMap<Point, Vector<Neighbors>> map;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    Point point(1, vecCords);
    Point point2(12, vecCords);
    Vector<Neighbors> vecNeighbors;
    vecNeighbors.push_back(Neighbors(1, 1.1f, vecCords));
    vecNeighbors.push_back(Neighbors(2, 2.1f, vecCords));
    map.insert(point, vecNeighbors);
    map.insert(point2, vecNeighbors);
    Vector<Neighbors> testVec;

// when
    map.remove(point);

// then
    map.find(point, testVec);
    ASSERT_EQ(testVec.getSize(), 0);
    map.find(point2, testVec);
    ASSERT_EQ(testVec.at(0), vecNeighbors.at(0));


}

TEST(UnorderedMapTest, UnorderedMapGet) {

   // given
    UnorderedMap<Point, Vector<Neighbors>> map;
    Vector<float> vecCords;
    vecCords.push_back(1.1f);
    vecCords.push_back(2.2f);
    vecCords.push_back(3.3f);
    Point point(1, vecCords);
    Point point2(12, vecCords);
    Vector<Neighbors> vecNeighbors;
    vecNeighbors.push_back(Neighbors(1, 1.1f, vecCords));
    vecNeighbors.push_back(Neighbors(2, 2.1f, vecCords));
    map.insert(point, vecNeighbors);
    map.insert(point2, vecNeighbors);
   // when
    Vector<Neighbors> test = map.get(point);

   // then
    ASSERT_EQ(vecNeighbors.at(0), test.at(0));

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}