//
// Created by vaggelis on 7/12/2023.
//

#include <gtest/gtest.h>

#include "../../../../headers/structures/point/Neighbors.h"
TEST(NeighborsTest, GetDistanceNeighbor)
{
    //given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);
    Neighbors n(1,5.0,vec);
    //when
    float distance = n.getDistance();
    //then
    ASSERT_EQ(distance, 5.0);
}

TEST(NeighborsTest, SetDistanceNeighbor)
{
    //given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);
    Neighbors n(1,5.0,vec);
    //when
    n.setDistance(7.0);
    float distance = n.getDistance();
    //then
    ASSERT_EQ(distance, 7.0);
}

TEST(NeighborsTest, GetFlagNeighbor)
{
    //given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);
    Neighbors n(1,5.0,vec);
    //when
    n.setFlag(true);
    bool flag = n.getFlag();
    //then
    ASSERT_EQ(flag, true);
}

TEST(NeighborsTest, SetIdNeighbor)
{
    //given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);
    Neighbors n(1,5.0,vec);
    //when
    n.setId(3);
    int id= n.getId();
    //then
    ASSERT_EQ(id, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}