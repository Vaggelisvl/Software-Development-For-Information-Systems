//
// Created by snz on 11/6/2023.
//
#include <gtest/gtest.h>
#include "../../../../headers/structures/vector/Vector.h"
#include "../../../../headers/structures/point/Point.h"
#include "../../../../headers/structures/Dataset.h"

TEST(DataSetTest, GenericTestLowBoundary) {

    // given
    Vector<Point> vec;
    char file[100]="tests/resources/input1.bin";
    Dataset dataset(file,20,100);

    // when
    dataset.readVectorFromFile(vec);

    // then
    ASSERT_EQ(vec.getSize(), 20);
    ASSERT_EQ(dataset.getDimensions(), 100);
    ASSERT_EQ(vec.at(0).getCoordinates().getSize(),100);
}