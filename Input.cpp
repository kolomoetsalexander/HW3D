#include "Input.hpp"
#include <iostream>
std::vector<Triangle> readTrianglesFromStdin(){
    long long n = 0;
    std::cin >> n;
    std::vector<Triangle> triangles;
    triangles.reserve(static_cast<size_t>(n));

    for (long long i = 0; i < n; ++i){
        Triangle t;
        std::cin >> t.A.x >> t.A.y >> t.A.z
                 >> t.B.x >> t.B.y >> t.B.z
                 >> t.C.x >> t.C.y >> t.C.z;
        triangles.push_back(t);
    }
    return triangles;
}