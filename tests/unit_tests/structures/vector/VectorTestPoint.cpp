//
// Created by snz on 11/5/2023.
//
#include <gtest/gtest.h>
#include "../../../../headers/structures/vector/Vector.h"
#include "../../../../headers/structures/point/Point.h"

TEST(VectorTest, GetSizePoint) {

    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    Vector<Point> vec2;
    vec2.push_back(Point(1,vec));
    vec2.push_back(Point(2,vec));
    vec2.push_back(Point(3,vec));

    // when
    int size = vec2.getSize();

    // then
    ASSERT_EQ(size, 3);
}
TEST(VectorTest, PushBackPoint) {

    //given
    Vector<float> vec0;
    vec0.push_back(1.1f);
    vec0.push_back(3.2f);
    vec0.push_back(4.3f);
    Vector<Point> vec;

    //when
    vec.push_back(Point(1,vec0));

    //then
    ASSERT_EQ(vec.getSize(), 1);
    ASSERT_EQ(vec.at(0).getId(),1);
    ASSERT_EQ(vec.at(0).getCoordinates().at(0),1.1f);
    ASSERT_EQ(vec.at(0).getCoordinates().at(1),3.2f);
    ASSERT_EQ(vec.at(0).getCoordinates().at(2),4.3f);
}

TEST(VectorTest, AtPoint) {

    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);
    vec.push_back(3.3f);

    Vector<Point> vec0;
    vec0.push_back(Point(1,vec));
    vec0.push_back(Point(2,vec));
    vec0.push_back(Point(3,vec));

    // given ,then
    // Test accessing elements within bounds
    ASSERT_EQ(vec0.at(0), Point(1,vec));
    ASSERT_EQ(vec0.at(1), Point(2,vec));
    ASSERT_EQ(vec0.at(2), Point(3,vec));

    // Test for an out-of-bounds index
    ASSERT_THROW(vec.at(-1), const char*);
    ASSERT_THROW(vec.at(3), const char*);
}

TEST(VectorTest, SortPoint) {

    //given
    Vector<float> vec;
    vec.push_back(42.0);
    vec.push_back(15.0);
    vec.push_back(78.0);
    vec.push_back(3.0);

    Vector<Point> vec0;
    vec0.push_back(Point(4,vec));
    vec0.push_back(Point(1,vec));
    vec0.push_back(Point(3,vec));
    vec0.push_back(Point(2,vec));

    //when
    vec0.sort();

    //then
    ASSERT_EQ(vec0.at(0), Point(1,vec));
    ASSERT_EQ(vec0.at(1), Point(2,vec));
    ASSERT_EQ(vec0.at(2), Point(3,vec));
    ASSERT_EQ(vec0.at(3), Point(4,vec));
}


TEST(VectorTest, ReplacePoint) {

    //given
    Vector<float> vec;
    vec.push_back(42.0f);
    vec.push_back(15.0f);
    vec.push_back(78.0f);
    Vector<Point> vec0;
    vec0.push_back(Point(4,vec));
    vec0.push_back(Point(1,vec));
    vec0.push_back(Point(3,vec));

    //when
    vec0.replace(Point(4,vec),Point(5,vec));

    //then
    ASSERT_EQ(vec0.at(0), Point(5,vec));
}

TEST(VectorTest, RemovePoint) {

    //given
    Vector<float> vec;
    vec.push_back(42.0);
    vec.push_back(15.0);
    vec.push_back(78.0);

    Vector<Point> vec0;
    vec0.push_back(Point(4,vec));
    vec0.push_back(Point(1,vec));
    vec0.push_back(Point(3,vec));

    //when
    vec0.remove(Point(4,vec));

    //then
    // Check if the value has been removed
    ASSERT_EQ(vec0.getSize(), 2.0f);
    ASSERT_EQ(vec0.at(0), Point(1,vec));
    ASSERT_EQ(vec0.at(1), Point(3,vec));
}

TEST(VectorTest, OperatorLessThanPoint) {
    // given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);

    Vector<Point> vec0;
    vec0.push_back(Point(1,vec));
    vec0.push_back(Point(2,vec));
    vec0.push_back(Point(3,vec));

    Vector<Point> vec1;
    vec1.push_back(Point(4,vec));
    vec1.push_back(Point(5,vec));
    vec1.push_back(Point(6,vec));

    // when , then
    ASSERT_TRUE(vec0 < vec1);
    ASSERT_FALSE(vec1 < vec0);
}
TEST(VectorTest, OperatorEqualPoint) {
    // Given
    Vector<float> vec;
    vec.push_back(1.1f);
    vec.push_back(2.2f);

    Vector<Point> vec0;
    vec0.push_back(Point(1, vec));
    vec0.push_back(Point(2, vec));
    vec0.push_back(Point(3, vec));

    Vector<Point> vec1;
    vec1.push_back(Point(1, vec));
    vec1.push_back(Point(2, vec));
    vec1.push_back(Point(3, vec));

    // when and then

    ASSERT_TRUE(vec0.at(0) == vec1.at(0));
    ASSERT_TRUE(vec0.at(1) == vec1.at(1));
    ASSERT_TRUE(vec0.at(2) == vec1.at(2));
}


TEST(VectorTest, OperatorGreaterThanPoint) {
    // given
    Vector<float> vec1;
    vec1.push_back(3.3f);
    vec1.push_back(4.4f);

    Vector<Point> vecP;
    vecP.push_back(Point(3,vec1));
    vecP.push_back(Point(4,vec1));

    Vector<Point> vecP1;
    vecP1.push_back(Point(1,vec1));
    vecP1.push_back(Point(2,vec1));

    // when , then
    ASSERT_TRUE(vecP > vecP1);
    ASSERT_FALSE(vecP1 > vecP);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}