#include <gtest/gtest.h>
#include "geometry/Intersection.hpp"

static Triangle makeTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
    return Triangle{a, b, c};
}
// Два треугольника имеют одну общую вершину.
TEST(IntersectionTests, SharedVertex){
    Triangle t1 = makeTriangle({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
    Triangle t2 = makeTriangle({2, 0, 0}, {1, 0, 0}, {2, 1, 0});
    EXPECT_TRUE(trianglesIntersect(t1, t2));
}
// Два треугольника имеют общее ребро.
TEST(IntersectionTests, SharedEdge){
    Triangle t1 = makeTriangle({0, 0, 0}, {2, 0, 0}, {0, 2, 0});
    Triangle t2 = makeTriangle({0, 0, 0}, {2, 0, 0}, {2, -2, 0});
    EXPECT_TRUE(trianglesIntersect(t1, t2));
}
// Один треугольник полностью внутри другого.
TEST(IntersectionTests, OneTriangleInsideAnother){
    Triangle t1 = makeTriangle({0, 0, 0}, {4, 0, 0}, {0, 4, 0});
    Triangle t2 = makeTriangle({1, 1, 0}, {2, 1, 0}, {1, 2, 0});
    EXPECT_TRUE(trianglesIntersect(t1, t2));
}
// Пересечение треугольников в пространстве.
TEST(IntersectionTests, NonCoplanarIntersection){
    Triangle t1 = makeTriangle({0, 0, 0}, {2, 0, 0}, {0, 2, 0});
    Triangle t2 = makeTriangle({0.5f, 0.5f, -1}, {0.5f, 0.5f, 1}, {1.5f, 0.5f, 0});
    EXPECT_TRUE(trianglesIntersect(t1, t2));
}

