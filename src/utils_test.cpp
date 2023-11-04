#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils.h"
#include <unordered_set>

TEST(Hashing, HashPoint) {
    Point A(0, 0), B(0.1, 0), C(0.00001, 0), D(-0.00001, 0), E(-0.1, 0);
    const auto hasher = std::hash<Point>();
    EXPECT_NE(hasher(A), hasher(B));
    EXPECT_EQ(hasher(A), hasher(C));

    std::unordered_set<Point> pointSet = { A, B, C};
    std::unordered_set<Point>::hasher fn = pointSet.hash_function(); 
    EXPECT_EQ(pointSet.size(), 2);
    EXPECT_TRUE(pointSet.count(D));
    EXPECT_FALSE(pointSet.count(E));
}
