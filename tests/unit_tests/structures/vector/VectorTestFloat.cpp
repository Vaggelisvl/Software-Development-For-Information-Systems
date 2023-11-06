//
// Created by snz on 11/5/2023.
//
#include <gtest/gtest.h>
#include "../../../../headers/structures/vector/Vector.h"
TEST(VectorTest, GetSizeFloat) {
    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    // when
    int size = vec.getSize();

    // then
    ASSERT_EQ(size, 3);
}
TEST(VectorTest, PushBackFloat) {
    //given
    Vector<float> vec;
    //when
    vec.push_back(42.0f);
    //then
    ASSERT_EQ(vec.getSize(), 1);
    ASSERT_EQ(vec.at(0), 42.0f);
}

TEST(VectorTest, AtFloat) {
    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    // given ,then
    // Test accessing elements within bounds
    ASSERT_FLOAT_EQ(vec.at(0), 1.1f);
    ASSERT_FLOAT_EQ(vec.at(1), 2.2f);
    ASSERT_FLOAT_EQ(vec.at(2), 3.3f);

    // Test for an out-of-bounds index
    ASSERT_THROW(vec.at(-1), const char*);
    ASSERT_THROW(vec.at(3), const char*);
}

TEST(VectorTest, SortFloat) {
    //given
    Vector<float> vec;
    vec.push_back(42.0);
    vec.push_back(15.0);
    vec.push_back(78.0);
    vec.push_back(3.0);
    //when
    vec.sort();
    //then
    ASSERT_EQ(vec.at(0), 3.0);
    ASSERT_EQ(vec.at(1), 15.0);
    ASSERT_EQ(vec.at(2), 42.0);
    ASSERT_EQ(vec.at(3), 78.0);
}

TEST(VectorTest, ReserveFloat) {
    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    // when
    vec.reserve(10);

    // then
    ASSERT_EQ(vec.getCapacity(), 10);
}


TEST(VectorTest, ReplaceFloat) {
    //given
    Vector<float> vec;
    vec.push_back(42.0f);
    vec.push_back(15.0f);
    vec.push_back(78.0f);
    //when
    vec.replace(15.0f, 99.0f);
    //then
    // Check if the value has been replaced
    ASSERT_EQ(vec.at(1), 99.0f);
}

TEST(VectorTest, RemoveFloat) {
    //given
    Vector<float> vec;
    vec.push_back(42.0);
    vec.push_back(15.0);
    vec.push_back(78.0);
    //when
    vec.remove(15.0);
    //then
    // Check if the value has been removed
    ASSERT_EQ(vec.getSize(), 2.0);
    ASSERT_EQ(vec.at(0), 42.0);
    ASSERT_EQ(vec.at(1), 78.0);
}

TEST(VectorTest, OperatorLessThanFloat) {
    // given
    Vector<float> vec1;
    vec1.push_back(1.1f);
    vec1.push_back(2.2f);

    Vector<float> vec2;
    vec2.push_back(3.3f);
    vec2.push_back(4.4f);

    // when , then
    ASSERT_TRUE(vec1 < vec2);
    ASSERT_FALSE(vec2 < vec1);
}
TEST(VectorTest, OperatorEqualFloat) {
    // given
    Vector<float> vec1;
    vec1.push_back(1.1f);
    vec1.push_back(2.2f);

    Vector<float> vec2;
    vec2.push_back(1.1f);
    vec2.push_back(2.2f);

    // when and then
    ASSERT_TRUE(vec1 == vec2);
    ASSERT_TRUE(vec2 == vec1);
}

TEST(VectorTest, OperatorGreaterThanFloat) {
    // given
    Vector<float> vec1;
    vec1.push_back(3.3f);
    vec1.push_back(4.4f);

    Vector<float> vec2;
    vec2.push_back(1.1f);
    vec2.push_back(2.2f);

    // when , then
    ASSERT_TRUE(vec1 > vec2);
    ASSERT_FALSE(vec2 > vec1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
