//
// Created by vaggelis on 1/12/2023.
//
#include <gtest/gtest.h>

TEST_F(MetricsTest, EuclideanDistance) {
    // Test case for Euclidean Distance

    Vector<float> a = {1.0, 2.0, 3.0};
    Vector<float> b = {4.0, 5.0, 6.0};

    float result = Metrics::euclideanDistance(a, b, 3);
m
    // Adjust the expected result based on the actual implementation of euclideanDistance
    float expected = 5.19615;

    // Check that the result is within a small delta of the expected value
    EXPECT_NEAR(result, expected, 0.00001);
}

TEST_F(MetricsTest, ManhattanDistance) {
    // Test case for Manhattan Distance

    Vector<float> a = {1.0, 2.0, 3.0};
    Vector<float> b = {4.0, 5.0, 6.0};

    float result = Metrics::manhattanDistance(a, b, 3);

    // Adjust the expected result based on the actual implementation of manhattanDistance
    float expected = 9.0;

    // Check that the result is equal to the expected value
    EXPECT_EQ(result, expected);
}

// Add more test cases for other methods in the Metrics class

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}