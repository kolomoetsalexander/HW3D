#include "application/Application.hpp"
#include "geometry/Intersection.hpp"
#include "geometry/Grid.hpp"
#include "geometry/Test.hpp"
#include "geometry/Triangle.hpp"

#include <iostream>
#include <vector>

int main() {
    long long n = 0;
    std::cin >> n;
    std::vector<Triangle> triangles = generateTriangles(n);
    // Поиск пересекающихся треугольников
    std::vector<bool> intersects(triangles.size(), false);
    Grid grid(triangles);
    for(const auto& pair : grid.candidatePairs()){
        std::size_t i = pair.first;
        std::size_t j = pair.second;
        if(trianglesIntersect(triangles[i], triangles[j])){
            intersects[i] = true;
            intersects[j] = true;
        }
    }
    //run app
    Application app;
    app.run(triangles, intersects);
    return 0;
}