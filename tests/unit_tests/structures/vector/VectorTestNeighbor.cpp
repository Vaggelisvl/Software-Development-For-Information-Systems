//
// Created by snz on 11/6/2023.
//
#include <gtest/gtest.h>
#include "../../../../headers/structures/vector/Vector.h"
#include "../../../../headers/structures/point/Neighbors.h"

TEST(VectorTestNeighbor, GetSizeNeighbor) {

    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    Vector<Neighbors> vec2;
    vec2.push_back(Neighbors(1,0.2f,vec));
    vec2.push_back(Neighbors(2,1.0f,vec));
    vec2.push_back(Neighbors(3,2.0f,vec));

    // when
    int size = vec2.getSize();

    // then
    ASSERT_EQ(size, 3);
}
TEST(VectorTestNeighbor, PushBackNeighbor) {

    //given
    Vector<float> vec0;
    vec0.push_back(1.1f);
    vec0.push_back(3.2f);
    vec0.push_back(4.3f);
    Vector<Neighbors> vec;

    //when
    vec.push_back(Neighbors(1,0.2f,vec0));

    //then
    ASSERT_EQ(vec.getSize(), 1);
    ASSERT_EQ(vec.at(0), Neighbors(1,0.2f,vec0));
}

TEST(VectorTestNeighbor, AtNeighbor) {

    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    Vector<Neighbors> vec0;
    vec0.push_back(Neighbors(1,0.2f,vec));
    vec0.push_back(Neighbors(2,0.5f,vec));
    vec0.push_back(Neighbors(3,1.2f,vec));

    // given ,then
    // Test accessing elements within bounds
    ASSERT_EQ(vec0.at(0), Neighbors(1,0.2f,vec));
    ASSERT_EQ(vec0.at(1), Neighbors(2,0.5f,vec));
    ASSERT_EQ(vec0.at(2), Neighbors(3,1.2f,vec));

    // Test for an out-of-bounds index
    ASSERT_THROW(vec.at(-1), const char*);
    ASSERT_THROW(vec.at(3), const char*);
}



TEST(VectorTestNeighbor, ReplaceNeighbor) {

    //given
    Vector<float> vec;
    vec.push_back(42.0f);
    vec.push_back(15.0f);
    vec.push_back(78.0f);
    Vector<Neighbors> vec0;
    vec0.push_back(Neighbors(4,5.0f,vec));
    vec0.push_back(Neighbors(1,3.2f,vec));
    vec0.push_back(Neighbors(3,0.2f,vec));
    vec0.push_back(Neighbors(2,6.0f,vec));

    //when
    vec0.replace(Neighbors(4,5.0f,vec),Neighbors(3,0.2f,vec));

    //then
    ASSERT_EQ(vec0.at(0), Neighbors(3,0.2f,vec));
}

TEST(VectorTestNeighbor, RemoveNeighbor) {

    //given
    Vector<float> vec;
    vec.push_back(42.0);
    vec.push_back(15.0);
    vec.push_back(78.0);

    Vector<Neighbors> vec0;
    vec0.push_back(Neighbors(4,5.0f,vec));
    vec0.push_back(Neighbors(1,3.2f,vec));
    vec0.push_back(Neighbors(3,0.2f,vec));


    //when
    vec0.remove(Neighbors(4,5.0f,vec));

    //then
    // Check if the value has been removed
    ASSERT_EQ(vec0.getSize(), 2.0f);
    ASSERT_EQ(vec0.at(0), Neighbors(1,3.2f,vec));
    ASSERT_EQ(vec0.at(1), Neighbors(3,0.2f,vec));
}

TEST(VectorTestNeighbor, OperatorEqualNeighbor) {
    // Given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);

    Vector<Neighbors> vec0;
    vec0.push_back(Neighbors(1,0.1f,vec));
    vec0.push_back(Neighbors(2,0.1f,vec));
    vec0.push_back(Neighbors(3,0.1f,vec));

    Vector<Neighbors> vec1;
    vec1.push_back(Neighbors(1,0.1f,vec));
    vec1.push_back(Neighbors(2,0.1f,vec));
    vec1.push_back(Neighbors(3,0.1f,vec));

    // when and then

    ASSERT_TRUE(vec0.at(0) == vec1.at(0));
    ASSERT_TRUE(vec0.at(1) == vec1.at(1));
    ASSERT_TRUE(vec0.at(2) == vec1.at(2));
}


TEST(VectorTestNeighbor, OperatorGreaterThanNeighbor) {
    // given
    Vector<float> vec1;
    vec1.push_back(3.3f);
    vec1.push_back(4.4f);

    Vector<Neighbors> vecN;
    vecN.push_back(Neighbors(1,0.1f,vec1));
    vecN.push_back(Neighbors(2,0.2f,vec1));
    vecN.push_back(Neighbors(3,0.3f,vec1));

    Vector<Neighbors> vecN1;
    vecN1.push_back(Neighbors(4,0.4f,vec1));
    vecN1.push_back(Neighbors(5,0.5f,vec1));
    vecN1.push_back(Neighbors(6,0.6f,vec1));
    // when , then
    ASSERT_TRUE(vecN1 > vecN);
    ASSERT_FALSE(vecN > vecN1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}