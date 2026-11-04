#include <gtest/gtest.h>
#include "geometry/Grid.hpp"
#include <algorithm>
#include <vector>

static Triangle makeTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
    return Triangle{a, b, c};
}

//empty
TEST(GridTests, EmptyGrid){
    std::vector<Triangle> triangles;
    Grid grid(triangles);
    EXPECT_TRUE(grid.candidatePairs().empty());
}

//far triangls
TEST(GridTests, DistantTriangles) {
    std::vector<Triangle> triangles = {
        makeTriangle({0, 0, 0}, {1, 0, 0}, {0, 1, 0}),
        makeTriangle({10, 10, 10}, {11, 10, 10}, {10, 11, 10})
    };

    Grid grid(triangles);
    EXPECT_TRUE(grid.candidatePairs().empty());
}

// Пересекающиеся треугольники должны попасть
// в список потенциальных пар.
TEST(GridTests, IntersectingTrianglesAreCandidates){
    std::vector<Triangle> triangles = {
        makeTriangle({0, 0, 0}, {2, 0, 0}, {0, 2, 0}),
        makeTriangle({0.5f, 0.5f, -1}, {0.5f, 0.5f, 1}, {1.5f, 0.5f, 0})
    };
    Grid grid(triangles);
    auto pairs = grid.candidatePairs();
    EXPECT_EQ(pairs.size(), 1);
    EXPECT_EQ(pairs[0].first, 0);
    EXPECT_EQ(pairs[0].second, 1);
}

// AABB пересекаются, хотя сами треугольники
// геометрически не пересекаются.
TEST(GridTests, OverlappingBoundingBoxes){
    std::vector<Triangle> triangles = {
        makeTriangle({0, 0, 0}, {2, 0, 0}, {0, 2, 0}),
        makeTriangle({2, 2, 0}, {2, 1.1f, 0}, {1.1f, 2, 0})
    };

    Grid grid(triangles);
    auto pairs = grid.candidatePairs();
    EXPECT_EQ(pairs.size(), 1);
    EXPECT_EQ(pairs[0].first, 0);
    EXPECT_EQ(pairs[0].second, 1);
}
