#include "input/Input.hpp"
#include <cmath>
#include <stdexcept>

std::vector<Triangle> readTriangles(std::istream& input){
    long long n = 0;
    input >> n;
    std::vector<Triangle> triangles;
    triangles.reserve(n);
    for (long long i = 0; i < n; ++i){
        Triangle triangle;

        input >> triangle.A.x >> triangle.A.y >> triangle.A.z
              >> triangle.B.x >> triangle.B.y >> triangle.B.z
              >> triangle.C.x >> triangle.C.y >> triangle.C.z;

        triangles.push_back(triangle);
    }
    return triangles;
}