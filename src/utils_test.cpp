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

TEST(Hashing, HashLine) {
    Point A(0, 0), B(0.1, 0), C(0.00001, 0), D(0, 1);
    const auto hasher = std::hash<Line>();
    EXPECT_EQ(hasher(Line(A, B)), hasher(Line(B, A)));
    EXPECT_EQ(hasher(Line(A, B)), hasher(Line(C, B)));
    EXPECT_NE(hasher(Line(A, B)), hasher(Line(A, D)));
}

TEST(Hashing, HashSet) {
    Point A(0, 0), B(0.1, 0), C(0.00001, 0), D(-0.00001, 0), E(-0.1, 0);
    std::unordered_set<Point> pointSet1 = { A, B, C};
    std::unordered_set<Point> pointSet2 = { A, C, B};
    std::unordered_set<Point> pointSet3 = { A, B, C, E};
    std::unordered_set<Point> pointSet4 = { E, B, C, A};
    std::unordered_set<Point> pointSet5 = { A, B, C, D};
    EXPECT_EQ(hashSet(pointSet1), hashSet(pointSet2));
    EXPECT_NE(hashSet(pointSet2), hashSet(pointSet3));
    EXPECT_EQ(hashSet(pointSet3), hashSet(pointSet4));
    EXPECT_NE(hashSet(pointSet4), hashSet(pointSet5));
    EXPECT_EQ(hashSet(pointSet5), hashSet(pointSet1));

}
