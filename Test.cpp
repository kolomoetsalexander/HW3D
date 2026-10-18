#include "Test.hpp"
#include <cmath>
#include <random>


std::vector<Triangle> generateTriangles(long long n){
    std::mt19937 rng(std::random_device{}());
    //the size of the cube increases with n, so the density of triangles remains approximately constant
    float spread = std::cbrt(static_cast<float>(n)) * 2.0f;
    std::uniform_real_distribution<float> centerDist(0.0f, spread);
    std::uniform_real_distribution<float> offsetDist(-1.0f, 1.0f);
    std::vector<Triangle> triangles;
    triangles.reserve(static_cast<size_t>(n));
    for(long long i = 0; i < n; ++i){
        glm::vec3 c(centerDist(rng), centerDist(rng), centerDist(rng));
        Triangle t;
        t.A = c + glm::vec3(offsetDist(rng), offsetDist(rng), offsetDist(rng));
        t.B = c + glm::vec3(offsetDist(rng), offsetDist(rng), offsetDist(rng));
        t.C = c + glm::vec3(offsetDist(rng), offsetDist(rng), offsetDist(rng));
        triangles.push_back(t);
    }
    return triangles;
}